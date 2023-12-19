#include "../error.h"
#include <stddef.h>
#include "../../driver/serial/serial.h"
#include "../string.h"

void panic(char* error, uint8_t error_code, uint16_t std_db_port){
  if(!serial_is_init(std_db_port)){
    serial_write(std_db_port, error, strlen(error));
    serial_write(std_db_port, "\n", 1);
    serial_write(std_db_port, "Error code: ", 12);
    serial_write_hex(std_db_port, error_code);
    serial_write(std_db_port, "\n", 1);
  }

  while(1);
};