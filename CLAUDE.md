# rmz3 decompilation — working notes for Claude Code

This is a pret-style decompilation of Mega Man Zero 3 (GBA, Japan). The
project currently builds and matches the original ROM byte-for-byte
(`make compare` passes). The task is converting remaining **naked**
functions — currently compiled from literal embedded/included assembly —
into equivalent C that agbcc compiles to the *exact same bytes*.

Read this whole file before touching any function.

## How naked functions are marked

Three states, defined in `include/gba/defines.h`:

- `NAKED` — pure `__attribute__((naked))`. Body is either an inline
  `asm("...")` block, or `INCCODE("asm/wip/FUN_xxxxxxxx.inc")` /
  `INCCODE("asm/unused/...")` pulling in a separate disassembly file.
  This is the main target for conversion.
- `NON_MATCH` — real C already exists and is believed *logically* correct,
  but doesn't compile to matching bytes (usually register allocation).
  Compiles as normal C under `MODERN=1`, falls back to naked asm otherwise
  (see the `#if MODERN ... #else ... INCCODE(...) #endif` pattern). These
  are good targets too — the hard "figure out the logic" work is already
  done; what's left is regalloc/instruction-order massaging, which is
  exactly what decomp-permuter is for.
- `WIP` — naked in both builds; logic not yet worked out at all. Leave
  these for later unless specifically asked.

Function names frequently embed their ROM address directly, e.g.
`FUN_08005a70` lives at `0x08005a70`. Not universal (some functions have
been given real names already) — don't rely on parsing the name, use `nm`
against the built ELF for the authoritative address.

## The check script — use this, don't hand-roll objdump/diff commands

`tools/decomp/check.sh` is the loop. It uses the **current build's own
ELF as ground truth** (valid because the project matches today), so there's
no need to touch `baserom.gba` directly or reason about thumb/arm
disassembly modes — `objdump` on the linked ELF already gets that right.

```sh
# BEFORE editing a function, capture its current (correct) disassembly:
tools/decomp/check.sh capture FUN_08005a70

# ... edit the .c file, replace the NAKED block with real C ...

# Check as often as needed while iterating:
tools/decomp/check.sh diff FUN_08005a70
# exit 0 = exact match, prints diff. exit 1 = mismatch, diff + rough % shown.
# exit 2 = build failed, compiler errors printed — fix syntax first.

# Once diff reports an exact match, confirm nothing else regressed:
tools/decomp/check.sh verify
```

**Always run `capture` before making any edit**, even if you think you'll
get it right first try. Without a captured baseline there's no diff target.

**Only work on the function the user explicitly names.** Don't pick a
different function, move on to a related one, or start "cleaning up"
nearby code without being asked — even if it looks trivial. One target
function per session unless told otherwise.

**Within that one function, iterate autonomously.** Don't stop at the
first `diff` failure and ask for guidance — read the diff, adjust the C,
rebuild, recheck. Only surface back to the user when: (a) you've hit an
exact match, (b) you've plateaued above ~85-90% for several attempts with
no clear next move (this is the signal to reach for decomp-permuter, see
below), or (c) the logic itself seems wrong, not just the instruction
encoding.

## agbcc quirks (gcc 2.95-era, GBA thumb/arm-interwork target)

agbcc is old and its codegen is brittle in ways modern gcc isn't. These
are the biggest sources of "logically identical but bytes don't match":

- **Local variable declaration order drives register allocation.**
  agbcc tends to assign registers in roughly the order locals are first
  declared/used. If your diff shows the right instructions but with
  registers swapped (e.g. r4/r5 transposed throughout), try reordering
  the declarations — don't rewrite the logic.
- **Loop shape matters.** `do { } while()` vs `while() { }` vs `for()`
  generate different branch layouts even for equivalent logic. The
  original compiler's preference generally shows up as a trailing
  conditional branch back to the top — if your diff shows an extra
  unconditional branch at loop entry that the target doesn't have, try
  `do-while`.
- **Avoid implying `memcpy` for small struct/array copies.** agbcc's
  `memcpy` calls look very different from its inline copy codegen. Prefer
  direct member-by-member assignment or a precomputed pointer + manual
  copy loop when the target shows inlined load/store pairs instead of a
  `bl memcpy`.
- **Struct member chains can emit extra loads.** `p->foo.bar.baz` accessed
  repeatedly may reload `p->foo.bar`'s address each time. If the target
  computes a sub-struct pointer once and reuses it, cache it in a local
  (`struct Bar *b = &p->foo.bar;`) rather than re-chaining.
- **Ternary vs if/else are not interchangeable in output.** If the target
  disassembly shows two separate stores with a branch (not conditional
  move-like folding), write it as if/else; agbcc's ternary codegen differs.
- **`-fshort-enums` is active** — enum-typed fields are as small as they
  fit, matches original struct layouts. Don't "fix" a `u8`/`s8` enum field
  to `int` even if it looks safer.
