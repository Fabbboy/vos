#include "../irq.h"

IRQ_Handler irq_handlers[16];

void PIC_sendEOI(uint8_t irq) {
  if (irq >= 8) {
    outb(PIC2_COMMAND, PIC_EOI);
  }
  outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_remap(){
  uint8_t a1, a2;

  a1 = inb(PIC1_DATA);
  a2 = inb(PIC2_DATA);

  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

  outb(PIC1_DATA, 0x20);
  outb(PIC2_DATA, 0x28);

  outb(PIC1_DATA, 0x04);
  outb(PIC2_DATA, 0x02);

  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  outb(PIC1_DATA, a1);
  outb(PIC2_DATA, a2);
};

void PIC_disable(){
  outb(PIC1_DATA, 0xFF);
  outb(PIC2_DATA, 0xFF);
};

void irq_set_mask(uint8_t irq_line){
  uint16_t port;
  uint8_t value;

  if(irq_line < 8){
    port = PIC1_DATA;
  } else {
    port = PIC2_DATA;
    irq_line -= 8;
  }

  value = inb(port) | (1 << irq_line);
  outb(port, value);
};

void irq_clear_mask(uint8_t irq_line){
  uint16_t port;
  uint8_t value;

  if(irq_line < 8){
    port = PIC1_DATA;
  } else {
    port = PIC2_DATA;
    irq_line -= 8;
  }

  value = inb(port) & ~(1 << irq_line);
  outb(port, value);
};

void irq_register_handler(uint8_t irq_line, IRQ_Handler handler){
#ifdef DEBUG
  serial_write(COM1, "IRQ: Registering handler for IRQ ", 32);
  serial_write_hex(COM1, irq_line);
  serial_write(COM1, "\n", 1);
#endif
  irq_handlers[irq_line] = handler;
};

void irq_unregister_handler(uint8_t irq_line){
  irq_handlers[irq_line] = NULL;
};

void irq_handler(registers_t *regs){
#ifdef DEBUG
  serial_write(COM1, "IRQ: ", 5);
  serial_write_hex(COM1, regs->int_no);
  serial_write(COM1, "\n", 1);
#endif

  if(irq_handlers[regs->int_no] != NULL){
    irq_handlers[regs->int_no](regs);
  }
  PIC_sendEOI(regs->int_no);
};

void irq_init(){
  PIC_remap();
  for (int i = 0; i < 16; i++) {
    irq_register_handler(i + 32, irq_handler);
  }
}

uint16_t pic_get_irr(){
  outb(PIC1_COMMAND, PIC_READ_IRR);
  outb(PIC2_COMMAND, PIC_READ_IRR);
  return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
};
uint16_t pic_get_isr(){
  outb(PIC1_COMMAND, PIC_READ_ISR);
  outb(PIC2_COMMAND, PIC_READ_ISR);
  return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
};