#pragma once 
#include <stdbool.h>
#include <stdint.h>
#include "../../utils/binary.h"

typedef struct {
  uint16_t base_low;
  uint16_t selector;
  uint8_t reserved;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
  uint16_t limit;
  idt_entry_t* base;
} __attribute__((packed)) idt_descriptor_t;

typedef enum {
  IDT_FLAG_GATE_TASK = 0x5,
  IDT_FLAG_GATE_16BIT_INT = 0x6,
  IDT_FLAG_GATE_16BIT_TRAP = 0x7,
  IDT_FLAG_GATE_32BIT_INT = 0xE,
  IDT_FLAG_GATE_32BIT_TRAP = 0xF,

  IDT_FLAG_RING_0 = (0x00 << 5),
  IDT_FLAG_RING_1 = (0x01 << 5),
  IDT_FLAG_RING_2 = (0x02 << 5),
  IDT_FLAG_RING_3 = (0x03 << 5),
  
  IDT_FLAG_PRESENT = 0x80,
} idt_flags;


extern idt_entry_t idt[256];
extern idt_descriptor_t idt_descriptor;

void __attribute__((cdecl)) idt_load(idt_descriptor_t* idt_descriptor);
void idt_set_gate (uint8_t index, uint32_t base, uint16_t selector, uint8_t flags);
void idt_enable_gate(uint8_t index);
void idt_disable_gate(uint8_t index);
void idt_init();