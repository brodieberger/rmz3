.if AP

.balign 4
.section .rodata

@ Trap captions, in the inline message box.
.global gApTrapQuakeText
gApTrapQuakeText:
	.string "{RED}Earthquake!{RED_END}$"

.global gApTrapMosaicText
gApTrapMosaicText:
	.string "{RED}Pixelate!{RED_END}$"

.global gApTrapSlipText
gApTrapSlipText:
	.string "{RED}Slippery Floor!{RED_END}$"

.endif
