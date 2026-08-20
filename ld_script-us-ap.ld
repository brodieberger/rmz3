/* US + Archipelago (REGION=us AP=1). Based on from ld_script-us.ld: ROM grows to 16M among other things */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY {
    ewram   : ORIGIN = 0x02000000, LENGTH = 256k
    iwram   : ORIGIN = 0x03000000, LENGTH = 32k
		rom     : ORIGIN = (0x08000000), LENGTH = 16M
}

gMaxLines = 0;
gNumMusicPlayers = 15;
gPadTerrainTail = 0;
gPadSpriteStaticTail = 0;
gPadSpriteDynamic = 0;

SECTIONS {
	. = 0x2000000;
	ewram (NOLOAD) :
	ALIGN(4)
    {
      INCLUDE "linker/ewram.txt"

      /* ARCHIPELAGO STATE. */
      . = ALIGN(4);
      __ap_ewram_start = .;
      src/ap.o (ewram_data);
      src/ap_stage_select.o (ewram_data);
      __ap_ewram_end = .;
    } >ewram = 0x00

	. = 0x3000000;
    iwram (NOLOAD) :
    ALIGN(4)
    {
        src/libs/m4a.o(.bss.code);
        INCLUDE "linker/iwram.txt"
    } >iwram = 0x00

    . = 0x8000000;
    .text :
    ALIGN(4)
    {
      src/rom_header.o (.text);
			src/crt0.o (.text);
			src/sprite2.o (.text);
			src/sprite2.o (.rodata);
			src/sprite2.o (.data);
			src/mmbn4.o (.rodata);
			src/mmbn4.o (.text);
			src/main.o (.text);
			INCLUDE "linker/text.txt"
    } >rom = 0x00

	lib_text 0x080FC024 :
	ALIGN(4)
	{
		src/libs/m4a_1.o (.text);
		src/libs/m4a.o (.text);
		src/libs/libagbsyscall.o (.text);
		src/libs/agb_sram.o (.text);
		*libgcc.a:*_call_via_rX*.o(.text);
		*libgcc.a:*_divsi3*.o(.text);
		*libgcc.a:*_dvmd_tls*.o(.text);
		*libgcc.a:*_modsi3*.o(.text);
		*libgcc.a:*_udivsi3*.o(.text);
		*libgcc.a:*_umodsi3*.o(.text);
		*libc.a:*memcpy*.o(.text);
		*libc.a:*memset*.o(.text);
	} >rom = 0x00

	.rodata 0x080FE64C :
	ALIGN(4)
	{
			INCLUDE "linker/rodata.txt"
	} >rom = 0x00

	/* Archipelago code and data, in the space the 16M expansion. */
	.ap_text :
	ALIGN(4)
	{
		__ap_rom_start = .;
		src/ap.o (.text);
		src/ap.o (.rodata);
		src/ap.o (.data);
		src/ap_cmd_room.o (.text);
		src/ap_cmd_room.o (.rodata);
		src/data/texts/ap_cmd_room.o (.rodata);
		src/ap_stage_select.o (.text);
		src/ap_stage_select.o (.rodata);
		src/ap_exlife_orbit.o (.text);
		src/ap_exlife_orbit.o (.rodata);
		src/ap_orbit_data.o (.rodata);
		. = ALIGN(4);
	} >rom = 0x00

	.ap_rodata :
	ALIGN(4)
	{
		__ap_rom_end = .;
	} >rom = 0x00

	/DISCARD/ :
    {
        *(*);
    }
}