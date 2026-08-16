.if AP

.balign 4
.section .rodata

.global gApStageRevisitTexts
gApStageRevisitTexts:
	.4byte ApText_Revisit_DerelictSpacecraft
	.4byte ApText_Revisit_AegisVolcanoBase
	.4byte ApText_Revisit_OceanicHwyRuins
	.4byte ApText_Revisit_WRFactory
	.4byte ApText_Revisit_OldResidential
	.4byte ApText_Revisit_MissileFactory
	.4byte ApText_Revisit_TwilightDesert
	.4byte ApText_Revisit_ForestOfAnatre
	.4byte ApText_Revisit_FrontlineIceBase
	.4byte ApText_Revisit_AreaX2
	.4byte ApText_Revisit_EnergyFacility
	.4byte ApText_Revisit_SnowyPlains
	.4byte ApText_Revisit_SunkenLibrary
	.4byte ApText_Revisit_GiantElevator
	.4byte ApText_Revisit_SubArcadia
	.4byte ApText_Revisit_ResearchLaboratory

.global gApStageStartTexts
gApStageStartTexts:
	.4byte ApText_Start_DerelictSpacecraft
	.4byte ApText_Start_AegisVolcanoBase
	.4byte ApText_Start_OceanicHwyRuins
	.4byte ApText_Start_WRFactory
	.4byte ApText_Start_OldResidential
	.4byte ApText_Start_MissileFactory
	.4byte ApText_Start_TwilightDesert
	.4byte ApText_Start_ForestOfAnatre
	.4byte ApText_Start_FrontlineIceBase
	.4byte ApText_Start_AreaX2
	.4byte ApText_Start_EnergyFacility
	.4byte ApText_Start_SnowyPlains
	.4byte ApText_Start_SunkenLibrary
	.4byte ApText_Start_GiantElevator
	.4byte ApText_Start_SubArcadia
	.4byte ApText_Start_ResearchLaboratory

.global gApFinalStageName
gApFinalStageName:
	.string "RESEARCH LABORATORY$"

@ The stage select's lines that it displays in the box when hovering over a level

.global gApSelectStageLabel
gApSelectStageLabel:
	.string "Stage:$"

.global gApSelectDisksLabel
gApSelectDisksLabel:
	.string "Disks:$"

.global gApSelectRankLabel
gApSelectRankLabel:
	.string "Highest Rank:$"

.global gApSelectLocked
gApSelectLocked:
	.string "LOCKED$"

.global gApSelectOpen
gApSelectOpen:
	.string "OPEN$"

.global gApSelectCleared
gApSelectCleared:
	.string "CLEARED$"

@ Indexed by RANK_F..RANK_S, so the letter for a rank is just gApSelectRankLetters[rank].
.global gApSelectRankLetters
gApSelectRankLetters:
	.string "FEDCBAS$"

.balign 4
ApText_Revisit_DerelictSpacecraft:
	.string "{WINDOW 0x62}"
		.string "{RED}DERELICT SPACECRAFT{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_AegisVolcanoBase:
	.string "{WINDOW 0x62}"
		.string "{RED}AEGIS VOLCANO BASE{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_OceanicHwyRuins:
	.string "{WINDOW 0x62}"
		.string "{RED}OCEANIC HWY RUINS{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_WRFactory:
	.string "{WINDOW 0x62}"
		.string "{RED}W.R. FACTORY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_OldResidential:
	.string "{WINDOW 0x62}"
		.string "{RED}OLD RESIDENTIAL{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_MissileFactory:
	.string "{WINDOW 0x62}"
		.string "{RED}MISSILE FACTORY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_TwilightDesert:
	.string "{WINDOW 0x62}"
		.string "{RED}TWILIGHT DESERT{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_ForestOfAnatre:
	.string "{WINDOW 0x62}"
		.string "{RED}FOREST OF ANATRE{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_FrontlineIceBase:
	.string "{WINDOW 0x62}"
		.string "{RED}FRONTLINE ICE BASE{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_AreaX2:
	.string "{WINDOW 0x62}"
		.string "{RED}AREA X-2{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_EnergyFacility:
	.string "{WINDOW 0x62}"
		.string "{RED}ENERGY FACILITY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_SnowyPlains:
	.string "{WINDOW 0x62}"
		.string "{RED}SNOWY PLAINS{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_SunkenLibrary:
	.string "{WINDOW 0x62}"
		.string "{RED}SUNKEN LIBRARY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_GiantElevator:
	.string "{WINDOW 0x62}"
		.string "{RED}GIANT ELEVATOR{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_SubArcadia:
	.string "{WINDOW 0x62}"
		.string "{RED}SUB ARCADIA{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Revisit_ResearchLaboratory:
	.string "{WINDOW 0x62}"
		.string "{RED}RESEARCH LABORATORY{RED_END}?\n"
		.string "  EXPLORE\n"
		.string "  RETRY MISSION$"

ApText_Start_DerelictSpacecraft:
	.string "{WINDOW 0x62}"
		.string "{RED}DERELICT SPACECRAFT{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_AegisVolcanoBase:
	.string "{WINDOW 0x62}"
		.string "{RED}AEGIS VOLCANO BASE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_OceanicHwyRuins:
	.string "{WINDOW 0x62}"
		.string "{RED}OCEANIC HWY RUINS{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_WRFactory:
	.string "{WINDOW 0x62}"
		.string "{RED}W.R. FACTORY{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_OldResidential:
	.string "{WINDOW 0x62}"
		.string "{RED}OLD RESIDENTIAL{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_MissileFactory:
	.string "{WINDOW 0x62}"
		.string "{RED}MISSILE FACTORY{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_TwilightDesert:
	.string "{WINDOW 0x62}"
		.string "{RED}TWILIGHT DESERT{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_ForestOfAnatre:
	.string "{WINDOW 0x62}"
		.string "{RED}FOREST OF ANATRE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_FrontlineIceBase:
	.string "{WINDOW 0x62}"
		.string "{RED}FRONTLINE ICE BASE{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_AreaX2:
	.string "{WINDOW 0x62}"
		.string "{RED}AREA X-2{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_EnergyFacility:
	.string "{WINDOW 0x62}"
		.string "{RED}ENERGY FACILITY{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_SnowyPlains:
	.string "{WINDOW 0x62}"
		.string "{RED}SNOWY PLAINS{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_SunkenLibrary:
	.string "{WINDOW 0x62}"
		.string "{RED}SUNKEN LIBRARY{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_GiantElevator:
	.string "{WINDOW 0x62}"
		.string "{RED}GIANT ELEVATOR{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_SubArcadia:
	.string "{WINDOW 0x62}"
		.string "{RED}SUB ARCADIA{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

ApText_Start_ResearchLaboratory:
	.string "{WINDOW 0x62}"
		.string "{RED}RESEARCH LABORATORY{RED_END}?\n"
		.string "  START MISSION\n"
		.string "  CANCEL$"

.endif
