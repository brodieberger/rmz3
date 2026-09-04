# Installation

> [!NOTE]
> `rmz3` uses the same toolchain as [pret](https://github.com/pret), so follow [pret's INSTALL.md](https://github.com/pret/pokeemerald/blob/6eb688876d34d43096a276e690ae46b8853e03ac/INSTALL.md).

## Prerequisites

In addition to [pret's toolchain](https://github.com/pret/pokeemerald/blob/6eb688876d34d43096a276e690ae46b8853e03ac/INSTALL.md), `rmz3` requires the additional software.

- [Deno](https://deno.com/): Used as a build script.

## Installation

```sh
> git clone https://github.com/mmzret/rmz3

# install agbcc
> git clone https://github.com/pret/agbcc
> cd agbcc
> ./build.sh
> ./install.sh ../rmz3
> cd ../

# Build rmz3
> cd ./rmz3
> make
```

## Modern

There is a `modern` option to build using the latest C compiler instead of the original C compiler (agbcc).

> [!NOTE]
> Upstream documents this option as non-working, on the grounds that hardcoded addresses survive
> relocation. On this fork that is no longer the case: `modern` builds, links, boots and passes the
> headless smoke test in both regions. What was actually wrong was three build-system bugs, not the
> code -- see `docs/RESEARCH.md` in the parent repository. The assembly is symbolic (3,586 symbolic
> literal-pool entries against 14 raw addresses), so it relocates.

```sh
make modern              # JP
make modern REGION=us    # US
```

`REGION=us` under `modern` uses `ld_script-us-flat.ld`, which pins nothing -- gcc emits different
code sizes than agbcc, so the hand-ordered `ld_script-us.ld` layout cannot be reused.

## CBODY

`CBODY=1` keeps agbcc but compiles the C body of every `NON_MATCH` function instead of its assembly.
It does not byte-match and is not meant to: it exists so that `check_semantic.py` can compare agbcc
against agbcc, where every one of its metrics is exact.

```sh
make REGION=us CBODY=1
```
