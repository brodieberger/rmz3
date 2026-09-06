/* US (REGION=us) "flat" layout: ld_script-modern.ld plus the US gap symbols.
   Pins no addresses and orders nothing by hand -- every section is placed by
   wildcard. Used by the two configurations whose code sizes do not match the
   vanilla ROM's: MODERN (gcc instead of agbcc) and CBODY (asm bodies replaced
   by their C equivalents). ld_script-us.ld cannot be reused for either, since
   it hard-codes the vanilla layout. */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY {
    ewram   : ORIGIN = 0x02000000, LENGTH = 4M - 4k
    iwram   : ORIGIN = 0x03000000, LENGTH = 32k
	  rom     : ORIGIN = (0x08000000), LENGTH = 32M
}

gMaxLines = 0;
gNumMusicPlayers = 15;

/* US .rodata fill before sprite_dynamic; us_gap.o supplies the real gap. */
gPadTerrainTail = 0;
gPadSpriteStaticTail = 0;
gPadSpriteDynamic = 0;

SECTIONS {
	. = 0x2000000;
	ewram (NOLOAD) :
	ALIGN(4)
    {
      INCLUDE "linker/ewram.txt"
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
      src/rom_header.o (.text*);
			src/crt0.o (.text);
			src/sprite2.o (.text);
			src/sprite2.o (.rodata);
			src/sprite2.o (.data);
      src/mmbn4.o (.rodata);
			src/mmbn4.o (.text);
			src/main.o (.text);
      /* INCLUDE "linker/text.txt" */
      *(.text*);
    } >rom = 0x00

	.data :
	ALIGN(4)
	{
		*(.data*);
	} >rom = 0x00

	.rodata :
	ALIGN(4)
	{
    /* INCLUDE "linker/rodata.txt" */
		*(.rodata*);
	} >rom = 0x00

    /* Discard everything not specifically mentioned above. */
	/DISCARD/ :
    {
        *(*);
    }
}
