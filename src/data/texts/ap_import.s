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
	.string "Z2 COMPUTER ZONE$"

.global gApImportStartText1
gApImportStartText1:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 COMPUTER ZONE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName2
gApImportName2:
	.string "Z2 TRAIN$"

.global gApImportStartText2
gApImportStartText2:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 TRAIN{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName3
gApImportName3:
	.string "Z2 POWER ROOM$"

.global gApImportStartText3
gApImportStartText3:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 POWER ROOM{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName4
gApImportName4:
	.string "Z2 FOREST OF DYSIS$"

.global gApImportStartText4
gApImportStartText4:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 FOREST OF DYSIS{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName5
gApImportName5:
	.string "Z2 RESIDENTIAL AREA$"

.global gApImportStartText5
gApImportStartText5:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 RESIDENTIAL AREA{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName6
gApImportName6:
	.string "Z2 BOMBARDMENT AIRCRAFT$"

.global gApImportStartText6
gApImportStartText6:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 BOMBARDMENT AIRCRAFT{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName7
gApImportName7:
	.string "Z2 FOREST OF NOTUS$"

.global gApImportStartText7
gApImportStartText7:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 FOREST OF NOTUS{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName8
gApImportName8:
	.string "Z2 COMPUTER ZONE 2$"

.global gApImportStartText8
gApImportStartText8:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 COMPUTER ZONE 2{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName9
gApImportName9:
	.string "Z2 CRYSTAL CAVE$"

.global gApImportStartText9
gApImportStartText9:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 CRYSTAL CAVE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName10
gApImportName10:
	.string "Z2 SHUTTLE FACTORY$"

.global gApImportStartText10
gApImportStartText10:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 SHUTTLE FACTORY{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName11
gApImportName11:
	.string "Z2 NEO ARCADIA TEMPLE$"

.global gApImportStartText11
gApImportStartText11:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 NEO ARCADIA TEMPLE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName12
gApImportName12:
	.string "Z2 TEMPLE OF FLAME$"

.global gApImportStartText12
gApImportStartText12:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 TEMPLE OF FLAME{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName13
gApImportName13:
	.string "Z2 TEMPLE OF ICE$"

.global gApImportStartText13
gApImportStartText13:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 TEMPLE OF ICE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.global gApImportName14
gApImportName14:
	.string "Z2 TEMPLE OF WIND$"

.global gApImportStartText14
gApImportStartText14:
	.string "{WINDOW 0x62}"
		.string "{RED}Z2 TEMPLE OF WIND{RED_END}?\n"
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
	.4byte gApImportStartText7
	.4byte gApImportStartText8
	.4byte gApImportStartText9
	.4byte gApImportStartText10
	.4byte gApImportStartText11
	.4byte gApImportStartText12
	.4byte gApImportStartText13
	.4byte gApImportStartText14

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
	.2byte (Text_ApImport_41-Text_ApImport)
	.2byte (Text_ApImport_42-Text_ApImport)
	.2byte (Text_ApImport_43-Text_ApImport)
	.2byte (Text_ApImport_44-Text_ApImport)
	.2byte (Text_ApImport_45-Text_ApImport)
	.2byte (Text_ApImport_46-Text_ApImport)
	.2byte (Text_ApImport_47-Text_ApImport)
	.2byte (Text_ApImport_48-Text_ApImport)
	.2byte (Text_ApImport_49-Text_ApImport)
	.2byte (Text_ApImport_50-Text_ApImport)
	.2byte (Text_ApImport_51-Text_ApImport)
	.2byte (Text_ApImport_52-Text_ApImport)
	.2byte (Text_ApImport_53-Text_ApImport)
	.2byte (Text_ApImport_54-Text_ApImport)
	.2byte (Text_ApImport_55-Text_ApImport)
	.2byte (Text_ApImport_56-Text_ApImport)
	.2byte (Text_ApImport_57-Text_ApImport)
	.2byte (Text_ApImport_58-Text_ApImport)
	.2byte (Text_ApImport_59-Text_ApImport)
	.2byte (Text_ApImport_60-Text_ApImport)
	.2byte (Text_ApImport_61-Text_ApImport)
	.2byte (Text_ApImport_62-Text_ApImport)
	.2byte (Text_ApImport_63-Text_ApImport)
	.2byte (Text_ApImport_64-Text_ApImport)
	.2byte (Text_ApImport_65-Text_ApImport)
	.2byte (Text_ApImport_66-Text_ApImport)
	.2byte (Text_ApImport_67-Text_ApImport)
	.2byte (Text_ApImport_68-Text_ApImport)
	.2byte (Text_ApImport_69-Text_ApImport)
	.2byte (Text_ApImport_70-Text_ApImport)
	.2byte (Text_ApImport_71-Text_ApImport)
	.2byte (Text_ApImport_72-Text_ApImport)
	.2byte (Text_ApImport_73-Text_ApImport)
	.2byte (Text_ApImport_74-Text_ApImport)
	.2byte (Text_ApImport_75-Text_ApImport)
	.2byte (Text_ApImport_76-Text_ApImport)
	.2byte (Text_ApImport_77-Text_ApImport)
	.2byte (Text_ApImport_78-Text_ApImport)
	.2byte (Text_ApImport_79-Text_ApImport)
	.2byte (Text_ApImport_80-Text_ApImport)
	.2byte (Text_ApImport_81-Text_ApImport)
	.2byte (Text_ApImport_82-Text_ApImport)
	.2byte (Text_ApImport_83-Text_ApImport)
	.2byte (Text_ApImport_84-Text_ApImport)
	.2byte (Text_ApImport_85-Text_ApImport)
	.2byte (Text_ApImport_86-Text_ApImport)
	.2byte (Text_ApImport_87-Text_ApImport)
	.2byte (Text_ApImport_88-Text_ApImport)
	.2byte (Text_ApImport_89-Text_ApImport)
	.2byte (Text_ApImport_90-Text_ApImport)
	.2byte (Text_ApImport_91-Text_ApImport)
	.2byte (Text_ApImport_92-Text_ApImport)
	.2byte (Text_ApImport_93-Text_ApImport)
	.2byte (Text_ApImport_94-Text_ApImport)
	.2byte (Text_ApImport_95-Text_ApImport)

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
Text_ApImport_3: @ 0x1403, Zero 2's 0x500
	.string "{WINDOW 0x00}"
	.string "Operator: There are four▼"
	.string "cooling systems▼"
	.string "for the computer room of▼"
	.string "the facility.▼"
	.string "Once you destroy all of▼"
	.string "the systems,▼"
	.string "the abilities of the▼"
	.string "computer room will be▼"
	.string "weakened.$"
Text_ApImport_4: @ 0x1404, Zero 2's 0x501
	.string "{WINDOW 0x89}"
	.string "Bwooooh! You are\n"
	.string "the one!?▼"
	.string "You are trying to\n"
	.string "destroy this and\n"
	.string "confuse us!▼"
	.string "Bwooooh! I won't let\n"
	.string "you do that!$"
Text_ApImport_5: @ 0x1405, Zero 2's 0x502
	.string "{WINDOW 0x88}"
	.string "Gh gh gh...▼"
	.string "I can't believe\n"
	.string "this. I was beaten\n"
	.string "by this little▼"
	.string "bug thing...▼"
	.string "Bobobohfa....!$"
Text_ApImport_6: @ 0x1406, Zero 2's 0x503
	.string "{WINDOW 0x00}"
	.string "Operator: you have three▼"
	.string "systems to destroy.$"
Text_ApImport_7: @ 0x1407, Zero 2's 0x504
	.string "{WINDOW 0x00}"
	.string "Operator: you have two▼"
	.string "systems to destroy.$"
Text_ApImport_8: @ 0x1408, Zero 2's 0x505
	.string "{WINDOW 0x00}"
	.string "Operator: you have one▼"
	.string "system to destroy.$"
Text_ApImport_9: @ 0x1409, Zero 2's 0x506
	.string "{WINDOW 0x00}"
	.string "Operator: All the systems▼"
	.string "have been destroyed.$"
Text_ApImport_10: @ 0x140a, Zero 2's 0x800
	.string "{WINDOW 0x00}"
	.string "Operator: We confirmed that▼"
	.string "there are supplies▼"
	.string "in this transport train.▼"
	.string "Watch out for obstructions▼"
	.string "and seize the train.$"
Text_ApImport_11: @ 0x140b, Zero 2's 0x801
	.string "{WINDOW 0x8D}"
	.string "Hey, you!▼"
	.string "Don't you know\n"
	.string "that this is\n"
	.string "Master Harpuia's▼"
	.string "territory?▼"
	.string "Huh, a minion of\n"
	.string "the resistance\n"
	.string "force!▼"
	.string "I shall stop you!$"
Text_ApImport_12: @ 0x140c, Zero 2's 0x802
	.string "{WINDOW 0x8C}"
	.string "No... No... I\n"
	.string "can't believe\n"
	.string "this...▼"
	.string "Master Harpuia...▼"
	.string "I'm ashamed...\n"
	.string "I was not good\n"
	.string "enough...▼"
	.string "Guhhha....h!$"
Text_ApImport_13: @ 0x140d, Zero 2's 0x803
	.string "{WINDOW 0x00}"
	.string "Operator: Mr. Zero! Please▼"
	.string "listen!▼"
	.string "Enemy Mechaniloids are▼"
	.string "approaching you.▼"
	.string "Their mission is to▼"
	.string "retrieve the supplies.▼"
	.string "Please protect the supplies▼"
	.string "and defeat the enemies.$"
Text_ApImport_14: @ 0x140e, Zero 2's 0x700
	.string "{WINDOW 0x00}"
	.string "Operator: Destroy all power▼"
	.string "reactors to put a stop▼"
	.string "to the factory functions▼"
	.string "for good.▼"
	.string "Currently, there are four▼"
	.string "power reactors▼"
	.string "in operation.$"
Text_ApImport_15: @ 0x140f, Zero 2's 0x701
	.string "{WINDOW 0x8F}"
	.string "What are you doing\n"
	.string "here?▼"
	.string "How dare you fool\n"
	.string "around in my area!▼"
	.string "I am Phoenix\n"
	.string "Magnion.▼"
	.string "Well, you'll pay\n"
	.string "for this insult...▼"
	.string "With my phoenix\n"
	.string "flame!▼"
	.string "I shall purify\n"
	.string "your evil mind\n"
	.string "with my flame.$"
Text_ApImport_16: @ 0x1410, Zero 2's 0x702
	.string "{WINDOW 0x8E}"
	.string "... I am...\n"
	.string "...A phoenix...▼"
	.string "I will be back...\n"
	.string "Again and again...▼"
	.string "Until you pay for\n"
	.string "your insult...▼"
	.string "Uh... Uwooooooh!$"
Text_ApImport_17: @ 0x1411, Zero 2's 0x400
	.string "{WINDOW 0x00}"
	.string "Operator: The ruins are▼"
	.string "beyond this forest.▼"
	.string "Use the portable Trans▼"
	.string "Server and▼"
	.string "rescue the resistance▼"
	.string "soldiers who were lost.$"
Text_ApImport_18: @ 0x1412, Zero 2's 0x401
	.string "{WINDOW 0x85}"
	.string "Hiss! This is a\n"
	.string "restricted area,\n"
	.string "even for us Neo▼"
	.string "Arcadians... You\n"
	.string "will never leave\n"
	.string "here alive. Hiss!$"
Text_ApImport_19: @ 0x1413, Zero 2's 0x402
	.string "{WINDOW 0x84}"
	.string "No... If only that\n"
	.string "Baby Elf wasn't\n"
	.string "stolen...▼"
	.string "I could have easily\n"
	.string "destroyed the\n"
	.string "nameless soldier...▼"
	.string "Hissssss!$"
Text_ApImport_20: @ 0x1414, Zero 2's 0x403
	.string "{WINDOW 0x87}"
	.string "Thank you, Mr. Zero.\n"
	.string "The ruins are full\n"
	.string "of traps. Please▼"
	.string "be careful.$"
Text_ApImport_21: @ 0x1415, Zero 2's 0x404
	.string "{WINDOW 0x87}"
	.string "Thank you. I hope\n"
	.string "the others are\n"
	.string "fine.$"
Text_ApImport_22: @ 0x1416, Zero 2's 0x405
	.string "{WINDOW 0x86}"
	.string "Thank you so much...\n"
	.string "I went too far\n"
	.string "and got stuck...$"
Text_ApImport_23: @ 0x1417, Zero 2's 0x406
	.string "{WINDOW 0x86}"
	.string "I'm glad that you\n"
	.string "came here to help\n"
	.string "me.▼"
	.string "Thank you very\n"
	.string "much.$"
Text_ApImport_24: @ 0x1418, Zero 2's 0x407
	.string "{WINDOW 0x86}"
	.string "Thanks!! I almost\n"
	.string "lost hope of\n"
	.string "a rescue...$"
Text_ApImport_25: @ 0x1419, Zero 2's 0x408
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
Text_ApImport_26: @ 0x141a, Zero 2's 0x409
	.string "{WINDOW 0x85}"
	.string "Give that back...▼"
	.string "And your life may\n"
	.string "be spared. Hiss!$"
Text_ApImport_27: @ 0x141b, Zero 2's 0x40a
	.string "{WINDOW 0x04}"
	.string "What are you waiting\n"
	.string "for...▼"
	.string "Run!$"
Text_ApImport_28: @ 0x141c, Zero 2's 0x40b
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
Text_ApImport_29: @ 0x141d, Zero 2's 0x40c
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
Text_ApImport_30: @ 0x141e, Zero 2's 0x40d
	.string "{WINDOW 0x04}"
	.string "Wait, X!▼"
	.string "... ... ...▼"
	.string "The Dark Elf...$"
Text_ApImport_31: @ 0x141f, Zero 2's 0xe00
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
Text_ApImport_32: @ 0x1420, Zero 2's 0xe01
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
Text_ApImport_33: @ 0x1421, Zero 2's 0xe02
	.string "{WINDOW 0x2D}"
	.string "Stop!$"
Text_ApImport_34: @ 0x1422, Zero 2's 0xe03
	.string "{WINDOW 0x31}"
	.string "Wha...!$"
Text_ApImport_35: @ 0x1423, Zero 2's 0xe04
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
Text_ApImport_36: @ 0x1424, Zero 2's 0xe05
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
Text_ApImport_37: @ 0x1425, Zero 2's 0xe06
	.string "{WINDOW 0x00}"
	.string "Operator: Emergency call▼"
	.string "for Zero!▼"
	.string "An unidentified object is▼"
	.string "rapidly flying toward the▼"
	.string "Resistance Base.▼"
	.string "Return to base immediately!$"
Text_ApImport_38: @ 0x1426, Zero 2's 0xe07
	.string "{WINDOW 0x2F}"
	.string "Ooh. Can you hear\n"
	.string "it? A bombardment\n"
	.string "aircraft is heading▼"
	.string "for your base with\n"
	.string "a special bomb.$"
Text_ApImport_39: @ 0x1427, Zero 2's 0xe08
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
Text_ApImport_40: @ 0x1428, Zero 2's 0xe09
	.string "{WINDOW 0x00}"
	.string "Operator: Roger...▼"
	.string "Transfer commencing.$"
Text_ApImport_41: @ 0x1429, Zero 2's 0xe0a
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
Text_ApImport_42: @ 0x142a, Zero 2's 0x600
	.string "{WINDOW 0x00}"
	.string "Pilot: No, we can't▼"
	.string "approach any further...▼"
	.string "Or we will appear on their▼"
	.string "radar.▼"
	.string "Ciel: ...Zero. Once you▼"
	.string "reach the enemy aircraft,▼"
	.string "please let me know by▼"
	.string "activating a portable▼"
	.string "Trans Server.$"
Text_ApImport_43: @ 0x142b, Zero 2's 0x601
	.string "{WINDOW 0x91}"
	.string "Don't expect you can\n"
	.string "go back easily.\n"
	.string "Zero!▼"
	.string "I know you have\n"
	.string "released the\n"
	.string "bomb...▼"
	.string "However, we can\n"
	.string "still continue\n"
	.string "our mission if▼"
	.string "I have the\n"
	.string "aircraft crash\n"
	.string "into your base!▼"
	.string "I am Kuwagust\n"
	.string "Anchus! We Will\n"
	.string "become a flaming▼"
	.string "arrow and crash into\n"
	.string "your base!$"
Text_ApImport_44: @ 0x142c, Zero 2's 0x602
	.string "{WINDOW 0x90}"
	.string "B... brotheeeeer!▼"
	.string "I'm sooorrrrry...\n"
	.string "I failed to avenge\n"
	.string "yoooouu!$"
Text_ApImport_45: @ 0x142d, Zero 2's 0x603
	.string "{WINDOW 0x04}"
	.string "I set the transfer\n"
	.string "coordinates.\n"
	.string "Transfer Ciel here.$"
Text_ApImport_46: @ 0x142e, Zero 2's 0x604
	.string "{WINDOW 0x41}"
	.string "I'll quickly\n"
	.string "release the\n"
	.string "bomb...▼"
	.string "The devise is...▼"
	.string "It's here.$"
Text_ApImport_47: @ 0x142f, Zero 2's 0x605
	.string "{WINDOW 0x41}"
	.string "I need ninety\n"
	.string "seconds to\n"
	.string "release fuse.▼"
	.string "Please, provide\n"
	.string "cover for me...$"
Text_ApImport_48: @ 0x1430, Zero 2's 0x606
	.string "{WINDOW 0x00}"
	.string "Ciel: The fuse has been▼"
	.string "released!▼"
	.string "Operator: We confirmed the▼"
	.string "fuse has been released.▼"
	.string "Preparing to transfer.▼"
	.string "Secure your position.$"
Text_ApImport_49: @ 0x1431, Zero 2's 0x607
	.string "{WINDOW 0x04}"
	.string "Ciel! You go ahead!!▼"
	.string "{WINDOW 0x41}"
	.string "All right! You\n"
	.string "follow me quickly!!$"
Text_ApImport_50: @ 0x1432, Zero 2's 0x608
	.string "{WINDOW 0x00}"
	.string "Operator: Position secured.▼"
	.string "Transfer commencing.$"
Text_ApImport_51: @ 0x1433, Zero 2's 0x60a
	.string "{WINDOW 0x00}"
	.string "Ciel: It's an emergency,▼"
	.string "Zero!▼"
	.string "Due to air turbulence...▼"
	.string "The transfer won't work!▼"
	.string "The storage of the aircraft▼"
	.string "is broken.▼"
	.string "Please escape from there!!$"
Text_ApImport_52: @ 0x1434, Zero 2's 0x60b
	.string "{WINDOW 0x00}"
	.string "Ciel: Please jump off!▼"
	.string "Our aircraft is on standby▼"
	.string "and ready to pick you up.$"
Text_ApImport_53: @ 0x1435, Zero 2's 0x60c
	.string "{WINDOW 0x00}"
	.string "Ciel: I finished about▼"
	.string "half of my analysis...$"
Text_ApImport_54: @ 0x1436, Zero 2's 0x60d
	.string "{WINDOW 0x00}"
	.string "Ciel: Maybe I'll be done▼"
	.string "shortly...$"
Text_ApImport_55: @ 0x1437, Zero 2's 0x900
	.string "{WINDOW 0x00}"
	.string "Ciel: ... You found Elpizo.▼"
	.string "Zero... Take care of him...▼"
	.string "Please.$"
Text_ApImport_56: @ 0x1438, Zero 2's 0x901
	.string "{WINDOW 0x93}"
	.string "W... Waaait!▼"
	.string "Wait. Wait. Wait.\n"
	.string "No one can go beyond\n"
	.string "here, ribbid!▼"
	.string "This is an order\n"
	.string "of Master Harpuia,\n"
	.string "ribbid!▼"
	.string "... ... ...?▼"
	.string "Hmm? Is there\n"
	.string "someone on the\n"
	.string "other side of▼"
	.string "the door? Ribbid.\n"
	.string "No way... This must\n"
	.string "be a false alarm.▼"
	.string "I need to have my\n"
	.string "sensor replaced...$"
Text_ApImport_57: @ 0x1439, Zero 2's 0x902
	.string "{WINDOW 0x92}"
	.string "Um... Ugha....▼"
	.string "Master Harpuia!▼"
	.string "How can I\n"
	.string "apologize to\n"
	.string "Master Harpuia...?▼"
	.string "Ug... Gwaaaah!$"
Text_ApImport_58: @ 0x143a, Zero 2's 0x903
	.string "{WINDOW 0x8B}"
	.string "Ha ha ha, Zero.\n"
	.string "Nice to see you\n"
	.string "again.▼"
	.string "Are you...\n"
	.string "Looking for me...?▼"
	.string "{WINDOW 0x04}"
	.string "Return to the base.\n"
	.string "What can you do by\n"
	.string "yourself...?▼"
	.string "{WINDOW 0x8B}"
	.string "Actually, I can do\n"
	.string "anything and\n"
	.string "everything...▼"
	.string "If I obtain a\n"
	.string "certain thing.▼"
	.string "I learned about\n"
	.string "something that makes\n"
	.string "you invincible once▼"
	.string "you obtain it...▼"
	.string "Thanks to these\n"
	.string "Baby Elves...▼"
	.string "{WINDOW 0x04}"
	.string "You mean... The\n"
	.string "Dark Elf...$"
Text_ApImport_59: @ 0x143b, Zero 2's 0x904
	.string "{WINDOW 0x8B}"
	.string "Yes. Hee hee hee.\n"
	.string "I once thought it\n"
	.string "was something from▼"
	.string "mythology... But I\n"
	.string "was wrong. I have\n"
	.string "come believe in it.▼"
	.string "The key to unlock\n"
	.string "the seal of the Dark\n"
	.string "Elf is somewhere▼"
	.string "around here... Let's\n"
	.string "see who'll find it\n"
	.string "first!$"
Text_ApImport_60: @ 0x143c, Zero 2's 0x905
	.string "{WINDOW 0x8B}"
	.string "Hee hee hee.▼"
	.string "Finally, I found\n"
	.string "the key!▼"
	.string "Nice try, Zero.\n"
	.string "Hee hee hee.$"
Text_ApImport_61: @ 0x143d, Zero 2's 0x906
	.string "{WINDOW 0x8B}"
	.string "Gha ha ha ha!▼"
	.string "Now... All I have to\n"
	.string "do is break the seal\n"
	.string "of the Dark Elf.▼"
	.string "Then I will be as\n"
	.string "strong as you, Zero.▼"
	.string "Or should I say\n"
	.string "stronger than\n"
	.string "you...?▼"
	.string "Oh, don't get me\n"
	.string "wrong... I won't use\n"
	.string "this power for▼"
	.string "evil. I do this for\n"
	.string "world peace.▼"
	.string "And, for Ms. Ciel!▼"
	.string "{WINDOW 0x94}"
	.string "Mi mimi...▼"
	.string "Mam.. ma...\n"
	.string "Mi Mimimi...$"
Text_ApImport_62: @ 0x143e, Zero 2's 0x907
	.string "{WINDOW 0x35}"
	.string "... ... ...▼"
	.string "Sorry, Zero...▼"
	.string "I didn't expect them\n"
	.string "to have become that\n"
	.string "strong...▼"
	.string "{WINDOW 0x04}"
	.string "X...▼"
	.string "{WINDOW 0x35}"
	.string "As long as I'm\n"
	.string "protecting the seal\n"
	.string "of the main body,▼"
	.string "I'm not ready to\n"
	.string "deal with them...▼"
	.string "{WINDOW 0x04}"
	.string "Don't worry...▼"
	.string "I'll handle it...▼"
	.string "{WINDOW 0x35}"
	.string "... ... ...▼"
	.string "She is responding\n"
	.string "to her children...\n"
	.string "Zero... We have no▼"
	.string "time... You must\n"
	.string "find a way to\n"
	.string "stop Elpizo.$"
Text_ApImport_63: @ 0x143f, Zero 2's 0x908
	.string "{WINDOW 0x04}"
	.string "... ... ...▼"
	.string "The Dark Elf...▼"
	.string "... ... ...▼"
	.string "Mission\n"
	.string "accomplished.\n"
	.string "Transfer me back.$"
Text_ApImport_64: @ 0x1440, Zero 2's 0x909
	.string "{WINDOW 0x00}"
	.string "Operator: Roger.▼"
	.string "Transfer commencing.$"
Text_ApImport_65: @ 0x1441, Zero 2's 0xa00
	.string "{WINDOW 0x00}"
	.string "Ciel: ... Zero. Can you▼"
	.string "hear me?▼"
	.string "It seems you can't enter▼"
	.string "it through the facility.▼"
	.string "You need to enter from▼"
	.string "the outside.▼"
	.string "Stay alert...$"
Text_ApImport_66: @ 0x1442, Zero 2's 0xa01
	.string "{WINDOW 0x2F}"
	.string "Hello, Zero.\n"
	.string "It's nice to see\n"
	.string "you again.▼"
	.string "I'd love to play\n"
	.string "with you... But\n"
	.string "unfortunately I▼"
	.string "have no time.▼"
	.string "As soon as I defeat\n"
	.string "you, I have to take\n"
	.string "care of commander▼"
	.string "Elpizo.▼"
	.string "So let's go, Zero!$"
Text_ApImport_67: @ 0x1443, Zero 2's 0xa02
	.string "{WINDOW 0x2E}"
	.string "Hah hah hah...▼"
	.string "While playing with\n"
	.string "you... Elpizo went\n"
	.string "somewhere...▼"
	.string "I got caught up in\n"
	.string "the fun of the\n"
	.string "moment. How▼"
	.string "foolish of me...▼"
	.string "Your strength\n"
	.string "drives me crazy...▼"
	.string "Next time...\n"
	.string "I'll do better...▼"
	.string "So, see you again...$"
Text_ApImport_68: @ 0x1444, Zero 2's 0xb00
	.string "{WINDOW 0x00}"
	.string "Ciel: This should be the▼"
	.string "meeting spot for our▼"
	.string "comrades.▼"
	.string "It's strange...▼"
	.string "No one has arrived...▼"
	.string "Zero... I've got a very▼"
	.string "bad feeling...$"
Text_ApImport_69: @ 0x1445, Zero 2's 0xb07
	.string "{WINDOW 0x00}"
	.string "Ciel: ... Zero! They are▼"
	.string "being controlled by▼"
	.string "something!▼"
	.string "Make sure you don't harm▼"
	.string "them, Zero.$"
Text_ApImport_70: @ 0x1446, Zero 2's 0xb03
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
Text_ApImport_71: @ 0x1447, Zero 2's 0xb04
	.string "{WINDOW 0x2C}"
	.string "Are you serious?\n"
	.string "How can a legend\n"
	.string "die?$"
Text_ApImport_72: @ 0x1448, Zero 2's 0xb05
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
Text_ApImport_73: @ 0x1449, Zero 2's 0xb06
	.string "{WINDOW 0x04}"
	.string "... ... ...▼"
	.string "Mission\n"
	.string "accomplished.\n"
	.string "Transfer me back.▼"
	.string "{WINDOW 0x62}"
	.string "Roger. Transfer\n"
	.string "commencing.$"
Text_ApImport_74: @ 0x144a, Zero 2's 0xc00
	.string "{WINDOW 0x00}"
	.string "Ciel: ...Zero.▼"
	.string "Stay Alert...$"
Text_ApImport_75: @ 0x144b, Zero 2's 0xc01
	.string "{WINDOW 0x31}"
	.string "Oh! You must be\n"
	.string "Zero!!▼"
	.string "Ha ha!\n"
	.string "I'm so glad to\n"
	.string "see you again!▼"
	.string "I was chasing a\n"
	.string "guy named Elpizo,\n"
	.string "you know him,▼"
	.string "right?▼"
	.string "Ha ha!▼"
	.string "I am lucky to\n"
	.string "meet you here.▼"
	.string "Now, let's start!!\n"
	.string "Let's do it now!▼"
	.string "Here I goooooo!!!$"
Text_ApImport_76: @ 0x144c, Zero 2's 0xc02
	.string "{WINDOW 0x30}"
	.string "Huh huh huh...▼"
	.string "Whew. That was\n"
	.string "really fun!\n"
	.string "Thank you, Zero.▼"
	.string "I enjoy a\n"
	.string "challenging\n"
	.string "fight like▼"
	.string "this one.\n"
	.string "Hee hee.▼"
	.string "Next time, let's\n"
	.string "go for even\n"
	.string "more!▼"
	.string "See ya!!$"
Text_ApImport_77: @ 0x144d, Zero 2's 0xd00
	.string "{WINDOW 0x00}"
	.string "Ciel: I've set a▼"
	.string "coordinate axis...▼"
	.string "Now you can return here▼"
	.string "anytime you want...▼"
	.string "So please return to the▼"
	.string "base once,▼"
	.string "before you go any further.▼"
	.string "Please... Zero.$"
Text_ApImport_78: @ 0x144e, Zero 2's 0xf01
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
Text_ApImport_79: @ 0x144f, Zero 2's 0xf02
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
Text_ApImport_80: @ 0x1450, Zero 2's 0xf03
	.string "{WINDOW 0x00}"
	.string "Ciel: I've set a▼"
	.string "coordinate axis...▼"
	.string "Now you can return here▼"
	.string "anytime you want...▼"
	.string "So please return to the▼"
	.string "base once. Please... Zero.$"
Text_ApImport_81: @ 0x1451, Zero 2's 0x1001
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
Text_ApImport_82: @ 0x1452, Zero 2's 0x1002
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
Text_ApImport_83: @ 0x1453, Zero 2's 0x1003
	.string "{WINDOW 0x00}"
	.string "Ciel: I've set a▼"
	.string "coordinate axis...▼"
	.string "Now you can return here▼"
	.string "anytime you want...▼"
	.string "So please return to the▼"
	.string "base once. Please... Zero.$"
Text_ApImport_84: @ 0x1454, Zero 2's 0x1101
	.string "{WINDOW 0x04}"
	.string "Harpuia!!▼"
	.string "{WINDOW 0x8B}"
	.string "Ha! Ha! Ha!▼"
	.string "You've made it here\n"
	.string "at last, Zero.$"
Text_ApImport_85: @ 0x1455, Zero 2's 0x1102
	.string "{WINDOW 0x8B}"
	.string "{BOTTOM}"
	.string "Look...▼"
	.string "This is...\n"
	.string "Dark Elf...▼"
	.string "A perfect Cyber-elf,\n"
	.string "which will bring\n"
	.string "peace to this▼"
	.string "world...$"
Text_ApImport_86: @ 0x1456, Zero 2's 0x1103
	.string "{WINDOW 0x8B}"
	.string "Hee hee, it will\n"
	.string "not be long before\n"
	.string "I can get rid of▼"
	.string "all the humans who\n"
	.string "waste our valuable\n"
	.string "energy, and destroy▼"
	.string "Neo Arcadia which\n"
	.string "protects them.$"
Text_ApImport_87: @ 0x1457, Zero 2's 0x1104
	.string "{WINDOW 0x8B}"
	.string "All I have to do\n"
	.string "is...▼"
	.string "Destroy X, who has\n"
	.string "been interfering\n"
	.string "with the true▼"
	.string "revival of Dark\n"
	.string "Elf...$"
Text_ApImport_88: @ 0x1458, Zero 2's 0x1105
	.string "{WINDOW 0x2D}"
	.string "I won't...\n"
	.string "Let that happen...$"
Text_ApImport_89: @ 0x1459, Zero 2's 0x1106
	.string "{WINDOW 0x8B}"
	.string "You!\n"
	.string "You can still say\n"
	.string "such a thing...!$"
Text_ApImport_90: @ 0x145a, Zero 2's 0x1107
	.string "{WINDOW 0x8B}"
	.string "Be a good boy and\n"
	.string "die...▼"
	.string "Wha ha ha ha ha!▼"
	.string "You must know your\n"
	.string "own worth. Do you\n"
	.string "regret that you▼"
	.string "haven't shown any\n"
	.string "respect for me...?\n"
	.string "Now that I am so▼"
	.string "much more than you!\n"
	.string "I've acquired a\n"
	.string "power that no one▼"
	.string "can match. I've\n"
	.string "become invincible!$"
Text_ApImport_91: @ 0x145b, Zero 2's 0x1108
	.string "{WINDOW 0x8B}"
	.string "Hee hee...▼"
	.string "It's getting\n"
	.string "late... Time to\n"
	.string "wake the Dark Elf▼"
	.string "up...\n"
	.string "Let's celebrate\n"
	.string "the new history▼"
	.string "of the world.$"
Text_ApImport_92: @ 0x145c, Zero 2's 0x1109
	.string "{WINDOW 0x8B}"
	.string "Why don't you\n"
	.string "enjoy yourselves.▼"
	.string "Well then, enjoy!$"
Text_ApImport_93: @ 0x145d, Zero 2's 0x110a
	.string "{WINDOW 0x2D}"
	.string "U... Ugh...▼"
	.string "Z...Zero...▼"
	.string "Kill... me...▼"
	.string "{WINDOW 0x04}"
	.string "...▼"
	.string "{WINDOW 0x2D}"
	.string "Just kill me...▼"
	.string "I will... soon be\n"
	.string "controlled by Baby\n"
	.string "Elf...▼"
	.string "Kill me now...\n"
	.string "And stop him...!$"
Text_ApImport_94: @ 0x145e, Zero 2's 0x110b
	.string "{WINDOW 0x2D}"
	.string "H... hurry, Zero...▼"
	.string "Protect Master X...\n"
	.string "and the world...\n"
	.string "from him...▼"
	.string "{WINDOW 0x04}"
	.string "I understand...\n"
	.string "Leave it to me.$"
Text_ApImport_95: @ 0x145f, Zero 2's 0x110c
	.string "{WINDOW 0x00}"
	.string "Ciel: I've set a▼"
	.string "coordinate axis...▼"
	.string "Now you can return here▼"
	.string "anytime you want...▼"
	.string "So please return to the▼"
	.string "base once. Please... Zero.$"

.endif
