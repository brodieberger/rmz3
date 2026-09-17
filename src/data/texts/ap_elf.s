.if AP

.balign 4
.section .rodata

@ For the auto fuse option.
.global gApElfActiveText
gApElfActiveText:
	.string "{RED}Always on{RED_END}$"

.endif
