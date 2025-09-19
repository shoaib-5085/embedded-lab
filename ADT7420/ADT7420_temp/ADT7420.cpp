#include "ADT7420.h"

void twi_init_master(void)
{
  TWBR = 72;
  TWCR = (1<<TWEA);    // TWEA is to enabel the acknowlede bit
  TWSR = 0;// ~(1<<TWPS1) | ~(1<<TWPS0);
}

void twi_start(void)
{
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while(!(TWCR & (1<<TWINT)));

  if((TWSR & 0XF8) == 0x08)
  {
  }
  else if ((TWSR & 0xF8) == 0x10)
  {}
  else
  {
    Serial.print("\n\nTWI START ERROR");
    Serial.print(TWSR,HEX);
  }
}

void twi_stop(void)
{
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void twi_send_data(uint8_t data)
{
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT)));
}

uint8_t twi_read_data(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Clear flag, enable, ACK
  while (!(TWCR & (1 << TWINT)));                  // Wait until byte received
  return TWDR;
}

uint16_t read_temperature(void)
{
  uint16_t data = 0;
  uint8_t receivedByte[2];

  twi_start();
  twi_address(SENSOR_ADDRESS,READ_DATA);
  
  for(int i = 1; i >= 0; i--)
  {
    receivedByte[i] = twi_read_data();
    data = data | ((uint16_t)receivedByte[i] << ((i) *8));
  }

  twi_stop();
  //data = data >> 3;   // If Resolution of the IC is set to 13 Bits
  return data;
}

void twi_address(uint8_t address, uint8_t readWrite)
{
  TWDR = (address << 1) | readWrite;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT)));
}

void device_write_reg(uint8_t address, uint8_t data)
{
  twi_start();
  twi_address(SENSOR_ADDRESS, WRITE_DATA);
  twi_send_data(address);
  twi_start();
  twi_address(SENSOR_ADDRESS, WRITE_DATA);
  twi_send_data(data);
  twi_stop();
  Serial.print("\nDATA WRITE DONE");
}

uint8_t device_read_reg(uint8_t address)
{
  uint8_t data;
  twi_start();
  twi_address(SENSOR_ADDRESS, WRITE_DATA);
  twi_send_data(address);
  twi_start();
  twi_address(SENSOR_ADDRESS, READ_DATA);
  
  TWCR = (1 << TWINT) | (1 << TWEN); // Clear flag, enable, NACK
  while (!(TWCR & (1 << TWINT)));    // Wait until byte received
  data = TWDR;
  
  twi_stop();
  
  return data;
}
