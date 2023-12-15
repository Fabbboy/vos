ENTRY(kentry)

SECTIONS {
  . = 1M;

	.boot :
	{
		KEEP(*(.multiboot_header))
	}

  .text : {
  *(.text)
  }


  .data : {
    data_start = .;
    *(.data)
    data_end = .;
  }

  .rodata : {
    rodata_start = .;
    *(.rodata)
    rodata_end = .;
  }

  .bss : {
    bss_start = .;
    *(.bss)
    bss_end = .;
  }
}