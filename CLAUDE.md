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
`.decomp_cache/<symbol>.target.s`. If the permuter also plateaus without
reaching 100%, that's a signal the *structure* is still wrong somewhere
(wrong field width, missed inlining, an implicit memcpy) — re-examine the
diff for a structural cause rather than continuing to permute.

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