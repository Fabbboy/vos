; void __attribute__((cdecl)) gdt_load(gdt_descriptor_t *gdt_descriptor, uint16_t code_selector, uint16_t data_selector);
bits 32
global gdt_load
gdt_load:
  ; make a new call frame
  push ebp
  mov ebp, esp