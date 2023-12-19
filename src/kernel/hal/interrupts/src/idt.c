#include "../idt.h"

idt_entry_t idt[256];
idt_descriptor_t idt_descriptor = {
    sizeof(idt) - 1, // Limit
    idt,             // Base
};

void idt_set_gate (uint8_t index, uint32_t base, uint16_t selector, uint8_t flags){
  idt[index].base_low = base & 0xFFFF;
  idt[index].base_high = (base >> 16) & 0xFFFF;
  idt[index].selector = selector;
  idt[index].reserved = 0;
  idt[index].flags = flags;
};

void idt_enable_gate(uint8_t index){
  SET_FLAG(idt[index].flags, IDT_FLAG_PRESENT);
};

void idt_disable_gate(uint8_t index){
  UNSET_FLAG(idt[index].flags, IDT_FLAG_PRESENT);
};

void idt_init(){
  idt_load(&idt_descriptor);
};

bool verify_idt(){
  if (idt_descriptor.limit != sizeof(idt) - 1){
    return false;
  }

  if (idt_descriptor.base != idt){
    return false;
  }

  return true;
};