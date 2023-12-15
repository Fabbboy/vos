ENTRY(kentry)

SECTIONS {
  . = 1M;
  .multiboot_header : { *(.multiboot_header) }
  .text : {
    text_start = .;
    *(.text)
    text_end = .;
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