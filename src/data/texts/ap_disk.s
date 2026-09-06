.if AP

.balign 4
.section .rodata

@ "Press A BUTTON to analyze." prompt. Shown only while some owned disk is unread.
.global gApDiskOpenAllText
gApDiskOpenAllText:
	.string "Press SELECT to analyze all.$"

.endif
