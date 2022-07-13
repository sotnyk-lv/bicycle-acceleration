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
  Serial.print("acc");
  Serial.print("\t" + String(mySensor.accelX()));
  Serial.print("\t" + String(mySensor.accelY()));
  Serial.print("\t" + String(mySensor.accelZ()));
  Serial.print("\t" + String(mySensor.accelSqrt()));

  mySensor.magUpdate();
  Serial.print("\tmag");
  Serial.print("\t" + String(mySensor.magX()));
  Serial.print("\t" + String(mySensor.magY()));
  Serial.print("\t" + String(mySensor.magZ()));
  Serial.print("\t" + String(mySensor.magHorizDirection()));

  Serial.println("\ttime\t" + String(millis()-t));
}
