#include<Wire.h> //library for I2C

const int MPU=0x68;  // I2C address of the MPU-6050

int16_t accX,accY,accZ,Temp,GyroX,GyroY,GyroZ;//16 bit data

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero; wakes up the MPU-6050
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);                 // stasrt with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);    // request 14 consecutive registers
  accX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  accY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  accZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyroX=Wire.read()<<8|Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyroY=Wire.read()<<8|Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyroZ=Wire.read()<<8|Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("accX = "); Serial.print(accX);
  Serial.print("\taccY = "); Serial.print(accY);
  Serial.print("\taccZ = "); Serial.print(accZ);
  Serial.print("\tTemp = "); Serial.print(Temp/340.00+36.53); //temperature in degrees C 
  Serial.print("\tGyroX = "); Serial.print(GyroX);
  Serial.print("\tGyroY = "); Serial.print(GyroY);
  Serial.print("\tGyroZ = "); Serial.println(GyroZ);
  delay(2000);
}
