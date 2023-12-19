bits 32

extern isr_handler

%macro ISR 1
global isr_%1_handler
isr_%1_handler:
  push 0
  push %1
  jmp isr_common
%endmacro

%macro ISR_ERR 1
global isr_%1_handler
isr_%1_handler:
  push %1
  jmp isr_common
%endmacro



;;;; Exceptions
ISR 0 ; Divide by zero
ISR 1 ; Debug 
ISR 2 ; Non-maskable interrupt
ISR 3 ; Breakpoint
ISR 4 ; Overflow
ISR 5 ; Bound range exceeded
ISR 6 ; Invalid opcode
ISR 7 ; Device not available
ISR_ERR 8 ; Double fault
ISR 9 ; Coprocessor segment overrun
ISR_ERR 10 ; Invalid TSS
ISR_ERR 11 ; Segment not present
ISR_ERR 12 ; Stack-segment fault
ISR_ERR 13 ; General protection fault
ISR_ERR 14 ; Page fault
ISR 15 ; Reserved
ISR_ERR 16 ; x87 FPU floating-point error
ISR_ERR 17 ; Alignment check
ISR 18 ; Machine check
ISR 19 ; SIMD floating-point exception
ISR 20 ; Virtualization exception
ISR_ERR 21 ; Control protection exception
ISR 22 ; Reserved
ISR 23 ; Reserved
ISR 24 ; Reserved
ISR 25 ; Reserved
ISR 26 ; Reserved
ISR 27 ; Reserved
ISR 28 ; Hypervisor injection exception
ISR_ERR 29 ; VMM communication exception
ISR_ERR 30 ; Security exception
ISR 31 ; Reserved


isr_common:
  pusha     ; pushes edi, esi, ebp, esp, ebx, edx, ecx, eax

  xor eax, eax ; push ds
  mov ax, ds
  push eax

  mov ax, 0x10 ; load kernel data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  push esp ; push pointer to stack  
  call isr_handler
  add esp, 4 ; pop pointer to stack

  pop eax ; pop pointer to stack
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa ; pops edi, esi, ebp, esp, ebx, edx, ecx, eax
  add esp, 8 ; pops error code and interrupt number
  iret 