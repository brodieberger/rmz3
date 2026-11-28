#!/usr/bin/env python3
"""Paint Zero's sprites a frame at a time, and save them straight into the decomp.

    tools/sprite_editor/sprite_editor.py                 # then open http://localhost:8766
    tools/sprite_editor/sprite_editor.py --sprites ~/rmz3/sprites

The page draws every frame whole and, on Save, cuts the frames back into tiles and subsprites
itself (core.js). This only serves the sprite files and writes the ones a save changes, so it
needs nothing but Python.
"""

import argparse
import base64
import json
import re
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


def handler(sprites):
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


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--sprites", type=Path, default=DEFAULT_SPRITES, help="the rmz3 sprites folder")
    ap.add_argument("--port", type=int, default=8766)
    args = ap.parse_args()
    if not (args.sprites / "sprites.mk").exists():
        raise SystemExit(f"{args.sprites} has no sprites.mk: point --sprites at the decomp's sprites folder")
    print(f"editing {args.sprites}")
    print(f"http://localhost:{args.port}  (Ctrl+C to stop)")
    ThreadingHTTPServer(("127.0.0.1", args.port), handler(args.sprites)).serve_forever()


if __name__ == "__main__":
    main()
