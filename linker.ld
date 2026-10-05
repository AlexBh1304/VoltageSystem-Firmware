ENTRY(_resethandler)

MEMORY
{
	FLASH (rx) : ORIGIN =0x00000000, LENGTH =16K
	SRAM (rwx) : ORIGIN =0x20000000, LENGTH =2K
}

SECTIONS
{

	.text :
	{
		*(.lol)
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_etext = .;

	}> FLASH
	
	.data :
	{
		_sdata = .;
		*(.data)
		. = ALIGN(4);
		_edata = .;


	}> SRAM AT> FLASH

	.bss :
	{
		_sbss = .;
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;

	}> SRAM

}

_stack_top = ORIGIN(SRAM) + LENGTH(SRAM);
