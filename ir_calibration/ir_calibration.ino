#include <QTRSensors.h>

// This example is designed for use with six analog QTR sensors. These
// reflectance sensors should be connected to analog pins A0 to A5. The
// sensors' emitter control pin (CTRL or LEDON) can optionally be connected to
// digital pin 2, or you can leave it disconnected and remove the call to
// setEmitterPin().
//
// The main loop of the example reads the raw sensor values (uncalibrated). You
// can test this by taping a piece of 3/4" black electrical tape to a piece of
// white paper and sliding the sensor across it. It prints the sensor values to
// the serial monitor as numbers from 0 (maximum reflectance) to 1023 (minimum
// reflectance).

QTRSensors qtr;

const uint8_t SensorCount = 8;
int sensorValues[SensorCount];
const int32_t offsetVal[SensorCount] = {449, 227, 197, 180, 183, 247, 160, 373};
const int32_t normVal[SensorCount] = {525, 712, 734, 749, 747, 699, 774, 587};
int32_t s[SensorCount];




void setup()
{
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A8, A9, A10, A11, A12, A13, A14, A15}, SensorCount);
  qtr.setEmitterPin(2);

  Serial.begin(9600);
}


void loop()
{
  for (int i = 0; i<25; i++)
  {
  // read raw sensor values
  qtr.read(sensorValues);

  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    s[i] = (sensorValues[i]-offsetVal[i])*1000/normVal[i];
    if(s[i] < 0)
    {
      s[i] = 0; 
    }
    Serial.print(s[i]);
//    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();
  delay(50);
  }
  Serial.print("Done");
  Serial.println();

  delay(5000);
}
