    .ifndef GUARD_MACROS_GFX_INC
    .set GUARD_MACROS_GFX_INC, 1

    @ Graphic.props
    .equiv MAP2D,   (1 << 0)
    .equiv LZ77,    (1 << 1)
    .equiv NO_PAL,  (1 << 2)
    .equiv BPP4,    (1 << 5)
    .equiv BPP8,    (1 << 6)

    .endif // GUARD_MACROS_ENUM_INC
