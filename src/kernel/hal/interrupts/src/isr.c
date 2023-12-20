#include "../isr.h"
#include "../../../lib/error.h"
#include "../../../lib/string.h"

ISR_Handler isr_handlers[256];

static char* const g_Exceptions[] = {
        "Divide by zero error",
        "Debug",
        "Non-maskable Interrupt",
        "Breakpoint",
        "Overflow",
        "Bound Range Exceeded",
        "Invalid Opcode",
        "Device Not Available",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Invalid TSS",
        "Segment Not Present",
        "Stack-Segment Fault",
        "General Protection Fault",
        "Page Fault",
        "",
        "x87 Floating-Point Exception",
        "Alignment Check",
        "Machine Check",
        "SIMD Floating-Point Exception",
        "Virtualization Exception",
        "Control Protection Exception",
        "",
        "",
        "",
        "",
        "",
        "",
        "Hypervisor Injection Exception",
        "VMM Communication Exception",
        "Security Exception",
        ""
};

void __attribute__((cdecl)) isr_0_handler();
void __attribute__((cdecl)) isr_1_handler();
void __attribute__((cdecl)) isr_2_handler();
void __attribute__((cdecl)) isr_3_handler();
void __attribute__((cdecl)) isr_4_handler();
void __attribute__((cdecl)) isr_5_handler();
void __attribute__((cdecl)) isr_6_handler();
void __attribute__((cdecl)) isr_7_handler();
void __attribute__((cdecl)) isr_8_handler();
void __attribute__((cdecl)) isr_9_handler();
void __attribute__((cdecl)) isr_10_handler();
void __attribute__((cdecl)) isr_11_handler();
void __attribute__((cdecl)) isr_12_handler();
void __attribute__((cdecl)) isr_13_handler();
void __attribute__((cdecl)) isr_14_handler();
void __attribute__((cdecl)) isr_15_handler();
void __attribute__((cdecl)) isr_16_handler();
void __attribute__((cdecl)) isr_17_handler();
void __attribute__((cdecl)) isr_18_handler();
void __attribute__((cdecl)) isr_19_handler();
void __attribute__((cdecl)) isr_20_handler();
void __attribute__((cdecl)) isr_21_handler();
void __attribute__((cdecl)) isr_22_handler();
void __attribute__((cdecl)) isr_23_handler();
void __attribute__((cdecl)) isr_24_handler();
void __attribute__((cdecl)) isr_25_handler();
void __attribute__((cdecl)) isr_26_handler();
void __attribute__((cdecl)) isr_27_handler();
void __attribute__((cdecl)) isr_28_handler();
void __attribute__((cdecl)) isr_29_handler();
void __attribute__((cdecl)) isr_30_handler();
void __attribute__((cdecl)) isr_31_handler();

void isr_init_gates() {
  idt_set_gate(0, (uint32_t)isr_0_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(1, (uint32_t)isr_1_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(2, (uint32_t)isr_2_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(3, (uint32_t)isr_3_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(4, (uint32_t)isr_4_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(5, (uint32_t)isr_5_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(6, (uint32_t)isr_6_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(7, (uint32_t)isr_7_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);

  idt_set_gate(8, (uint32_t)isr_8_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(9, (uint32_t)isr_9_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(10, (uint32_t)isr_10_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(11, (uint32_t)isr_11_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(12, (uint32_t)isr_12_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(13, (uint32_t)isr_13_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(14, (uint32_t)isr_14_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(15, (uint32_t)isr_15_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);

  idt_set_gate(16, (uint32_t)isr_16_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(17, (uint32_t)isr_17_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(18, (uint32_t)isr_18_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(19, (uint32_t)isr_19_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);

  idt_set_gate(20, (uint32_t)isr_20_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(21, (uint32_t)isr_21_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(22, (uint32_t)isr_22_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(23, (uint32_t)isr_23_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);

  idt_set_gate(24, (uint32_t)isr_24_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(25, (uint32_t)isr_25_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(26, (uint32_t)isr_26_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(27, (uint32_t)isr_27_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);

  idt_set_gate(28, (uint32_t)isr_28_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(29, (uint32_t)isr_29_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(30, (uint32_t)isr_30_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
  idt_set_gate(31, (uint32_t)isr_31_handler, GDT_CODE_SEGMENT,
               IDT_FLAG_GATE_32BIT_INT | IDT_FLAG_RING_0 | IDT_FLAG_PRESENT);
}

void isr_init() {
  isr_init_gates();
  for (int i = 0; i < 32; i++) {
    idt_enable_gate(i);
  }

};

void isr_handler_register(uint8_t index, ISR_Handler handler) {
  isr_handlers[index] = handler;
};


void __attribute__((cdecl)) isr_handler(registers_t *regs) {
  if (isr_handlers[regs->int_no] != 0) {
    isr_handlers[regs->int_no](regs);
  } else if (regs->int_no < 32) {
    serial_write_hex(COM1, regs->int_no);
    serial_write(COM1, " ", 1);
    serial_write(COM1, g_Exceptions[regs->int_no], strlen(g_Exceptions[regs->int_no]));
    serial_write(COM1, "\n", 1);
    panic("", 0x01, COM1);
  }else {
    serial_write_hex(COM1, regs->int_no);
    serial_write(COM1, " ", 1);
    serial_write(COM1, "Unknown interrupt\n", 18);
    panic("", 0x01, COM1);
  }
}