; void __attribute__((cdecl)) idt_load(idt_register_t* idt_register);
bits 32
global idt_load
idt_load:
  ; setup new call frame
  push ebp
  mov ebp, esp

  ; load idt 
  mov eax, [ebp + 8]
  lidt [eax]

  ; restore registers
  mov esp, ebp
  pop ebp
  ret