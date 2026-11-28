# Vanilla C reaches these tables by number to byte-match.
# Rewrites agbcc's pool words into each table as symbol+offset, so the table can move.

function hex(s,    i, v) {
  s = tolower(substr(s, 3))
  v = 0
  for (i = 1; i <= length(s); i++)
    v = v * 16 + index("0123456789abcdef", substr(s, i, 1)) - 1
  return v
}

BEGIN {
  n = split("gBgMapOffsets 0x085222a0 gBgGraphics 0x08547280 gDialogGraphics 0x085a7ec4 " \
            "gStaticMotionGraphics 0x085d78f8 gStageTilesetOffsets 0x087044b0", t, " ")
  for (i = 1; i <= n; i += 2) {
    sym[i] = t[i]
    base[i] = hex(t[i + 1])
  }
}

$1 == ".word" && $2 ~ /^0x8[0-9a-f]+$/ {
  v = hex($2)
  for (i = 1; i <= n; i += 2) {
    if (v >= base[i] && v < base[i] + 0x1000) {
      print "\t.word\t" sym[i] "+" (v - base[i])
      next
    }
  }
}

{ print }
