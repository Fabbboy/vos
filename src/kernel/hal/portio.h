#include <stdint.h>
#include "../utils/binary.h"

/**
 * @brief Writes a byte to the specified I/O port.
 *
 * This function writes a byte value to the specified I/O port.
 *
 * @param port The I/O port to write to.
 * @param val The byte value to write.
 */
static inline void outb(uint16_t port, uint8_t val) {
  asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

/**
 * @brief Reads a byte from the specified I/O port.
 *
 * This function reads a byte value from the specified I/O port and returns it.
 *
 * @param port The I/O port to read from.
 * @return The byte value read from the port.
 */
static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/**
 * @brief Reads a word (16 bits) from the specified I/O port.
 *
 * This function reads a word value from the specified I/O port and returns it.
 *
 * @param port The I/O port to read from.
 * @return The word value read from the port.
 */
static inline uint16_t inw(uint16_t port) {
  uint16_t ret;
  asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/**
 * @brief Writes a word (16 bits) to the specified I/O port.
 *
 * This function writes a word value to the specified I/O port.
 *
 * @param port The I/O port to write to.
 * @param val The word value to write.
 */
static inline void outw(uint16_t port, uint16_t val) {
  asm volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

/**
 * @brief Performs an I/O wait.
 *
 * This function performs an I/O wait by writing to the I/O port 0x80.
 * It is used to introduce a delay in I/O operations.
 */
static inline void io_wait(void) {
  asm volatile("outb %%al, $0x80" : : "a"(0));
}
/**
 * Enables interrupts.
 */
static inline void enable_interrupts() { asm volatile("sti"); }

/**
 * Disables interrupts.
 */
static inline void disable_interrupts() { asm volatile("cli"); }