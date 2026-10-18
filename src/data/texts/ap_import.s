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

.global TextOfs_ApImport
TextOfs_ApImport:
	.2byte (Text_ApImport_0-Text_ApImport)
	.2byte (Text_ApImport_1-Text_ApImport)
	.2byte (Text_ApImport_2-Text_ApImport)
	.2byte (Text_ApImport_3-Text_ApImport)
	.2byte (Text_ApImport_4-Text_ApImport)
	.2byte (Text_ApImport_5-Text_ApImport)

.global Text_ApImport
Text_ApImport:
Text_ApImport_0: @ 0x1400, Zero 2's 0xb00
	.string "{WINDOW 0x00}"
	.string "Ciel: This should be the▼"
	.string "meeting spot for our▼"
	.string "comrades.▼"
	.string "It's strange...▼"
	.string "No one has arrived...▼"
	.string "Zero... I've got a very▼"
	.string "bad feeling...$"
Text_ApImport_1: @ 0x1401, Zero 2's 0xb07
	.string "{WINDOW 0x00}"
	.string "Ciel: ... Zero. They are▼"
	.string "being controlled by▼"
	.string "something.▼"
	.string "Make sure you don't harm▼"
	.string "them… Zero.$"
Text_ApImport_2: @ 0x1402, Zero 2's 0xb03
	.string "{WINDOW 0x2D}"
	.string "That commander of\n"
	.string "yours seemed to have\n"
	.string "retrieved the IFF▼"
	.string "beacon... I wonder\n"
	.string "what he is up to...\n"
	.string "Why is he acting▼"
	.string "alone… breaking into\n"
	.string "Neo Arcadian\n"
	.string "facilities...?▼"
	.string "I don't understand\n"
	.string "the logic at all...▼"
	.string "Well… I don't really\n"
	.string "need to know...\n"
	.string "All those Inferior▼"
	.string "resistance behaviors\n"
	.string "are not all that\n"
	.string "different.▼"
	.string "Well Zero… it's\n"
	.string "time for you to\n"
	.string "die.$"
Text_ApImport_3: @ 0x1403, Zero 2's 0xb04
	.string "{WINDOW 0x2C}"
	.string "Are you serious?\n"
	.string "How can a legend\n"
	.string "die?$"
Text_ApImport_4: @ 0x1404, Zero 2's 0xb05
	.string "{WINDOW 0x2C}"
	.string "Ha ha ha... You are\n"
	.string "still so strong...\n"
	.string "I like it...▼"
	.string "No... I love it\n"
	.string "this way.\n"
	.string "You are the only▼"
	.string "one who can make\n"
	.string "me feel this\n"
	.string "alive... I enjoy▼"
	.string "the sensation… I\n"
	.string "love the pain...\n"
	.string "You are worthy...$"
Text_ApImport_5: @ 0x1405, Zero 2's 0xb06
	.string "{WINDOW 0x04}"
	.string "... ... ...▼"
	.string "Mission\n"
	.string "accomplished.\n"
	.string "Transfer me back.▼"
	.string "{WINDOW 0x62}"
	.string "Roger. Transfer\n"
	.string "commencing.$"

.endif
