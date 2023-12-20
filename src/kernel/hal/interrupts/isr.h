#pragma once
#include "../../driver/serial/serial.h"
#include "../../globals.h"
#include "gdt.h"
#include "idt.h"
#include <stdint.h>

typedef struct {
  uint32_t ds;                                     // Data segment selector
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
  uint32_t int_no, err_code; // Interrupt number and error code (if applicable)
  uint32_t eip, cs, eflags, useresp,
      ss; // Pushed by the processor automatically.
} __attribute__((packed)) registers_t;

typedef void (*ISR_Handler)(registers_t *);

void __attribute__((cdecl)) isr_handler(registers_t *regs);
void isr_init_gates();
void isr_init();

void isr_handler_register(uint8_t index, ISR_Handler handler);
