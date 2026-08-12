.if AP

.balign 4
.section .rodata

.global gApFreeRunConfirmTexts
gApFreeRunConfirmTexts:
	.4byte ApText_FreeRun_DerelictSpacecraft
	.4byte ApText_FreeRun_AegisVolcanoBase
	.4byte ApText_FreeRun_OceanicHwyRuins
	.4byte ApText_FreeRun_WRFactory
	.4byte ApText_FreeRun_OldResidential
	.4byte ApText_FreeRun_MissileFactory
	.4byte ApText_FreeRun_TwilightDesert
	.4byte ApText_FreeRun_ForestOfAnatre
	.4byte ApText_FreeRun_FrontlineIceBase
	.4byte ApText_FreeRun_AreaX2
	.4byte ApText_FreeRun_EnergyFacility
	.4byte ApText_FreeRun_SnowyPlains
	.4byte ApText_FreeRun_SunkenLibrary
	.4byte ApText_FreeRun_GiantElevator
	.4byte ApText_FreeRun_SubArcadia

ApText_FreeRun_DerelictSpacecraft:
	.string "{WINDOW 0x62}"
		.string "{RED}DERELICT SPACECRAFT{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_AegisVolcanoBase:
	.string "{WINDOW 0x62}"
		.string "{RED}AEGIS VOLCANO BASE{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_OceanicHwyRuins:
	.string "{WINDOW 0x62}"
		.string "{RED}OCEANIC HWY RUINS{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_WRFactory:
	.string "{WINDOW 0x62}"
		.string "{RED}W.R. FACTORY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_OldResidential:
	.string "{WINDOW 0x62}"
		.string "{RED}OLD RESIDENTIAL{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_MissileFactory:
	.string "{WINDOW 0x62}"
		.string "{RED}MISSILE FACTORY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_TwilightDesert:
	.string "{WINDOW 0x62}"
		.string "{RED}TWILIGHT DESERT{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_ForestOfAnatre:
	.string "{WINDOW 0x62}"
		.string "{RED}FOREST OF ANATRE{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_FrontlineIceBase:
	.string "{WINDOW 0x62}"
		.string "{RED}FRONTLINE ICE BASE{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_AreaX2:
	.string "{WINDOW 0x62}"
		.string "{RED}AREA X-2{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_EnergyFacility:
	.string "{WINDOW 0x62}"
		.string "{RED}ENERGY FACILITY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_SnowyPlains:
	.string "{WINDOW 0x62}"
		.string "{RED}SNOWY PLAINS{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_SunkenLibrary:
	.string "{WINDOW 0x62}"
		.string "{RED}SUNKEN LIBRARY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_GiantElevator:
	.string "{WINDOW 0x62}"
		.string "{RED}GIANT ELEVATOR{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_FreeRun_SubArcadia:
	.string "{WINDOW 0x62}"
		.string "{RED}SUB ARCADIA{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

.endif
