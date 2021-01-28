#include<Wire.h>
#define M_PI 3.141592653589793238462643

const int MPUarm=0x68;  // I2C address of the MPU-6050
const int MPUprobe=0x69;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ;
float RollArm, RollProbe;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPUarm);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Wire.beginTransmission(MPUprobe);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  Serial.begin(115200);
}

void loop(){
  Wire.beginTransmission(MPUarm);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPUprobe,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)   
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  RollArm = atan2(AcY, AcZ) * 180/M_PI;
  Serial.print(RollArm);
  Wire.beginTransmission(MPUprobe);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPUprobe,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)   
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  RollProbe = atan2(AcY, AcZ) * 180/M_PI;
  Serial.print('\t');
  Serial.print(RollProbe);
  Serial.print('\t');
  Serial.println(RollProbe-RollArm);
  delay(100);
}
