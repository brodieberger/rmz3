@ Text for imported levels.

.if AP

.balign 4
.section .rodata

.global gApImportName0
gApImportName0:
	.string "Z2 CRYSTAL CAVE$"

.global gApImportStartText0
gApImportStartText0:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 CRYSTAL CAVE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.balign 4
.global gApImportStartTexts
gApImportStartTexts:
	.4byte gApImportStartText0

.endif
