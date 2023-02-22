#include <Wire.h>
#include "IDU_EE_data.h"
#include "ODU_EE_data.h"
#define ADDR_Ax 0b000  //A2, A1, A0
#define ADDR (0b1010 << 3) + ADDR_Ax
#define IDU_ARR_LENGTH 255
#define ODU_ARR_LENGTH 512

short chkSum = 0, data = 0,arr_counter = ODU_ARR_LENGTH;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  write_data(ee_odu_data);
  delay(3000);
  read_data();
  delay(2000);
}

void loop() {
}

void writeI2CByte(byte data_addr, byte data) {
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte readI2CByte(byte data_addr) {
  byte data = NULL;
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(ADDR, 1);  //retrieve 1 returned byte
  delay(1);
  if (Wire.available()) {
    data = Wire.read();
  }
  return data;
}
void read_data() {
  for (int i = 0; i < arr_counter; i++) {

    Serial.print("ADD: ");
    Serial.print(i);
    Serial.print("\t DTA: ");
    data = readI2CByte(i);
    chkSum += data;
    Serial.println(data);
    delay(10);
  }
  Serial.println();
  Serial.print("Check Sum: ");
  Serial.println(chkSum, HEX);
  chkSum = 0;
}
void write_data(char data[]) {

  int arr_size = sizeof(data) / sizeof(data[0]);

  for (int j = 0; j < arr_counter; j++) {
    //Serial.println(data[i]);
    writeI2CByte(j, data[j]);
    Serial.println(chkSum, HEX);
    delay(10);
  }
}
