#include "driver/serial/serial.h"
#include "driver/serial/serial_utils.h"
#include "hal/interrupts/gdt.h"
#include "hal/interrupts/idt.h"
#include "hal/interrupts/isr.h"
#include "lib/multiboot2.h"
#include "lib/string.h"
#include <stdbool.h>
#include <stdint.h>
#include "globals.h"

void hal_init() {
  init_gdt();
#ifdef DEBUG
  serial_write(COM1, "GDT initialized\n", 16);
  if (verify_gdt()) {
    serial_write(COM1, "GDT verified\n", 13);
  } else {
    serial_write(COM1, "GDT verification failed\n", 24);
  }
#endif
  idt_init();
#ifdef DEBUG

  serial_write(COM1, "IDT initialized\n", 16);
  if (verify_idt()) {
    serial_write(COM1, "IDT verified\n", 13);
  } else {
    serial_write(COM1, "IDT verification failed\n", 24);
  }

#endif
  isr_init();
#ifdef DEBUG
  serial_write(COM1, "ISR initialized\n", 16);
#endif
}

void kernel_main(uint32_t magic, uint32_t multiboot_info_ptr) {
  serial_init(COM1, 115200, 1);
#ifdef DEBUG
  serial_write(COM1, "Serial initialized on COM1\n", 27);
#endif

  if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
    serial_write(COM1, "Invalid magic number\n", 21);
    serial_write_hex(COM1, magic);
    serial_write(COM1, ":", 1);
    serial_write_hex(COM1, MULTIBOOT2_BOOTLOADER_MAGIC);
    serial_write(COM1, "\n", 1);
    return;
  }

  /// Extract informations from multiboot2 header
  struct multiboot_header_tag *tag =
      (struct multiboot_header_tag *)multiboot_info_ptr;

  //// Load IDT and GDT
  hal_init();

  // TODO: maybe move this if while needs serial
  serial_cleanup(COM1);
  while (1)
    ;
}
