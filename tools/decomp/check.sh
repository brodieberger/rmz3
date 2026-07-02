#!/usr/bin/env bash
#
# tools/decomp/check.sh — per-function match checker for rmz3 decomp work.
#
# Uses the project's OWN current build as ground truth: since `make compare`
# passes today, objdumping a symbol out of the current ELF gives you the
# exact correct disassembly for that function, mode (thumb/arm) and all.
# No need to touch baserom.gba directly or guess disassembly flags.
#
# Workflow:
#   1. Before editing a naked function, capture its baseline disassembly:
#        tools/decomp/check.sh capture FUN_08005a70
#
#   2. Edit the .c file, replacing the NAKED/asm() block with real C.
#
#   3. Check your progress as often as you want:
#        tools/decomp/check.sh diff FUN_08005a70
#      Prints a unified diff + rough match percentage. Exit code 0 = exact
#      instruction match, 1 = mismatch (diff shown), 2 = build failed.
#
#   4. When it's a clean match, confirm the whole ROM still matches:
#        tools/decomp/check.sh verify
#
# All commands must be run from the repo root.

set -uo pipefail

CACHE_DIR=".decomp_cache"
ELF="rmz3.elf"

TOOL_BIN="${DEVKITARM:-}/bin"
if [ -n "${DEVKITARM:-}" ] && [ -x "$TOOL_BIN/arm-none-eabi-objdump" ]; then
  OBJDUMP="$TOOL_BIN/arm-none-eabi-objdump"
  NM="$TOOL_BIN/arm-none-eabi-nm"
else
  # Fall back to PATH if DEVKITARM isn't set in this shell
  OBJDUMP="arm-none-eabi-objdump"
  NM="arm-none-eabi-nm"
fi

die() { echo "ERROR: $*" >&2; exit 2; }

do_build() {
  echo "== building =="
  # Deliberately build just the ROM, not the default `all` target (which is
  # `$(ROM) compare`) — `compare` fails the whole-ROM sha1 check any time a
  # function under active conversion doesn't yet match, which is the normal
  # state while iterating. `cmd_verify` below does its own explicit sha1 check.
  if ! make -j"$(nproc)" rmz3.gba > /tmp/rmz3_build.log 2>&1; then
    echo "== BUILD FAILED =="
    tail -n 60 /tmp/rmz3_build.log
    exit 2
  fi
}

get_disasm() {
  # get_disasm SYMBOL OUTFILE
  local symbol="$1" outfile="$2"
  local nm_out
  nm_out="$("$NM" "$ELF" 2>/dev/null)"
  if ! grep -qE " ${symbol}\$" <<< "$nm_out"; then
    die "symbol '$symbol' not found in $ELF (check spelling, or that it's not static-stripped)"
  fi
  "$OBJDUMP" -d --disassemble="$symbol" --no-show-raw-insn -M reg-names-std "$ELF" \
    | awk '/^[0-9a-f]+ </{f=1} f' \
    > "$outfile"
  if [ ! -s "$outfile" ]; then
    die "objdump produced no output for '$symbol' — is it inlined or stripped?"
  fi
}

cmd_capture() {
  local symbol="${1:?usage: check.sh capture SYMBOL}"
  mkdir -p "$CACHE_DIR"
  do_build
  get_disasm "$symbol" "$CACHE_DIR/$symbol.target.s"
  echo "== captured baseline for $symbol -> $CACHE_DIR/$symbol.target.s =="
  wc -l < "$CACHE_DIR/$symbol.target.s" | xargs echo "instructions:"
}

cmd_diff() {
  local symbol="${1:?usage: check.sh diff SYMBOL}"
  local target="$CACHE_DIR/$symbol.target.s"
  [ -f "$target" ] || die "no baseline captured for $symbol — run 'capture' before editing next time. Falling back to git to regenerate is not automatic."

  do_build
  local candidate="/tmp/${symbol}.candidate.s"
  get_disasm "$symbol" "$candidate"

  if diff -q "$target" "$candidate" > /dev/null; then
    echo "== ✅ $symbol : EXACT INSTRUCTION MATCH =="
    exit 0
  fi

  local total changed pct
  total=$(wc -l < "$target")
  changed=$(diff -u "$target" "$candidate" | grep -cE '^[+-][^+-]')
  if [ "$total" -gt 0 ]; then
    pct=$(( 100 - (changed * 100 / (total * 2)) ))
  else
    pct=0
  fi

  echo "== ❌ $symbol : MISMATCH (~${pct}% lines unchanged) =="
  diff -u "$target" "$candidate"
  exit 1
}

cmd_verify() {
  do_build
  echo "== verifying full ROM against rmz3.sha1 =="
  if sha1sum -c rmz3.sha1; then
    echo "== ✅ FULL ROM MATCH =="
    exit 0
  else
    echo "== ❌ ROM MISMATCH — something regressed =="
    exit 1
  fi
}

main() {
  cd "$(git rev-parse --show-toplevel 2>/dev/null || pwd)" || die "not in a git repo"
  local cmd="${1:-}"
  shift || true
  case "$cmd" in
    capture) cmd_capture "$@" ;;
    diff)    cmd_diff "$@" ;;
    verify)  cmd_verify "$@" ;;
    *)
      echo "usage: $0 {capture|diff|verify} [SYMBOL]" >&2
      exit 2
      ;;
  esac
}

main "$@"
