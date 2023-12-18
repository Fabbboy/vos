/**
 * @file serial.h
 * @brief Header file for serial communication driver.
 */

#pragma once
#include <stdint.h>
#include "../../hal/portio.h"
#include <stdbool.h>

/**
 * @brief Initializes the serial communication.
 * 
 * @param com The COM port number.
 * @param baud_rate The baud rate for serial communication.
 * @param divisor The divisor value for setting the baud rate.
 */
void serial_init(uint16_t com, uint32_t baud_rate, uint8_t divisor);
/**
 * @brief Cleans up the serial port with the specified COM number.
 *
 * @param com The COM number of the serial port to clean up.
 */
void serial_cleanup(uint16_t com);

/**
 * @brief Checks if the transmit FIFO is empty.
 * 
 * @param com The COM port number.
 * @return true if the transmit FIFO is empty, false otherwise.
 */
bool serial_is_transmit_fifo_empty(uint16_t com);

/**
 * @brief Checks if data has been received.
 * 
 * @param com The COM port number.
 * @return true if data has been received, false otherwise.
 */
bool serial_received(uint16_t com);

/**
 * @brief Checks if the serial port with the specified COM number is initialized.
 *
 * @param com The COM number of the serial port.
 * @return true if the serial port is initialized, false otherwise.
 */
bool serial_is_init(uint16_t com);

/**
 * @brief Writes data to the serial port.
 * 
 * @param com The COM port number.
 * @param data The data to be written.
 * @param length The length of the data.
 */
void serial_write(uint16_t com, char* data, uint32_t length);

/**
 * @brief Writes data in hexadecimal format to the serial port.
 * 
 * @param com The COM port number.
 * @param data The data to be written in hexadecimal format.
 */
void serial_write_hex(uint16_t com, uint32_t data);

/**
 * @brief Reads data from the serial port.
 * 
 * @param com The COM port number.
 * @param length The length of the data to be read.
 * @return A pointer to the read data.
 */
char* serial_read(uint16_t com, uint32_t length);

/**
 * @brief Reads a single byte from the serial port.
 * 
 * @param com The COM port number.
 * @return The read byte.
 */
char serial_read_byte(uint16_t com);