- **Compile flags in use (vanilla, non-modern):**
  `-mthumb-interwork -Wimplicit -Wparentheses -Werror -O2 -fshort-enums -fhex-asm`
- **Repeated writes through a struct's pointer field can need asymmetric
  caching.** For `X.ptrField[idx] |= a; X.ptrField[idx] |= b;` (same
  computed index, same field, used twice), agbcc may schedule the field
  *read* before the *index* is computed, even though the two are
  independent — cache the field into a local pointer in its own statement
  placed *before* computing the index (`u8* p = X.ptrField; idx = ...;
  *(p + idx) |= a;`). The caching may need to apply to only the **first**
  occurrence — a second, seemingly-identical occurrence right after can
  need to re-read `X.ptrField` directly rather than reusing the cached
  local. Don't assume the two occurrences must be written symmetrically;
  try the asymmetric version if the symmetric one doesn't match. See the
  `unlockAllSecretDisk` worked example below.

## Getting started on a function

Tell Claude Code the specific function to work on by name, e.g.:

> "Convert FUN_08005a70 in src/overworld_layer.c to matching C"

If you're not sure where a naked function's assembly lives, it's either
an inline `asm()` block right in the `.c` file, or referenced via
`INCCODE("asm/wip/...")` / `INCCODE("asm/unused/...")` — the source file
will show which.

Good candidates when you're picking manually:

- `asm/unused/*.inc` — dead code, no callers to worry about breaking,
  usually short. Fine warm-up targets.
- Existing `NON_MATCH` functions in `src/` — the logic is already
  written and believed correct, so this is pure regalloc massaging,
  prime decomp-permuter territory (see below).
- Smaller files in `asm/wip/*.inc` before larger ones — check line count
  first.
- Larger `NAKED` functions with inline `asm()` blocks (state machines,
  boss/enemy AI) — these take longest, tackle once the workflow feels
  solid on smaller ones.

## When stuck above ~90%: decomp-permuter

If `check.sh diff` plateaus — same handful of instructions off across
several manual attempts — stop hand-editing and run decomp-permuter on the
candidate. It randomly mutates declaration order, expression shape, and
temporaries, keeping anything that improves the match score, and is
specifically good at exactly the regalloc problems agbcc causes. Feed it
your current best-effort C plus the captured target from
`.decomp_cache/<symbol>.target.s`.

**If permuter *also* plateaus with zero improvement over many thousands of
iterations** (not just your manual attempts), treat that as a stronger
signal than "run it longer": it usually means the *statement-level
structure* is still wrong (an instruction-order bug, not just register
noise), and undirected random mutation is unlikely to discover an entirely
new structural pattern (like an asymmetric caching trick — see the agbcc
quirks list above) from scratch within a reasonable budget. What actually
works in that situation:
1. Go back to the raw target disassembly and look for something genuinely
   *independent-but-reordered* (two instructions with no data dependency
   on each other, emitted in a different order than your candidate) — not
   just swapped registers. That's the real bug.
2. Fix that one structural thing by hand. The match % can look *worse*
   immediately after — register-allocation noise can now dominate the
   score once the structural bug is gone, which is fine.
3. **Re-run permuter against the corrected structure.** A search that
   plateaued for 80,000+ iterations against the wrong structure can find
   an exact match in a few hundred once the structure is right — pure
   register-allocation noise is exactly what permuter is good at, it just
   can't get there if the fundamental shape is still wrong.

Don't expect Ghidra's decompilation to hand you the fix here either — it's
a **sanity check on logic and real symbol names, not a structural
template.** Applying Ghidra's literal pseudo-C shape (e.g. exactly where
it inserts a temp variable, or `do-while` vs `for`) can make the match
*worse*, since Ghidra reconstructs code for human readability, not to
preserve the statement-level shape that controls instruction scheduling.
Use it to confirm the logic and cross-check field/global names against
real headers — but verify any *structural* hint by actually testing it.

### Setting up decomp-permuter for this project

This repo doesn't use the `GLOBAL_ASM` convention `import.py` expects, so
its automatic setup won't work — build the permuter directory by hand:

- **Don't feed it the real project `.c` file as `base.c`.** `pycparser`
  (which permuter uses to parse/mutate C) chokes on some GNU attribute
  syntax used elsewhere in this project's real header graph, and it'll
  fail on the whole file even though the offending syntax is unrelated to
  your function. Instead hand-write a minimal, self-contained `base.c`:
  just the typedefs/struct/macros/extern decls your one function actually
  needs, with **no** `#include` of project headers at all.
- **Don't point `target.o` at the real built object file either.**
  Permuter's scorer disassembles the *entire* `.o` with no symbol
  filtering, so a multi-function object (e.g. a whole `.c` file's `.o`)
  gets compared against nonsense from unrelated functions. Instead extract
  just the target function's original assembly (from the `NAKED` block or
  `.inc` file) into its own `.s` with `.thumb_func` / `.global <funcname>`
  directives, and assemble that alone:
  `arm-none-eabi-as -mcpu=arm7tdmi -march=armv4t -mthumb -mthumb-interwork -g target.s -o target.o`
