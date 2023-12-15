section .multiboot_header
align 4
  dd 0xE85250D6
  db 0x0
  db 0x2
  db -(0xE85250D6 + 0x0 + 0x2)
  dd 0x100000
  



section .text 
global kentry 
bits 32
kentry:
  jmp $