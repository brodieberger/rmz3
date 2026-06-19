# preproc

`pret/pokefirered` の カスタム`preproc`

この時代のGCCでは、文字列リテラルをUTF8以外でエンコーディングできないっぽいので、preprocで処理する必要がある

## Usage

**Build**

```sh
  make
```

```sh
Usage:
  preproc [OPTIONS] SRC_FILE CHARMAP_FILE

Arguments:
  SRC_FILE      is the source file to preprocess. 
                It must have a .s, .c, or .i extension. (.s for assembly, .c or .i for C)
  CHARMAP_FILE  is the charmap file that defines the mapping from characters to byte sequences. e.g. rmz3/charmap.txt

Options:
  -i denotes if input is from stdin
  -e enables enum handling (only for assembly sources (.s))
```
