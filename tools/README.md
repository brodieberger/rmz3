# `/tools`

To use the script, ROM file must be placed in the root as `rmz3/baserom.gba`.

Scripts require Deno runtime installation.

```sh
rmz3/tools
      ├── common        # Common subroutine for /dev, /dumper, /misc
      ├── dev           # This directory contains the build scripts used when building rmz3.gba.
      ├── dumper        # This directory contains data dumpers for decompilation work.
      ├── scaninc       # from pret, see tools/scaninc/README.md
      ├── gbagfx        # from pret, see tools/gbagfx/README.md
      ├── preproc       # from pret, see tools/preproc/README.md
      ├── mid2agb       # from pret, midi音源をGBA用のアセンブリコードに変換するプログラム
      ├── misc          # Misc scripts useful for Decomp
      ├── sprite_editor # Paint Zero's animations in the browser, see tools/sprite_editor/README.md
      └── rom_addresses.awk  # Lets the byte-matching builds' hardcoded table addresses follow moved data
```
