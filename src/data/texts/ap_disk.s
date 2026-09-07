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
.global gApShopTitleText
gApShopTitleText:
	.string "SHOP$"

.global gApShopSlotText
gApShopSlotText:
	.string "SLOT$"

.global gApShopCostText
gApShopCostText:
	.string "COST$"

.global gApShopHaveText
gApShopHaveText:
	.string "HAVE$"

.global gApShopSlashText
gApShopSlashText:
	.string "/$"

.global gApShopSoldText
gApShopSoldText:
	.string "SOLD$"

.endif
