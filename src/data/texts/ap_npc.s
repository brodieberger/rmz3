.if AP

.balign 4
.section .rodata

@ New AP dialogue
.global gApCerveauAwayText
gApCerveauAwayText:
	.string "{WINDOW 0x6C}"
		.string "Oh, Cerveau?▼"
		.string "He's over in the\n"
		.string "maintenance room!▼"
		.string "Harpuia's in bad\n"
		.string "shape.$"

.endif
