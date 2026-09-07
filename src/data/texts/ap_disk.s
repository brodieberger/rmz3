.if AP

.balign 4
.section .rodata

@ Cerveau's analysis screen new text. Mostly regarding the shop screen.

.global gApDiskOpenAllText
gApDiskOpenAllText:
	.string "Press SELECT to analyze all.$"

.global gApDiskOpenAllShopText
gApDiskOpenAllShopText:
	.string "SELECT: Read all.  L/R: Shop.$"

.global gApDiskShopHintText
gApDiskShopHintText:
	.string "Press L or R for the shop.$"

.global gApShopPromptText
gApShopPromptText:
	.string "A: Buy  L/R: Disks.$"

@ The right hand panel, printed at x 0x11. Thirteen characters of room.
.global gApShopEcText
gApShopEcText:
	.string "EC$"

.global gApShopBuyText
gApShopBuyText:
	.string "BUY$"

.global gApShopPoorText
gApShopPoorText:
	.string "NO EC$"

.global gApShopSlashText
gApShopSlashText:
	.string "/$"

.global gApShopSoldText
gApShopSoldText:
	.string "SOLD$"

.endif
