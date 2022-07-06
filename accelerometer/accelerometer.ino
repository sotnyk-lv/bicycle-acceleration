#include <MPU9250_asukiaaa.h>
 
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif
 
MPU9250_asukiaaa mySensor;
unsigned long t;
 
void setup() {
  while(!Serial);
   
  Serial.begin(115200);
  Serial.println("started");
   
  #ifdef _ESP32_HAL_I2C_H_
  // for esp32
  Wire.begin(SDA_PIN, SCL_PIN); //sda, scl
  #else
  Wire.begin();
  #endif
   
  mySensor.setWire(&Wire);
   
  mySensor.beginAccel();
  mySensor.beginMag();
   
  // you can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
}
 
void loop() {
  t = millis();
  mySensor.accelUpdate();
  Serial.print("accel");
  Serial.print("\t x: " + String(mySensor.accelX()));
  Serial.print("\t y: " + String(mySensor.accelY()));
  Serial.print("\t z: " + String(mySensor.accelZ()));
  Serial.print("\tfull: " + String(mySensor.accelSqrt()));
   
  mySensor.magUpdate();
  Serial.print("\tmag ");
  Serial.print("\t x: " + String(mySensor.magX()));
  Serial.print("\t y: " + String(mySensor.magY()));
  Serial.print("\t z: " + String(mySensor.magZ()));
  Serial.print("\tdirection: " + String(mySensor.magHorizDirection()));
   
  Serial.println("\tat " + String(millis()-t) + "ms");
}
