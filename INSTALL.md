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

There is a `modern` option to build using the latest C compiler instead of the original C compiler (agbcc), but currently **THIS OPTION DOESN'T WORK**.
This is because some addresses are still hardcoded, and relocation causes them to function incorrectly.
