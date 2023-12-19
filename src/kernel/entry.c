#include "driver/serial/serial.h"
#include "hal/interrupts/gdt.h"
#include "hal/interrupts/idt.h"
#include "lib/multiboot2.h"
#include "lib/string.h"
#include <stdbool.h>
#include <stdint.h>

#define COM1 0x3F8
bool enable_debug = true;

void kernel_main(uint32_t magic, uint32_t multiboot_info_ptr) {
  serial_init(COM1, 115200, 1);
  if (enable_debug) {
    serial_write(COM1, "Serial initialized on COM1\n", 27);
  }

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

  //// Load GDT
  init_gdt();
  if (enable_debug) {
    serial_write(COM1, "GDT initialized\n", 16);
  }
  idt_init();
  if (enable_debug) {
    serial_write(COM1, "IDT initialized\n", 16);
  }

  // TODO: maybe move this if while needs serial
  serial_cleanup(COM1);
  while (1)
    ;
}
