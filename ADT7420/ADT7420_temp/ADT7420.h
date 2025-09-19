
#ifndef  ADT7420_H_
#define  ADT7420_H_
#include <Arduino.h>


#define SENSOR_ADDRESS    0x4A
#define READ_DATA         0x01
#define WRITE_DATA        0x00

//////////////////////////// REGISTERS ADDRESSES //////////////////////////////////
#define TEMP_MSB_BYTE     0x00
#define TEMP_LSB_BYTE     0x01
#define STATUS            0x02
#define CONFIGURATION     0x03
#define HIGH_SETPOINT_MSB 0x04
#define HIGH_SETPOINT_LSB 0x05
#define LOW_SETPOINT_MSB  0x06
#define LOW_SETPOINT_LSB  0x07
#define CRIT_SETPOINT_MSB 0x08
#define CRIT_SETPOINT_LSB 0x09
#define HYST_SETPOINT     0x0A
#define DEVICE_ID         0x0B
#define DEVICE_RESET      0x2F


void twi_init_master(void);
void twi_start(void);
void twi_stop(void);
uint16_t read_temperature(void);
void twi_send_data(uint8_t data);
uint8_t twi_read_data(void);
void twi_address(uint8_t address, uint8_t readWrite);

void device_write_reg(uint8_t address, uint8_t data);

uint8_t device_read_reg(uint8_t address);

#endif
