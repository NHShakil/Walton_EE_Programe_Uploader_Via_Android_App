#include <Wire.h>

#define ADDR_Ax 0b000  //A2, A1, A0
#define ADDR (0b1010 << 3) + ADDR_Ax

short chkSum = 0, data = 0;

//char ee_data [1024] = {326a,0c01,0a00,0170,5a70,685f,5a5a,3287,5a87,7668,5a55,5500,0028,281e,3034,2621,1c17,1322,1d18,130f,0100,0104,0bb8,0000,0000,0080,0000,0000,0000,0000,0000,0000,0600,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,00ff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff,ffff};
char ee_data[1024] = {
  0X23, 0X6a, 0X1b, 0X01, 0X0a, 0X00, 0X01, 0X78, 0X64,
  0X82, 0X7d, 0X6e, 0X64, 0X55, 0X46, 0X82, 0X64, 0X82,
  0X7d, 0X6e, 0X64, 0X55, 0X50, 0X00, 0X00, 0X28, 0X28,
  0X1e, 0X30, 0X34, 0X26, 0X21, 0X1c, 0X17, 0X13, 0X22,
  0X1d, 0X18, 0X13, 0X0f, 0X01, 0X00, 0X00, 0X04, 0X0b,
  0Xb8, 0X00, 0X00, 0X00, 0X00, 0X00, 0Xe8, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0Xe0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
  0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff, 0Xff,
  0Xff, 0Xff, 0Xff, 0Xff
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  //writeI2CByte(0, 1);

  write_data(ee_data);
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
  for (int i = 0; i < 256; i++) {

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

  for (int j = 0; j < 256; j++) {
    //Serial.println(data[i]);
    writeI2CByte(j, data[j]);
  }
}
