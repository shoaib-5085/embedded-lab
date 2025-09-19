/*
   This file is to read the temperature using I2C
   This file for the IC ADT7420.
*/
#include "ADT7420.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(21, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  twi_init_master();
  delay(500);
  Serial.println("\n\nPROGRAM START");

  device_write_reg(CONFIGURATION, 0xC0);
  Serial.print("\n\nDEVICE ID:   ");
  Serial.print(device_read_reg(DEVICE_ID),HEX);
}

float tempData;

void loop() {
  // put your main code here, to run repeatedly:

  //twi_send_data(0x0A);
  //twi_start();
  //twi_address(SENSOR_ADDRESS,READ_TEMP_DATA);
  //twi_send_data(0x0B);
  tempData = read_temperature();
  tempData = ((float)tempData) / 128.0;
  Serial.print("\n\nI2C TEMP: ");
  Serial.print(tempData);

  tempData = analogRead(A0);
  tempData = ((tempData * 500) / 1024) - 50 ;
  Serial.print("\tANALOG TEMP: ");
  Serial.print(tempData);
  
  //twi_stop();
  delay(2000);
}
