#!/usr/bin/env python3
"""Paint Zero's sprites a frame at a time, and save them straight into the decomp.

    tools/sprite_editor/start.sh                         # opens http://localhost:8766
    tools/sprite_editor/sprite_editor.py --sprites ~/rmz3/sprites

The page draws every frame whole and, on Save, cuts the frames back into tiles and subsprites
itself (core.js). This only serves the sprite files, writes the ones a save changes and runs make
when the page asks, so it needs nothing but Python.
"""

import argparse
import base64
import json
import os
import re
import subprocess
import threading
import webbrowser
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

HERE = Path(__file__).resolve().parent
DEFAULT_SPRITES = HERE.parents[1] / "sprites"

# The only files a save may write.
WRITABLE = re.compile(r"dynamic/zero/[\w/]+/(metasprite\.json|sheet/header\.inc|sheet/\d+\.png)|sprites\.mk")


def inside(sprites, rel):
    """-> the file rel names, or None if it is outside the sprites folder."""
    path = (sprites / rel).resolve()
    return path if path.is_relative_to(sprites.resolve()) else None


def animations(sprites):
    """Zero's animations, as paths under sprites/. The door's sheets are not plain tiles."""
    out = []
    for meta in sorted((sprites / "dynamic/zero").rglob("metasprite.json")):
        sheet = meta.parent / "sheet"
        header = sheet / "header.inc"
        if not (sheet / "0.png").exists() or not header.exists():
            continue
        if any(int(n) % 32 for n in re.findall(r"\.4byte (\d+) \|", header.read_text())):
            continue
        out.append(meta.parent.relative_to(sprites).as_posix())
    return out


def build(root, region):
    """Runs make for one region. -> what the page shows."""
    rom = "rmz3-us.gba" if region == "us" else "rmz3.gba"
    env = dict(os.environ)
    env.setdefault("DEVKITARM", "/usr")
    run = subprocess.run(["make", f"REGION={region}", f"-j{os.cpu_count()}"], cwd=root, env=env,
                         stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    lines = run.stdout.splitlines()
    print(f"make REGION={region}: exit {run.returncode}")
    return {
        "built": run.returncode == 0 or f"{rom}: FAILED" in lines,
        "matches": run.returncode == 0,
        "rom": str(root / rom),
        "log": "\n".join(lines[-40:]),
    }


def handler(sprites):
    building = threading.Lock()

    class Handler(BaseHTTPRequestHandler):
        def send(self, body, kind, code=200):
            self.send_response(code)
            self.send_header("Content-Type", kind)
            self.send_header("Content-Length", str(len(body)))
            self.send_header("Cache-Control", "no-store")
            self.end_headers()
            self.wfile.write(body)

        def do_GET(self):
            if self.path == "/":
                self.send((HERE / "editor.html").read_bytes(), "text/html; charset=utf-8")
            elif self.path == "/core.js":
                self.send((HERE / "core.js").read_bytes(), "text/javascript")
            elif self.path == "/animations.json":
                self.send(json.dumps({"sprites": str(sprites), "animations": animations(sprites)}).encode(),
                          "application/json")
            elif self.path.startswith("/file/"):
                path = inside(sprites, self.path[len("/file/"):])
                if path and path.is_file():
                    self.send(path.read_bytes(), "application/octet-stream")
                else:
                    self.send(b"not found", "text/plain", 404)
            else:
                self.send(b"not found", "text/plain", 404)

        def do_POST(self):
            req = json.loads(self.rfile.read(int(self.headers["Content-Length"])))
            if self.path == "/build":
                if req.get("region") not in ("us", "jp"):
                    self.send(json.dumps({"error": "region must be us or jp"}).encode(), "application/json", 400)
                elif not building.acquire(blocking=False):
                    self.send(json.dumps({"error": "a build is already running"}).encode(), "application/json", 409)
                else:
                    try:
                        res = build(sprites.parent, req["region"])
                    finally:
                        building.release()
                    self.send(json.dumps({"error": None, **res}).encode(), "application/json")
                return
            files = {}
            for rel, data in req["files"].items():
                path = inside(sprites, rel)
                if not WRITABLE.fullmatch(rel) or path is None:
                    self.send(json.dumps({"error": f"refused to write {rel}"}).encode(), "application/json", 400)
                    return
                files[path] = base64.b64decode(data)
            for path, data in files.items():
                path.write_bytes(data)
            print("saved", ", ".join(sorted(req["files"])))
            self.send(json.dumps({"error": None}).encode(), "application/json")

        def log_message(self, *args):
            pass

    return Handler


def open_browser(url):
    version = Path("/proc/version")
    if version.exists() and "microsoft" in version.read_text().lower():
        try:
            subprocess.run(["cmd.exe", "/c", "start", url], cwd="/mnt/c", stderr=subprocess.DEVNULL)
            return
        except OSError:
            pass
    webbrowser.open(url)


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--sprites", type=Path, default=DEFAULT_SPRITES, help="the rmz3 sprites folder")
    ap.add_argument("--port", type=int, default=8766)
    args = ap.parse_args()
    if not (args.sprites / "sprites.mk").exists():
        raise SystemExit(f"{args.sprites} has no sprites.mk: point --sprites at the decomp's sprites folder")
    url = f"http://localhost:{args.port}"
    try:
        server = ThreadingHTTPServer(("127.0.0.1", args.port), handler(args.sprites))
    except OSError:
        print(f"already running at {url}")
        open_browser(url)
        return
    print(f"editing {args.sprites}")
    print(f"{url}  (Ctrl+C to stop)")
    open_browser(url)
    server.serve_forever()


if __name__ == "__main__":
    main()
