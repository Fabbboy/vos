#include "lib/multiboot2.h"
#include <stdint.h>
#include "driver/serial/serial.h"
#include <stdbool.h>
#include "lib/string.h"

#define COM1 0x3F8

void kernel_main(uint32_t magic, uint32_t multiboot_info_ptr) {
  bool enable_debug = true;
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

  //TODO: maybe move this if while needs serial
  serial_cleanup(COM1);
  while (1);
}
