@ Text for imported levels.

.if AP

.balign 4
.section .rodata

.global gApChainName
gApChainName:
	.string "CHAIN ROD$"

.global gApImportName0
gApImportName0:
	.string "Z2 SAND WILDERNESS$"

.global gApImportStartText0
gApImportStartText0:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 SAND WILDERNESS{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName1
gApImportName1:
	.string "Z2 FOREST OF DYSIS$"

.global gApImportStartText1
gApImportStartText1:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 FOREST OF DYSIS{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName2
gApImportName2:
	.string "Z2 RESIDENTIAL AREA$"

.global gApImportStartText2
gApImportStartText2:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 RESIDENTIAL AREA{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName3
gApImportName3:
	.string "Z2 CRYSTAL CAVE$"

.global gApImportStartText3
gApImportStartText3:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 CRYSTAL CAVE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName4
gApImportName4:
	.string "Z2 NEO ARCADIA TEMPLE$"

.global gApImportStartText4
gApImportStartText4:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 NEO ARCADIA TEMPLE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName5
gApImportName5:
	.string "Z2 TEMPLE OF FLAME$"

.global gApImportStartText5
gApImportStartText5:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 TEMPLE OF FLAME{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName6
gApImportName6:
	.string "Z2 TEMPLE OF ICE$"

.global gApImportStartText6
gApImportStartText6:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 TEMPLE OF ICE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.balign 4
.global gApImportStartTexts
gApImportStartTexts:
	.4byte gApImportStartText0
	.4byte gApImportStartText1
	.4byte gApImportStartText2
	.4byte gApImportStartText3
	.4byte gApImportStartText4
	.4byte gApImportStartText5
	.4byte gApImportStartText6

.global TextOfs_ApImport
TextOfs_ApImport:
	.2byte (Text_ApImport_0-Text_ApImport)
	.2byte (Text_ApImport_1-Text_ApImport)
	.2byte (Text_ApImport_2-Text_ApImport)
	.2byte (Text_ApImport_3-Text_ApImport)
	.2byte (Text_ApImport_4-Text_ApImport)
	.2byte (Text_ApImport_5-Text_ApImport)
	.2byte (Text_ApImport_6-Text_ApImport)
	.2byte (Text_ApImport_7-Text_ApImport)
	.2byte (Text_ApImport_8-Text_ApImport)
	.2byte (Text_ApImport_9-Text_ApImport)
	.2byte (Text_ApImport_10-Text_ApImport)
	.2byte (Text_ApImport_11-Text_ApImport)
	.2byte (Text_ApImport_12-Text_ApImport)
	.2byte (Text_ApImport_13-Text_ApImport)
	.2byte (Text_ApImport_14-Text_ApImport)
	.2byte (Text_ApImport_15-Text_ApImport)
	.2byte (Text_ApImport_16-Text_ApImport)
	.2byte (Text_ApImport_17-Text_ApImport)
	.2byte (Text_ApImport_18-Text_ApImport)
	.2byte (Text_ApImport_19-Text_ApImport)
	.2byte (Text_ApImport_20-Text_ApImport)
	.2byte (Text_ApImport_21-Text_ApImport)
	.2byte (Text_ApImport_22-Text_ApImport)
	.2byte (Text_ApImport_23-Text_ApImport)
	.2byte (Text_ApImport_24-Text_ApImport)
	.2byte (Text_ApImport_25-Text_ApImport)
	.2byte (Text_ApImport_26-Text_ApImport)
	.2byte (Text_ApImport_27-Text_ApImport)
	.2byte (Text_ApImport_28-Text_ApImport)
	.2byte (Text_ApImport_29-Text_ApImport)
	.2byte (Text_ApImport_30-Text_ApImport)
	.2byte (Text_ApImport_31-Text_ApImport)
	.2byte (Text_ApImport_32-Text_ApImport)
	.2byte (Text_ApImport_33-Text_ApImport)
	.2byte (Text_ApImport_34-Text_ApImport)
	.2byte (Text_ApImport_35-Text_ApImport)
	.2byte (Text_ApImport_36-Text_ApImport)
	.2byte (Text_ApImport_37-Text_ApImport)
	.2byte (Text_ApImport_38-Text_ApImport)
	.2byte (Text_ApImport_39-Text_ApImport)
	.2byte (Text_ApImport_40-Text_ApImport)

.global Text_ApImport
Text_ApImport:
Text_ApImport_0: @ 0x1400, Zero 2's 0x300
	.string "{WINDOW 0x04}"
	.string "Let's go...$"
Text_ApImport_1: @ 0x1401, Zero 2's 0x328
	.string "{WINDOW 0x04}"
	.string "This isn't fun\n"
	.string "anymore...$"
Text_ApImport_2: @ 0x1402, Zero 2's 0x301
	.string "{WINDOW 0x04}"
	.string "Somehow...\n"
	.string "I... I did it...▼"
	.string "But... It...▼"
	.string "It cost me\n"
	.string "everything...$"
Text_ApImport_3: @ 0x1403, Zero 2's 0x400
	.string "{WINDOW 0x00}"
	.string "Operator: The ruins are▼"
	.string "beyond this forest.▼"
	.string "Use the portable Trans▼"
	.string "Server and▼"
	.string "rescue the resistance▼"
	.string "soldiers who were lost.$"
Text_ApImport_4: @ 0x1404, Zero 2's 0x401
	.string "{WINDOW 0x85}"
	.string "Hiss! This is a\n"
	.string "restricted area,\n"
	.string "even for us Neo▼"
	.string "Arcadians... You\n"
	.string "will never leave\n"
	.string "here alive. Hiss!$"
Text_ApImport_5: @ 0x1405, Zero 2's 0x402
	.string "{WINDOW 0x84}"
	.string "No... If only that\n"
	.string "Baby Elf wasn't\n"
	.string "stolen...▼"
	.string "I could have easily\n"
	.string "destroyed the\n"
	.string "nameless soldier...▼"
	.string "Hissssss!$"
Text_ApImport_6: @ 0x1406, Zero 2's 0x403
	.string "{WINDOW 0x87}"
	.string "Thank you, Mr. Zero.\n"
	.string "The ruins are full\n"
	.string "of traps. Please▼"
	.string "be careful.$"
Text_ApImport_7: @ 0x1407, Zero 2's 0x404
	.string "{WINDOW 0x87}"
	.string "Thank you. I hope\n"
	.string "the others are\n"
	.string "fine.$"
Text_ApImport_8: @ 0x1408, Zero 2's 0x405
	.string "{WINDOW 0x86}"
	.string "Thank you so much...\n"
	.string "I went too far\n"
	.string "and got stuck...$"
Text_ApImport_9: @ 0x1409, Zero 2's 0x406
	.string "{WINDOW 0x86}"
	.string "I'm glad that you\n"
	.string "came here to help\n"
	.string "me.▼"
	.string "Thank you very\n"
	.string "much.$"
Text_ApImport_10: @ 0x140a, Zero 2's 0x407
	.string "{WINDOW 0x86}"
	.string "Thanks!! I almost\n"
	.string "lost hope of\n"
	.string "a rescue...$"
Text_ApImport_11: @ 0x140b, Zero 2's 0x408
	.string "{WINDOW 0x87}"
	.string "Commander sent us\n"
	.string "here to investigate\n"
	.string "something called a▼"
	.string "Baby Elf...\n"
	.string "But we encountered\n"
	.string "the Neo Arcadian▼"
	.string "army. My comrades\n"
	.string "are still somewhere\n"
	.string "in the forest.▼"
	.string "Please save them,\n"
	.string "Zero!$"
Text_ApImport_12: @ 0x140c, Zero 2's 0x409
	.string "{WINDOW 0x85}"
	.string "Give that back...▼"
	.string "And your life may\n"
	.string "be spared. Hiss!$"
Text_ApImport_13: @ 0x140d, Zero 2's 0x40a
	.string "{WINDOW 0x04}"
	.string "What are you waiting\n"
	.string "for...▼"
	.string "Run!$"
Text_ApImport_14: @ 0x140e, Zero 2's 0x40b
	.string "{WINDOW 0x35}"
	.string "It's been a long\n"
	.string "time...\n"
	.string "Zero...▼"
	.string "{WINDOW 0x04}"
	.string "X!▼"
	.string "{WINDOW 0x35}"
	.string "I can no longer\n"
	.string "rest...▼"
	.string "Both Baby\n"
	.string "Elves have\n"
	.string "awakened...▼"
	.string "The Baby Elves\n"
	.string "are still\n"
	.string "children...▼"
	.string "They cry for\n"
	.string "their mother as\n"
	.string "they tremble▼"
	.string "from the\n"
	.string "loneliness.▼"
	.string "{WINDOW 0x04}"
	.string "... ... ...\n"
	.string "What's your point,\n"
	.string "X?$"
Text_ApImport_15: @ 0x140f, Zero 2's 0x40c
	.string "{WINDOW 0x35}"
	.string "The Baby Elves will\n"
	.string "do anything to\n"
	.string "reunite with▼"
	.string "their mother.▼"
	.string "Stir the humans'\n"
	.string "minds and bring\n"
	.string "chaos...▼"
	.string "It's all to meet\n"
	.string "their mother,\n"
	.string "the Dark Elf....▼"
	.string "The Dark Elf\n"
	.string "that I sealed...$"
Text_ApImport_16: @ 0x1410, Zero 2's 0x40d
	.string "{WINDOW 0x04}"
	.string "Wait, X!▼"
	.string "... ... ...▼"
	.string "The Dark Elf...$"
Text_ApImport_17: @ 0x1411, Zero 2's 0xe00
	.string "{WINDOW 0x2F}"
	.string "Why are you so\n"
	.string "late, Zero?▼"
	.string "I was so bored that\n"
	.string "we had to retire\n"
	.string "all the resistance▼"
	.string "soldiers to pass\n"
	.string "the time... All\n"
	.string "that remains is▼"
	.string "only this inferior\n"
	.string "ex-Neo Arcadia\n"
	.string "citizen.$"
Text_ApImport_18: @ 0x1412, Zero 2's 0xe01
	.string "{WINDOW 0x31}"
	.string "Zero, I've been\n"
	.string "waiting for you\n"
	.string "too long.▼"
	.string "They were too weak\n"
	.string "to have fun with...\n"
	.string "I have wanted to▼"
	.string "face you. Why don't\n"
	.string "we have fun\n"
	.string "together!!$"
Text_ApImport_19: @ 0x1413, Zero 2's 0xe02
	.string "{WINDOW 0x2D}"
	.string "Stop!$"
Text_ApImport_20: @ 0x1414, Zero 2's 0xe03
	.string "{WINDOW 0x31}"
	.string "Wha...!$"
Text_ApImport_21: @ 0x1415, Zero 2's 0xe04
	.string "{WINDOW 0x2D}"
	.string "... ... ...▼"
	.string "Did you come to\n"
	.string "rescue this\n"
	.string "Reploid, Zero?▼"
	.string "{WINDOW 0x04}"
	.string "... Yeah.▼"
	.string "{WINDOW 0x2D}"
	.string "Why do you bother?\n"
	.string "Even if you help\n"
	.string "him, he won't▼"
	.string "thank you. And...\n"
	.string "If he lives, even\n"
	.string "more resistance▼"
	.string "soldiers are going\n"
	.string "to die.$"
Text_ApImport_22: @ 0x1416, Zero 2's 0xe05
	.string "{WINDOW 0x04}"
	.string "I'll save this\n"
	.string "Reploid... And I\n"
	.string "won't let anymore▼"
	.string "resistance soldiers\n"
	.string "Die.▼"
	.string "{WINDOW 0x2D}"
	.string "How greedy...\n"
	.string "But can you\n"
	.string "really do that▼"
	.string "by yourself?$"
Text_ApImport_23: @ 0x1417, Zero 2's 0xe06
	.string "{WINDOW 0x00}"
	.string "Operator: Emergency call▼"
	.string "for Zero!▼"
	.string "An unidentified object is▼"
	.string "rapidly flying toward the▼"
	.string "Resistance Base.▼"
	.string "Return to base immediately!$"
Text_ApImport_24: @ 0x1418, Zero 2's 0xe07
	.string "{WINDOW 0x2F}"
	.string "Ooh. Can you hear\n"
	.string "it? A bombardment\n"
	.string "aircraft is heading▼"
	.string "for your base with\n"
	.string "a special bomb.$"
Text_ApImport_25: @ 0x1419, Zero 2's 0xe08
	.string "{WINDOW 0x31}"
	.string "Using bombs is not\n"
	.string "my style. But all\n"
	.string "is fair in love▼"
	.string "and war...▼"
	.string "{WINDOW 0x2D}"
	.string "Your resistance\n"
	.string "forces have made\n"
	.string "a mistake that▼"
	.string "can't be forgiven.\n"
	.string "Neo Arcadia, or\n"
	.string "should I say, human▼"
	.string "society is not a\n"
	.string "thing that Reploids\n"
	.string "can rebel against.▼"
	.string "If they do, they\n"
	.string "should be\n"
	.string "exterminated...▼"
	.string "{WINDOW 0x04}"
	.string "Operator! Transfer\n"
	.string "us back to the\n"
	.string "base!$"
Text_ApImport_26: @ 0x141a, Zero 2's 0xe09
	.string "{WINDOW 0x00}"
	.string "Operator: Roger...▼"
	.string "Transfer commencing.$"
Text_ApImport_27: @ 0x141b, Zero 2's 0xe0a
	.string "{WINDOW 0x2D}"
	.string "Zero...▼"
	.string "I don't think that\n"
	.string "justice is\n"
	.string "destroying▼"
	.string "resistance forces.\n"
	.string "But, as long as\n"
	.string "they try to disobey▼"
	.string "humans, destroying\n"
	.string "them is my goal.$"
Text_ApImport_28: @ 0x141c, Zero 2's 0xb00
	.string "{WINDOW 0x00}"
	.string "Ciel: This should be the▼"
	.string "meeting spot for our▼"
	.string "comrades.▼"
	.string "It's strange...▼"
	.string "No one has arrived...▼"
	.string "Zero... I've got a very▼"
	.string "bad feeling...$"
Text_ApImport_29: @ 0x141d, Zero 2's 0xb07
	.string "{WINDOW 0x00}"
	.string "Ciel: ... Zero! They are▼"
	.string "being controlled by▼"
	.string "something!▼"
	.string "Make sure you don't harm▼"
	.string "them, Zero.$"
Text_ApImport_30: @ 0x141e, Zero 2's 0xb03
	.string "{WINDOW 0x2D}"
	.string "That commander of\n"
	.string "yours seemed to have\n"
	.string "retrieved the IFF▼"
	.string "beacon... I wonder\n"
	.string "what he is up to...\n"
	.string "Why is he acting▼"
	.string "alone, breaking into\n"
	.string "Neo Arcadian\n"
	.string "facilities...?▼"
	.string "I don't understand\n"
	.string "the logic at all...▼"
	.string "Well, I don't really\n"
	.string "need to know...\n"
	.string "All those Inferior▼"
	.string "resistance behaviors\n"
	.string "are not all that\n"
	.string "different.▼"
	.string "Well Zero, it's\n"
	.string "time for you to\n"
	.string "die!$"
Text_ApImport_31: @ 0x141f, Zero 2's 0xb04
	.string "{WINDOW 0x2C}"
	.string "Are you serious?\n"
	.string "How can a legend\n"
	.string "die?$"
Text_ApImport_32: @ 0x1420, Zero 2's 0xb05
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
	.string "the sensation, I\n"
	.string "love the pain...\n"
	.string "You are worthy...$"
Text_ApImport_33: @ 0x1421, Zero 2's 0xb06
	.string "{WINDOW 0x04}"
	.string "... ... ...▼"
	.string "Mission\n"
	.string "accomplished.\n"
	.string "Transfer me back.▼"
	.string "{WINDOW 0x62}"
	.string "Roger. Transfer\n"
	.string "commencing.$"
Text_ApImport_34: @ 0x1422, Zero 2's 0xd00
	.string "{WINDOW 0x00}"
	.string "Ciel: I've set a▼"
	.string "coordinate axis...▼"
	.string "Now you can return here▼"
	.string "anytime you want...▼"
	.string "So please return to the▼"
	.string "base once,▼"
	.string "before you go any further.▼"
	.string "Please... Zero.$"
Text_ApImport_35: @ 0x1423, Zero 2's 0xf01
	.string "{WINDOW 0x31}"
	.string "Hey, Zero!▼"
	.string "You came along to\n"
	.string "get Elpizo?\n"
	.string "I know you did!▼"
	.string "He is crazy about\n"
	.string "the Dark Elf.\n"
	.string "Leave that guy to▼"
	.string "Harpuia and have\n"
	.string "fun with me\n"
	.string "instead!!▼"
	.string "Iiieyahh!\n"
	.string "Get ready for a\n"
	.string "fight!$"
Text_ApImport_36: @ 0x1424, Zero 2's 0xf02
	.string "{WINDOW 0x31}"
	.string "Ngwooooohhh!!▼"
	.string "What's the problem!▼"
	.string "Even though I had\n"
	.string "powered up, I'm no\n"
	.string "match for you!▼"
	.string "I... I won't give\n"
	.string "up...▼"
	.string "Someday... I will\n"
	.string "destroy you for\n"
	.string "sure!!!▼"
	.string "Just you wait!$"
Text_ApImport_37: @ 0x1425, Zero 2's 0xf03
	.string "{WINDOW 0x00}"
	.string "Ciel: I've set a▼"
	.string "coordinate axis...▼"
	.string "Now you can return here▼"
	.string "anytime you want...▼"
	.string "So please return to the▼"
	.string "base once. Please... Zero.$"
Text_ApImport_38: @ 0x1426, Zero 2's 0x1001
	.string "{WINDOW 0x2F}"
	.string "{BOTTOM}"
	.string "Fu fu...\n"
	.string "I'm waiting for\n"
	.string "you, Zero.▼"
	.string "I guess Fefnir's\n"
	.string "disease infected\n"
	.string "me.▼"
	.string "Once I start\n"
	.string "thinking of you...\n"
	.string "I stop caring about▼"
	.string "the Dark Elf...▼"
	.string "Even if the world\n"
	.string "dies, I will be\n"
	.string "happy as long▼"
	.string "as I can defeat\n"
	.string "you.▼"
	.string "Now, let's battle!$"
Text_ApImport_39: @ 0x1427, Zero 2's 0x1002
	.string "{WINDOW 0x2E}"
	.string "Huh huh huh...▼"
	.string "I'm getting worse\n"
	.string "than ever...▼"
	.string "The only thing I\n"
	.string "can take seriously\n"
	.string "is...▼"
	.string "Fighting with you.▼"
	.string "But... I'm happy.▼"
	.string "I'll keep going...▼"
	.string "Dreaming that I\n"
	.string "can destroy you\n"
	.string "someday...▼"
	.string "See you... soon...$"
Text_ApImport_40: @ 0x1428, Zero 2's 0x1003
	.string "{WINDOW 0x00}"
	.string "Ciel: I've set a▼"
	.string "coordinate axis...▼"
	.string "Now you can return here▼"
	.string "anytime you want...▼"
	.string "So please return to the▼"
	.string "base once. Please... Zero.$"

.endif