- `compile.sh` just needs to replicate this project's real
  preprocess+agbcc+assemble pipeline (see the vanilla compile flags
  above). Permuter calls it as `compile.sh <c_file> -o <o_file>`
  (`$1`/`$3`).
- The mainline `simonlindholm/decomp-permuter` is sufficient — no need to
  chase ARM- or agbcc-named forks. Every fork drives the same `agbcc`
  binary this project already has; only the search algorithm differs, and
  it's the input (a structurally-correct candidate) that matters most.

## Worked examples

### DiskLoop_Exit — `DiskLoop_BlackOut` caller

Target disassembly:

```asm
	thumb_func_start DiskLoop_Exit
DiskLoop_Exit: @ 0x080F8368
	push {r4, lr}
	adds r4, r0, #0
	movs r0, #0x40
	bl ClearBlink
	ldr r2, _080F8398 @ =gWindowRegBuffer
	ldrh r1, [r2]
	ldr r0, _080F839C @ =0x0000DFFF
	ands r0, r1
	movs r1, #0
	strh r0, [r2]
	ldr r0, _080F83A0 @ =gPaletteManager
	strh r1, [r0]
	ldr r0, _080F83A4 @ =0x00000DCC
	adds r1, r4, r0
	movs r0, #1
	strb r0, [r1, #0xd]
	ldr r1, _080F83A8 @ =0x05030400
	adds r0, r4, #0
	bl SetGameMode
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080F8398: .4byte gWindowRegBuffer
_080F839C: .4byte 0x0000DFFF
_080F83A0: .4byte gPaletteManager
_080F83A4: .4byte 0x00000DCC
_080F83A8: .4byte 0x05030400
```

Matching C:

```c
static void DiskLoop_Exit(struct GameState* g) {
  u8* s;
  RemovePaletteAnimation(64);
  gWindowRegBuffer.dispcnt &= ~DISPCNT_WIN0_ON;
  PALETTE16(0) = 0;
  s = (u8*)&(g->sceneState).menu;
  s[13] = 1;
  SetGameMode(g, GAMEMODE(MAINGAME, OVERWORLD, 3, 5));
}
```

### unlockAllSecretDisk — asymmetric pointer-field caching

Target disassembly (loop body only — this is the part that resisted a
dozen+ manual attempts and 84,000+ permuter iterations before the
structural bug below was found):

```asm
_080F8C3C:
	ldr r2, [r6]        @ r6 = &gStageDiskManager (cached before the loop)
	lsrs r4, r5, #2     @ r5 = loop counter i
	adds r2, r2, r4
	adds r3, r5, #0
	ands r3, r7          @ r7 = 3 (cached before the loop)
	movs r0, #1
	lsls r0, r3
	ldrb r1, [r2]
	orrs r0, r1
	strb r0, [r2]
	ldr r2, [r6]         @ re-read the field — NOT reusing a cached pointer
	adds r2, r2, r4
	movs r0, #0x10
	lsls r0, r3
	ldrb r1, [r2]
	orrs r0, r1
	strb r0, [r2]
	adds r0, r5, #1
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	cmp r5, #0xb3
	bls _080F8C3C
```

Matching C:

```c
void unlockAllSecretDisk(u8* flagbits) {
  u8* base;
  u8 i;
  u8 shift;
  gStageDiskManager.disk = flagbits;
  _CpuFastFill(0, flagbits, 32);
  CpuFill32(0, flagbits + 0x20, 16);
  i = 0;
  do {
    base = gStageDiskManager.disk;
    shift = i >> 2;
    *(base + shift) |= (1 << (i & 3));
    *(gStageDiskManager.disk + shift) |= (0x10 << (i & 3));
    i = (i + 1) & 0xff;
  } while (i < DISK_COUNT);
  clearStageDisk();
}
```

The key details, in order of how hard they were to find:

1. `ldr` (read `gStageDiskManager.disk`) had to be scheduled *before*
   `lsrs` (compute `i >> 2`), even though the two have no data dependency
   on each other. Every phrasing that computed the index first — a `for`
   loop, `for` with the index inlined, `for` with the index in its own
   local, flipping the operand order in the pointer addition — produced
   the same wrong order regardless. What fixed it: assigning
   `gStageDiskManager.disk` to a local pointer (`base`) in its **own
   statement**, placed textually before the shift is computed.
2. That fix alone left the right instructions in the wrong registers (a
   pure 3-register rotation) — declaration order and loop shape
   (`do-while` vs `for`) made zero difference across 6+ tries.
   Re-running decomp-permuter against this *now-structurally-correct*
   candidate found the exact register assignment in 291 iterations.
3. The permuter's winning candidate revealed the asymmetry: `base` is
   only reused for the **first** `|=`; the second one re-reads
   `gStageDiskManager.disk` directly rather than reusing `base`. Writing
   both occurrences the same way (both through `base`, or both inlined)
   never matched — only the asymmetric version did.