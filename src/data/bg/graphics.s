  .include "asm/macros.inc"

.section .rodata
.balign 4, 0

@ preproc を使う
gBgGraphics::

gGraphic_Capcom:: @ Gfx0 in 0x08547280
	.4byte Capcom_Tiles-. @ data: 0x08547CF8
	.4byte (Capcom_Pal - Capcom_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
  gPalette_Capcom::
		.4byte Capcom_Pal-. @ data: 0x08548658 = .+5068
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphic_Inti:: @ Gfx1 in 0x08547294
	.4byte Inti_Tiles-. @ data: 0x08548678
	.4byte (Inti_Pal - Inti_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
  gPalette_Inti::
		.4byte Inti_Pal-. @ data: 0x08548B64
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphic_085472a8:: @ Gfx2 in 0x085472A8
	.4byte Cutscene085472a8_Tiles-.
	.4byte (Cutscene085472a8_End - Cutscene085472a8_Tiles - 256) | (256 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
  gPalette_085472a8::
		.4byte (Cutscene085472a8_End - 256)-.
		.2byte 256 @ bytesize
		.byte 0, 6 @ lz77(bool8), dst = PaletteID

gGraphic_TitleZero:: @ Gfx3 in 0x085472BC
	.4byte TitleZero_Tiles-. @ data: 0x0854B174
	.4byte (TitleZero_Pal - TitleZero_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
  gPalette_TitleZero::
		.4byte TitleZero_Pal-. @ data: 0x0854DE40
		.2byte 64 @ bytesize
		.byte 0, 14 @ lz77(bool8), dst = PaletteID

gGraphic_TitleCiel:: @ Gfx4 in 0x085472D0
	.4byte TitleCiel_Tiles-. @ data: 0x0854DE80 = .+27568
	.4byte (TitleCiel_Pal - TitleCiel_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
  gPalette_TitleCiel::
		.4byte TitleCiel_Pal-. @ data: 0x0854FEC4 = .+35816
		.2byte 64 @ bytesize
		.byte 0, 14 @ lz77(bool8), dst = PaletteID

	@ Gfx5 in 0x085472E4
	.4byte HUD_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte HUD_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 14 @ lz77(bool8), dst = PaletteID

	@ Gfx6 in 0x085472F8
	.4byte HUD_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte HUD_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx7 in 0x0854730C
	.4byte HUD_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte HUD_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx8 in 0x08547320
	.4byte HUD_Tiles-.
	.4byte 0 | (256 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, LZ77 	@ rowsize(unused), props
		@ Palette
		.4byte HUD_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 6 @ lz77(bool8), dst = PaletteID

	@ Gfx9 in 0x08547334
	.4byte HUD_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte HUD_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

gGraphic_HUD::	@ Gfx10 in 0x08547348
	.4byte HUD_Tiles-. @ data: 0x0854FF04
	.4byte (HUD_Pal - HUD_Tiles) | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
	gPalette_HUD::
		.4byte HUD_Pal-. @ data: 0x085516C4
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

gGraphic_MissionStart:: @ Gfx11 in 0x0854735C
	.4byte MissionStart_Tiles-. @ data: 0x085516E4 = .+41864
	.4byte (MissionStart_Pal - MissionStart_Tiles) | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
	gPalette_MissionStart::
		.4byte MissionStart_Pal-. @ data: 0x08551E24 = .+43708
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

gGraphic_MissionFailed:: @ Gfx12 in 0x08547370
	.4byte MissionFailed_Tiles-. @ data: 0x08551E44 = .+43732
	.4byte (MissionFailed_Pal - MissionFailed_Tiles) | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
	gPalette_MissionFailed::
		.4byte MissionFailed_Pal-. @ data: 0x08552168 = .+44524
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Gfx13 in 0x08547384
	.4byte Gfx08547384_Tiles-.
	.4byte (Gfx08547384_Pal - Gfx08547384_Tiles) | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
.if ENGLISH
	.2byte 256, (LZ77 | BPP4) 
.else
	.2byte 256, BPP4 
.endif 	@ rowsize(unused), props
		@ Palette
		.4byte Gfx08547384_Pal-.
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Gfx14 in 0x08547398
	.4byte _gfx_08552AE8-.
	.4byte 832 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_08552E28-.
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Gfx15 in 0x085473AC
	.4byte _gfx_08552E48-.
	.4byte 1408 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_085533C8-.
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Gfx16 in 0x085473C0
	.4byte _gfx_085533E8-.
	.4byte 1564 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_08553A04-.
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

gGraphic_Unk17:: @ Gfx17 in 0x085473D4
	.4byte _gfx_08553A24-.
	.4byte 1344 | (896 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 168, BPP4 	@ rowsize(unused), props
	gPalette_Unk17::
		.4byte _gfx_08553F64-.
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

gGraphic_LogoDemo::	@ Gfx18 in 0x085473E8
	.4byte TitleLogo_Tiles-.
	.4byte (TitleLogo_Pal - TitleLogo_Tiles) | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, BPP4 	@ rowsize(unused), props
	gPalette_LogoDemo::
		.4byte TitleLogo_Pal-.
		.2byte 32 @ bytesize
		.byte 0, 1 @ lz77(bool8), dst = PaletteID

	@ Gfx19 in 0x085473FC
	.4byte MenuMain_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte MenuMain_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx20 in 0x08547410
	.4byte MenuMain_Tiles-.
	.4byte (MenuMain_Pal - MenuMain_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte MenuMain_Pal-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphic_ExSkillMenu::	@ Gfx21 in 0x08547424
	.4byte MenuExSkill_Tiles-.
	.4byte (MenuExSkill_Pal - MenuExSkill_Tiles) | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
	gPalette_ExSkillMenu::
		.4byte MenuExSkill_Pal-.
		.2byte 96 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

gGraphic_MiscMenu:: @ Gfx22 in 0x08547438
	.4byte MiscMenu_Tiles-. @ data: 0x08556B3C = .+63236
	.4byte (MiscMenu_Pal - MiscMenu_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
  gPalette_MiscMenu::
		.4byte MiscMenu_Pal-. @ data: 0x08558590 = .+69964
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphic_ElfMenu::	@ Gfx23 in 0x0854744C
	.4byte ElfMenu_Tiles-. @ data: 0x08558670 = .+70180
	.4byte (ElfMenu_Pal - ElfMenu_Tiles) | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
	gPalette_ElfMenu::
		.4byte ElfMenu_Pal-. @ data: 0x085592B4 = .+73308
		.2byte 160 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

gGraphic_Zero3D:: @ Gfx24 in 0x08547460
	.4byte Zero3D0_Tiles-. @ data: 0x08559354 = .+73460
	.4byte (Zero3D0_Pal - Zero3D0_Tiles) | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte Zero3D0_Pal-. @ data: 0x08559624 = .+74168
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

	@ Gfx25 in 0x08547474
	.4byte _gfx_08559644-.
	.4byte 688 | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_085598F4-.
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

	@ Gfx26 in 0x08547488
	.4byte _gfx_08559914-.
	.4byte 660 | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_08559BA8-.
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

	@ Gfx27 in 0x0854749C
	.4byte _gfx_08559BC8-.
	.4byte 588 | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_08559E14-.
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

	@ Gfx28 in 0x085474B0
	.4byte _gfx_08559E34-.
	.4byte 536 | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_0855A04C-.
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

	@ Gfx29 in 0x085474C4
	.4byte _gfx_0855A06C-.
	.4byte 592 | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_0855A2BC-.
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

	@ Gfx30 in 0x085474D8
	.4byte _gfx_0855A2DC-.
	.4byte 608 | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_0855A53C-.
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

	@ Gfx31 in 0x085474EC
	.4byte _gfx_0855A55C-.
	.4byte 624 | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_0855A7CC-.
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

	@ Gfx32 in 0x08547500
	.4byte _gfx_0855A7EC-.
	.4byte 636 | (384 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_0855AA68-.
		.2byte 32 @ bytesize
		.byte 0, 7 @ lz77(bool8), dst = PaletteID

gGraphics_ElfCat::	@ Gfx33 in 0x08547514
Graphic_ElfCat_Nurse:
	.4byte ElfCatNurse_Tiles-. @ data: 0x0855AA88 = .+79220
	.4byte (ElfCatNurse_Pal - ElfCatNurse_Tiles) | (576 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, (MAP2D | BPP4) 	@ rowsize, props
	gPalettes_ElfCat::
		.4byte ElfCatNurse_Pal-. @ data: 0x0855ACC8 = .+79784
		.2byte 32 @ bytesize
		.byte 0, 13 @ lz77(bool8), dst = PaletteID

Graphic_ElfCat_Animal: @ Gfx34 in 0x08547528
	.4byte ElfCatAnimal_Tiles-. @ data: 0x0855ACE8 = .+79808
	.4byte (ElfCatAnimal_Pal - ElfCatAnimal_Tiles) | (576 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, (MAP2D | BPP4) 	@ rowsize, props
		@ Palette
		.4byte ElfCatAnimal_Pal-. @ data: 0x0855AF28 = .+80372
		.2byte 32 @ bytesize
		.byte 0, 13 @ lz77(bool8), dst = PaletteID

Graphic_ElfCat_Hacker: @ Gfx35 in 0x0854753C
	.4byte ElfCatHacker_Tiles-. @ data: 0x0855AF48 = .+80396
	.4byte (ElfCatHacker_Pal - ElfCatHacker_Tiles) | (576 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, (MAP2D | BPP4) 	@ rowsize, props
		@ Palette
		.4byte ElfCatHacker_Pal-. @ data: 0x0855B188 = .+80960
		.2byte 32 @ bytesize
		.byte 0, 13 @ lz77(bool8), dst = PaletteID

Graphic_SecretDickBlue: @ Gfx36 in 0x08547550
	.4byte SecretDickBlue_Tiles-. @ data: 0x0855B1A8 = .+80984
	.4byte (SecretDickBlue_Pal - SecretDickBlue_Tiles) | (235 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, (MAP2D | BPP4) 	@ rowsize, props
		@ Palette
		.4byte SecretDickBlue_Pal-. @ data: 0x0855B2A8 = .+81228
		.2byte 32 @ bytesize
		.byte 0, 8 @ lz77(bool8), dst = PaletteID

Graphic_SecretDickRed: @ Gfx37 in 0x08547564
	.4byte SecretDickRed_Tiles-. @ data: 0x0855B2C8 = .+81252
	.4byte (SecretDickRed_Pal - SecretDickRed_Tiles) | (235 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 128, (MAP2D | BPP4) 	@ rowsize, props
		@ Palette
		.4byte SecretDickRed_Pal-. @ data: 0x0855B3C8 = .+81496
		.2byte 32 @ bytesize
		.byte 0, 8 @ lz77(bool8), dst = PaletteID

	@ Gfx38 in 0x08547578
	.4byte ElfCatNone_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte ElfCatNone_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

gGraphic_Unk39:: @ Gfx39 in 0x0854758C
	.4byte ElfCatNone_Tiles-. @ data: 0x0855B3E8 = .+81500
	.4byte (ElfCatNone_Pal - ElfCatNone_Tiles) | (576 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 288, (MAP2D | BPP4) 	@ rowsize, props
	gPalette_Unk39::
		.4byte ElfCatNone_Pal-. @ data: 0x0855B628 = .+82064
		.2byte 32 @ bytesize
		.byte 0, 13 @ lz77(bool8), dst = PaletteID

gGraphics_CyberElfTab:: @ Gfx40 in 0x085475A0
	.4byte ElfTabNurse_Tiles-. @ data: 0x0855B648 = .+82088
	.4byte (ElfTabNurse_Pal - ElfTabNurse_Tiles) | (672 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (MAP2D | BPP4) 	@ rowsize, props
  gPalettes_CyberElfTab:: @ Palette
		.4byte ElfTabNurse_Pal-. @ data: 0x0855B848 = .+82588
		.2byte 32 @ bytesize
		.byte 0, 11 @ lz77(bool8), dst = PaletteID

	@ Gfx41 in 0x085475B4
	.4byte ElfTabAnimal_Tiles-. @ data: 0x0855B868 = .+82612
	.4byte (ElfTabAnimal_Pal - ElfTabAnimal_Tiles) | (672 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (MAP2D | BPP4) 	@ rowsize, props
		@ Palette
		.4byte ElfTabAnimal_Pal-. @ data: 0x0855BA68 = .+83112
		.2byte 32 @ bytesize
		.byte 0, 11 @ lz77(bool8), dst = PaletteID

	@ Gfx42 in 0x085475C8
	.4byte ElfTabHacker_Tiles-. @ data: 0x0855BA88
	.4byte (ElfTabHacker_Pal - ElfTabHacker_Tiles) | (672 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (MAP2D | BPP4) 	@ rowsize, props
		@ Palette
		.4byte ElfTabHacker_Pal-. @ data: 0x0855BC88
		.2byte 32 @ bytesize
		.byte 0, 11 @ lz77(bool8), dst = PaletteID

gGraphic_CodeName:: @ Gfx43 in 0x085475DC
	.4byte CodeName_Tiles-. @ data: 0x0855BCA8
	.4byte (CodeName_Pal - CodeName_Tiles) | (768 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
  gPalette_CodeName::
		.4byte CodeName_Pal-. @ data: 0x0855C694
		.2byte 32 @ bytesize
		.byte 0, 15 @ lz77(bool8), dst = PaletteID

@ ここから gGraphic_GameOverString まで Gfx44 .. Gfx101 は　タイルマップのみ?
@ 多分タイルデータは、ステージと同じものを使って、タイルマップのみこっちで用意していると思われる

	@ Gfx44 in 0x085475F0
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx45 in 0x08547604
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx46 in 0x08547618
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx47 in 0x0854762C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx48 in 0x08547640
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx49 in 0x08547654
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx50 in 0x08547668
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx51 in 0x0854767C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx52 in 0x08547690
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx53 in 0x085476A4
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx54 in 0x085476B8
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx55 in 0x085476CC
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx56 in 0x085476E0
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx57 in 0x085476F4
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx58 in 0x08547708
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx59 in 0x0854771C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx60 in 0x08547730
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx61 in 0x08547744
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx62 in 0x08547758
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx63 in 0x0854776C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx64 in 0x08547780
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx65 in 0x08547794
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx66 in 0x085477A8
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx67 in 0x085477BC
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx68 in 0x085477D0
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx69 in 0x085477E4
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx70 in 0x085477F8
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx71 in 0x0854780C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx72 in 0x08547820
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx73 in 0x08547834
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx74 in 0x08547848
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx75 in 0x0854785C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx76 in 0x08547870
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx77 in 0x08547884
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx78 in 0x08547898
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx79 in 0x085478AC
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx80 in 0x085478C0
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx81 in 0x085478D4
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx82 in 0x085478E8
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx83 in 0x085478FC
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx84 in 0x08547910
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx85 in 0x08547924
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx86 in 0x08547938
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx87 in 0x0854794C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx88 in 0x08547960
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx89 in 0x08547974
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx90 in 0x08547988
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx91 in 0x0854799C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx92 in 0x085479B0
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx93 in 0x085479C4
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx94 in 0x085479D8
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx95 in 0x085479EC
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx96 in 0x08547A00
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx97 in 0x08547A14
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx98 in 0x08547A28
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx99 in 0x08547A3C
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx100 in 0x08547A50
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx101 in 0x08547A64
	.4byte GameOverString_Tiles-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte GameOverString_Tiles-.
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

gGraphic_GameOverString:: @ Gfx102 in 0x08547A78
	.4byte GameOverString_Tiles-. @ data: 0x0855C6B4
	.4byte (GameOverString_Pal - GameOverString_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
  gPalette_GameOverString::
		.4byte GameOverString_Pal-. @ data: 0x0855CC30
		.2byte 64 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Gfx103 in 0x08547A8C
	.4byte dummy-. @ data: 0x0855CC70 = .+86500
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86488
		.2byte 0 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Gfx104 in 0x08547AA0
	.4byte dummy-. @ data: 0x0855CC70 = .+86480
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86468
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx105 in 0x08547AB4
	.4byte dummy-. @ data: 0x0855CC70 = .+86460
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86448
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx106 in 0x08547AC8
	.4byte dummy-. @ data: 0x0855CC70 = .+86440
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86428
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx107 in 0x08547ADC
	.4byte dummy-. @ data: 0x0855CC70 = .+86420
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86408
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx108 in 0x08547AF0
	.4byte dummy-. @ data: 0x0855CC70 = .+86400
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86388
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx109 in 0x08547B04
	.4byte dummy-. @ data: 0x0855CC70 = .+86380
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86368
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx110 in 0x08547B18
	.4byte dummy-. @ data: 0x0855CC70 = .+86360
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86348
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx111 in 0x08547B2C
	.4byte dummy-. @ data: 0x0855CC70 = .+86340
	.4byte (Recap_Tiles - dummy) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, 0 	@ rowsize(unused), props
		@ Palette
		.4byte dummy-. @ data: 0x0855CC70 = .+86328
		.2byte 0 @ bytesize
		.byte 0, 0 @ lz77(bool8), dst = PaletteID

	@ Gfx112 in 0x08547B40
	.4byte Recap_Tiles-. @ data: 0x0855CC70 = .+86320
	.4byte (Recap_Pal - Recap_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte Recap_Pal-. @ data: 0x08560BC8 = .+102524
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphic_CsOmegaShip::	@ Gfx113 in 0x08547B54
	.4byte CsOmegaShip_Tiles-. @ data: 0x08560BE8 = .+102548
	.4byte (CsOmegaShip_Pal - CsOmegaShip_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
	gPalette_CsOmegaShip::
		.4byte CsOmegaShip_Pal-. @ data: 0x08566C64 = .+127236
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx114 in 0x08547B68
	.4byte CsDarkElf_Tiles-. @ data: 0x08566D44 = .+127452
	.4byte (CsDarkElf_Pal - CsDarkElf_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte CsDarkElf_Pal-. @ data: 0x08568AF0 = .+135036
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx115 in 0x08547B7C
	.4byte CsOmegaCall_Tiles-. @ data: 0x08568B10 = .+135060
	.4byte (CsOmegaCall_Pal - CsOmegaCall_Tiles) | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte CsOmegaCall_Pal-. @ data: 0x0856D4AC = .+153892
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx116 in 0x08547B90
	.4byte _gfx_0856D58C-.
	.4byte 27280 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte _gfx_0857401C-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx117 in 0x08547BA4
	.4byte _gfx_085740FC-.
	.4byte 16324 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x3fc4)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx118 in 0x08547BB8
	.4byte (_gfx_085740FC+0x40a4)-.
	.4byte 16140 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x7fb0)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx119 in 0x08547BCC
	.4byte (_gfx_085740FC+0x8090)-.
	.4byte 17416 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0xc498)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx120 in 0x08547BE0
	.4byte (_gfx_085740FC+0xc578)-.
	.4byte 10884 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0xeffc)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx121 in 0x08547BF4
	.4byte (_gfx_085740FC+0xf0dc)-.
	.4byte 31544 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x16c14)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx122 in 0x08547C08
	.4byte (_gfx_085740FC+0x16cf4)-.
	.4byte 18080 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x1b394)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx123 in 0x08547C1C
	.4byte (_gfx_085740FC+0x1b474)-.
	.4byte 22744 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x20d4c)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx124 in 0x08547C30
	.4byte (_gfx_085740FC+0x20e2c)-.
	.4byte 9276 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x23268)-.
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx125 in 0x08547C44
	.4byte (_gfx_085740FC+0x23288)-.
	.4byte 15380 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x26e9c)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx126 in 0x08547C58
	.4byte (_gfx_085740FC+0x26f7c)-.
	.4byte 9664 | (64 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x2953c)-.
		.2byte 32 @ bytesize
		.byte 0, 10 @ lz77(bool8), dst = PaletteID

	@ Gfx127 in 0x08547C6C
	.4byte (_gfx_085740FC+0x2955c)-.
	.4byte 15720 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP8) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x2d2c4)-.
		.2byte 224 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx128 in 0x08547C80
	.4byte (_gfx_085740FC+0x2d3a4)-.
	.4byte 2500 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x2dd68)-.
		.2byte 96 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphic_OpeningAnim0:: @ Gfx129 in 0x08547C94
	.4byte (_gfx_085740FC+0x2ddc8)-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, LZ77 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x2ddc8)-.
		.2byte 0 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphic_OpeningAnim1:: @ Gfx130 in 0x08547CA8
	.4byte (_gfx_085740FC+0x2ddc8)-.
	.4byte 12252 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | BPP4) 	@ rowsize(unused), props
  gPalette_OpeningAnim1::
		.4byte (_gfx_085740FC+0x30da4)-.
		.2byte 32 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphic_OpeningAnim2:: @ Gfx131 in 0x08547CBC
	.4byte (_gfx_085740FC+0x30dc4)-.
	.4byte 12184 | (512 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 256, (LZ77 | NO_PAL | BPP4) 	@ rowsize(unused), props
  gPalette_OpeningAnim2:: @ Palette
		.4byte (_gfx_085740FC+0x33d5c)-.
		.2byte 0 @ bytesize
		.byte 0, 9 @ lz77(bool8), dst = PaletteID

	@ Gfx132 in 0x08547CD0
	.4byte (_gfx_085740FC+0x33d5c)-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, LZ77 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x33d5c)-.
		.2byte 0 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

	@ Gfx133 in 0x08547CE4
	.4byte (_gfx_085740FC+0x33d5c)-.
	.4byte 0 | (0 << 22) 	@ bit0..21: bytesize, bit22..31: dst (VRAM TileID)
	.2byte 0, LZ77 	@ rowsize(unused), props
		@ Palette
		.4byte (_gfx_085740FC+0x33d5c)-.
		.2byte 0 @ bytesize
		.byte 0, 2 @ lz77(bool8), dst = PaletteID

gGraphicData::

Capcom_Tiles:
  .if ENGLISH
    .incbin "graphics/bg/capcom-en.4bpp.lz"
  .else
    .incbin "graphics/bg/capcom.4bpp.lz"
  .endif
Capcom_Pal:
  .if ENGLISH
  .incbin "graphics/bg/capcom-en.gbapal"
  .else
  .incbin "graphics/bg/capcom.gbapal"
  .endif

Inti_Tiles:
  .if ENGLISH
    .incbin "graphics/bg/inti-en.4bpp.lz"
  .else
    .incbin "graphics/bg/inti.4bpp.lz"
  .endif
Inti_Pal:
  .incbin "graphics/bg/inti.gbapal"

Cutscene085472a8_Tiles:
.if ENGLISH
  .incbin "graphics/bg/cutscene_085472a8-en.bin"
.else
  .incbin "graphics/bg/cutscene_085472a8.bin"
.endif
Cutscene085472a8_End:

TitleZero_Tiles:
  .if ENGLISH
    .incbin "graphics/bg/title_zero-en.4bpp.lz"
  .else
    .incbin "graphics/bg/title_zero.4bpp.lz"
  .endif
TitleZero_Pal:
  .incbin "graphics/bg/title_zero.gbapal"

TitleCiel_Tiles:
  .if ENGLISH
    .incbin "graphics/bg/title_ciel-en.4bpp.lz"
  .else
    .incbin "graphics/bg/title_ciel.4bpp.lz"
  .endif
TitleCiel_Pal:
  .incbin "graphics/bg/title_ciel.gbapal"

HUD_Tiles:
  .incbin "graphics/bg/hp_gauge.4bpp"
HUD_Pal:
  .incbin "graphics/bg/hp_gauge.gbapal"

MissionStart_Tiles:
  .incbin "graphics/bg/mission_start.4bpp"
MissionStart_Pal:
  .incbin "graphics/bg/mission_start.gbapal"

MissionFailed_Tiles:
  .incbin "graphics/bg/mission_failed.4bpp.lz"
MissionFailed_Pal:
  .incbin "graphics/bg/mission_failed.gbapal"

Gfx08547384_Tiles:
.if ENGLISH
.incbin "graphics/bg/gfx_08547384-en.bin"
.else
.incbin "graphics/bg/gfx_08547384.4bpp"
.endif
Gfx08547384_Pal:
.incbin "graphics/bg/gfx_08547384.gbapal"

_gfx_08552AE8:
.incbin "graphics/bg/gfx_08547398.4bpp"
_gfx_08552E28:
.incbin "graphics/bg/gfx_08547398.gbapal"

_gfx_08552E48:
.incbin "graphics/bg/stage_clear.4bpp.lz"
_gfx_085533C8:
.incbin "graphics/bg/stage_clear.gbapal"

_gfx_085533E8:
.incbin "graphics/bg/game_over.4bpp.lz"
_gfx_08553A04:
.incbin "graphics/bg/game_over.gbapal"

_gfx_08553A24:
.incbin "graphics/bg/gfx_085473d4.4bpp"
_gfx_08553F64:
.incbin "graphics/bg/gfx_085473d4.gbapal"

TitleLogo_Tiles:
.if ENGLISH
.incbin "graphics/bg/title_logo-en.4bpp"
TitleLogo_Pal:
.incbin "graphics/bg/title_logo-en.gbapal"
.else
.incbin "graphics/bg/title_logo.4bpp"
TitleLogo_Pal:
.incbin "graphics/bg/title_logo.gbapal"
.endif
TitleLogo_End:

MenuMain_Tiles:
.if ENGLISH
  .incbin "graphics/bg/menu_main-en.4bpp.lz"
.else
  .incbin "graphics/bg/menu_main.4bpp.lz"
.endif
MenuMain_Pal:
.incbin "graphics/bg/menu_main.gbapal"
MenuMain_End:

MenuExSkill_Tiles:
.if ENGLISH
  .incbin "graphics/bg/menu_exskill-en.4bpp.lz"
.else
  .incbin "graphics/bg/menu_exskill.4bpp.lz"
.endif
MenuExSkill_Pal:
.incbin "graphics/bg/menu_exskill.gbapal"
MenuExSkill_End:

MiscMenu_Tiles:
  .if ENGLISH
    .incbin "graphics/bg/menu_others-en.4bpp.lz"
  .else
    .incbin "graphics/bg/menu_others.4bpp.lz"
  .endif
MiscMenu_Pal:
  .incbin "graphics/bg/menu_others.gbapal"

ElfMenu_Tiles:
  .if ENGLISH
    .incbin "graphics/bg/menu_elf-en.4bpp.lz"
  .else
    .incbin "graphics/bg/menu_elf.4bpp.lz"
  .endif
ElfMenu_Pal:
  .incbin "graphics/bg/menu_elf.gbapal"

Zero3D0_Tiles:
  .incbin "graphics/bg/zero_3d/0.4bpp.lz"
Zero3D0_Pal:
  .incbin "graphics/bg/zero_3d/0.gbapal"

_gfx_08559644:
.incbin "graphics/bg/zero_3d/1.4bpp.lz"
_gfx_085598F4:
.incbin "graphics/bg/zero_3d/1.gbapal"

_gfx_08559914:
.incbin "graphics/bg/zero_3d/2.4bpp.lz"
_gfx_08559BA8:
.incbin "graphics/bg/zero_3d/2.gbapal"

_gfx_08559BC8:
.incbin "graphics/bg/zero_3d/3.4bpp.lz"
_gfx_08559E14:
.incbin "graphics/bg/zero_3d/3.gbapal"

_gfx_08559E34:
.incbin "graphics/bg/zero_3d/4.4bpp.lz"
_gfx_0855A04C:
.incbin "graphics/bg/zero_3d/4.gbapal"

_gfx_0855A06C:
.incbin "graphics/bg/zero_3d/5.4bpp.lz"
_gfx_0855A2BC:
.incbin "graphics/bg/zero_3d/5.gbapal"

_gfx_0855A2DC:
.incbin "graphics/bg/zero_3d/6.4bpp.lz"
_gfx_0855A53C:
.incbin "graphics/bg/zero_3d/6.gbapal"

_gfx_0855A55C:
.incbin "graphics/bg/zero_3d/7.4bpp.lz"
_gfx_0855A7CC:
.incbin "graphics/bg/zero_3d/7.gbapal"

_gfx_0855A7EC:
.incbin "graphics/bg/zero_3d/8.4bpp.lz"
_gfx_0855AA68:
.incbin "graphics/bg/zero_3d/8.gbapal"

ElfCatNurse_Tiles:
  .if ENGLISH
  .incbin "graphics/bg/str_nurse_elf-en.4bpp"
  .else
  .incbin "graphics/bg/str_nurse_elf.4bpp"
  .endif
ElfCatNurse_Pal:
  .incbin "graphics/bg/str_nurse_elf.gbapal"

ElfCatAnimal_Tiles:
  .if ENGLISH
  .incbin "graphics/bg/str_animal_elf-en.4bpp"
  .else
  .incbin "graphics/bg/str_animal_elf.4bpp"
  .endif
ElfCatAnimal_Pal:
  .incbin "graphics/bg/str_animal_elf.gbapal"

ElfCatHacker_Tiles:
  .if ENGLISH
  .incbin "graphics/bg/str_hacker_elf-en.4bpp"
  .else
  .incbin "graphics/bg/str_hacker_elf.4bpp"
  .endif
ElfCatHacker_Pal:
  .incbin "graphics/bg/str_hacker_elf.gbapal"

SecretDickBlue_Tiles:
  .incbin "graphics/bg/secret_dick_blue.4bpp"
SecretDickBlue_Pal:
  .incbin "graphics/bg/secret_dick_blue.gbapal"

SecretDickRed_Tiles:
  .incbin "graphics/bg/secret_dick_red.4bpp"
SecretDickRed_Pal:
  .incbin "graphics/bg/secret_dick_red.gbapal"

ElfCatNone_Tiles:
  .incbin "graphics/bg/str_none_elf.4bpp"
ElfCatNone_Pal:
  .incbin "graphics/bg/str_none_elf.gbapal"

ElfTabNurse_Tiles:
  .incbin "graphics/bg/elftab/nurse.4bpp"
ElfTabNurse_Pal:
  .incbin "graphics/bg/elftab/nurse.gbapal"

ElfTabAnimal_Tiles:
  .incbin "graphics/bg/elftab/animal.4bpp"
ElfTabAnimal_Pal:
  .incbin "graphics/bg/elftab/animal.gbapal"

ElfTabHacker_Tiles:
  .incbin "graphics/bg/elftab/hacker.4bpp"
ElfTabHacker_Pal:
  .incbin "graphics/bg/elftab/hacker.gbapal"

CodeName_Tiles:
.if ENGLISH
  .incbin "graphics/bg/codename-en.4bpp.lz"
.else
  .incbin "graphics/bg/codename.4bpp.lz"
.endif
CodeName_Pal:
  .if ENGLISH
  .incbin "graphics/bg/codename-en.gbapal"
  .else
  .incbin "graphics/bg/codename.gbapal"
  .endif

GameOverString_Tiles:
  .if ENGLISH
    .incbin "graphics/bg/game_over_screen-en.4bpp.lz"
  .else
    .incbin "graphics/bg/game_over_screen.4bpp.lz"
  .endif
GameOverString_Pal:
  .incbin "graphics/bg/game_over_screen.gbapal"

dummy:

Recap_Tiles:
  .incbin "graphics/bg/cutscene_recap.4bpp.lz"
Recap_Pal:
  .incbin "graphics/bg/cutscene_recap.gbapal"

CsOmegaShip_Tiles:
  .incbin "graphics/bg/8bpp/cutscene_omegaship.8bpp.lz"
CsOmegaShip_Pal:
  .incbin "graphics/bg/8bpp/cutscene_omegaship.gbapal"

CsDarkElf_Tiles:
  .incbin "graphics/bg/cutscene_darkelf.4bpp.lz"
CsDarkElf_Pal:
  .incbin "graphics/bg/cutscene_darkelf.gbapal"

CsOmegaCall_Tiles:
  .incbin "graphics/bg/8bpp/cutscene_comeon_zero.8bpp.lz"
CsOmegaCall_Pal:
  .incbin "graphics/bg/8bpp/cutscene_comeon_zero.gbapal"

_gfx_0856D58C:
.incbin "graphics/bg/8bpp/cutscene_omega_white.8bpp.lz"
_gfx_0857401C:
.incbin "graphics/bg/8bpp/cutscene_omega_white.gbapal"

_gfx_085740FC:
.if ENGLISH
.incbin "graphics/bg/bg-en.bin"
.else
.incbin "graphics/bg/bg.bin"
.endif
