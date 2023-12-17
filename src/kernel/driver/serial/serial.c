#include "serial.h"

void serial_init(uint16_t com, uint32_t baud_rate, uint8_t divisor) {
  outb(com + 1, 0x00); // Disable all interrupts
  outb(com + 3, 0x80); // Enable DLAB (set baud rate divisor)
  outb(com + 0, divisor & 0xFF); // Set divisor (lo byte)
  outb(com + 1, divisor >> 8); // Set divisor (hi byte)
  outb(com + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(com + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  outb(com + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

void serial_cleanup(uint16_t com){
  outb(com + 1, 0x00); // Disable all interrupts
  outb(com + 3, 0x00); // Disable DLAB (set baud rate divisor)
  outb(com + 2, 0x00); // Disable FIFO, clear them, with 14-byte threshold
  outb(com + 4, 0x00); // IRQs disabled, RTS/DSR set
};

bool serial_is_transmit_fifo_empty(uint16_t com) {
  return inb(com + 5) & 0x20;
}

bool serial_received(uint16_t com) {
  return inb(com + 5) & 1;
}

void serial_write(uint16_t com, char* data, uint32_t length) {
  for (uint32_t i = 0; i < length; i++) {
    while (!serial_is_transmit_fifo_empty(com));
    outb(com, data[i]);
  }
}

void serial_write_hex(uint16_t com, uint32_t data){
  char* hex = "0123456789ABCDEF";
  char* hex_data = "0x00000000";
  for (int i = 0; i < 8; i++) {
    hex_data[2 + i] = hex[(data >> (28 - (i * 4))) & 0xF];
  }
  serial_write(com, hex_data, 10);
};

char* serial_read(uint16_t com, uint32_t length){
  char* data = "";
  for (uint32_t i = 0; i < length; i++) {
    while (!serial_received(com));
    data[i] = serial_read_byte(com);
  }
  return data;
};
char serial_read_byte(uint16_t com){
  while (!serial_received(com));
  return inb(com);
};
