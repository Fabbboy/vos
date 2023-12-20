#include "isr.h"
#include "stddef.h"
#include "../../globals.h"

#define PIC1 0x20 // Master PIC
#define PIC2 0xA0 // Slave PIC
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI 0x20

#define ICW1_ICW4 0x01      /* ICW4 (not) needed */
#define ICW1_SINGLE 0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08     /* Level triggered (edge) mode */
#define ICW1_INIT 0x10      /* Initialization - required! */

#define ICW4_8086 0x01       /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02       /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08  /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10       /* Special fully nested (not) */

#define PIC_READ_IRR 0x0a
#define PIC_READ_ISR 0x0b

typedef void (*IRQ_Handler)(registers_t *);

// EOI = End Of Interrupt
void PIC_sendEOI(uint8_t irq);

void PIC_remap();
void PIC_disable();

void irq_set_mask(uint8_t irq_line);
void irq_clear_mask(uint8_t irq_line);

void irq_register_handler(uint8_t irq_line, IRQ_Handler handler);
void irq_unregister_handler(uint8_t irq_line);

void irq_init();

uint16_t pic_get_irr();
uint16_t pic_get_isr();