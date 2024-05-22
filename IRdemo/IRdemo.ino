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
uint16_t sensorValues[SensorCount];
uint16_t IRValues[SensorCount];
int s0;
int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
int s7;



int FLpin1 = 22;
int FLpin2 = 23;
int FLpinEN = 10;

int FRpin1 = 24;
int FRpin2 = 25;
int FRpinEN = 11;

int BLpin1 = 28;
int BLpin2 = 29;
int BLpinEN = 12;

int BRpin1 = 26;
int BRpin2 = 27;
int BRpinEN = 13;

const float Nspeed = 60;
const float Kp = .2;
const float Ki = 0.0;
const float Kd = 0.0;

int error = 0;
int prevError = 0;
int speedLeft = Nspeed;
int speedRight = Nspeed;

int threshold = 100;

float P = 0;
float I = 0;
float D = 0;
float pid = 0;

void setup()
{
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A8, A9, A10, A11, A12, A13, A14, A15}, SensorCount);
  qtr.setEmitterPin(2);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

 for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  
  pinMode(FLpin1, OUTPUT);
  pinMode(FLpin2, OUTPUT);
  pinMode(FLpinEN, OUTPUT);

  

  
  pinMode(FRpin1, OUTPUT);
  pinMode(FRpin2, OUTPUT);
  pinMode(FRpinEN, OUTPUT);

  

  pinMode(BLpin1, OUTPUT);
  pinMode(BLpin2, OUTPUT);
  pinMode(BLpinEN, OUTPUT);
  
  pinMode(BRpin1, OUTPUT);
  pinMode(BRpin2, OUTPUT);
  pinMode(BRpinEN, OUTPUT);

  digitalWrite(FLpin1, LOW);
  digitalWrite(FLpin2, HIGH);
  
  digitalWrite(FRpin1, LOW);
  digitalWrite(FRpin2, HIGH);

  digitalWrite(BLpin1, HIGH);
  digitalWrite(BLpin2, LOW);
  
  digitalWrite(BRpin1, HIGH);
  digitalWrite(BRpin2, LOW);

  
  Serial.begin(9600);
}


void loop()
{
//  // read raw sensor values
    getError();
    pid = (Kp * P) - (Ki * I) + (Kd * D);
    speedLeft = Nspeed - pid;
    speedRight = Nspeed + pid;
    if (speedLeft > threshold){ speedLeft = threshold;}
    if (speedLeft < 0){ speedLeft = 0;}
    if (speedRight > threshold){ speedRight = threshold;}
    if (speedRight < 0){ speedRight = 0;}
    Serial.print('\t');
    Serial.print(pid);
    Serial.print('\t');
    Serial.print(speedLeft);
    Serial.print('\t');
    Serial.print(speedRight);
    Serial.println();

    analogWrite(BRpinEN, speedRight);
    analogWrite(FLpinEN, speedLeft);
    analogWrite(BLpinEN, speedLeft);
    analogWrite(FRpinEN, speedRight);


  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
 
  //analogWrite(BRpinEN, 100);

  
}

void getError()
{
   qtr.read(sensorValues);
   for (uint8_t i = 0; i < SensorCount; i++)
  {
    //IRValues[i] = sensorValue[i];
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  s0 = sensorValues[0];
  s1 = sensorValues[1];
  s2 = sensorValues[2];
  s3 = sensorValues[3];
  s4 = sensorValues[4];
  s5 = sensorValues[5];
  s6 = sensorValues[6];
  s7 = sensorValues[7];
  error = 4*s0+3*s1+2*s2+s3-s4-2*s5-3*s6-4*s7;
  
  P = error;
  I = I + error;
  D = error-prevError;
  Serial.print(error);
//  Serial.print('\t');
//  Serial.print(P);
//   Serial.print('\t');
//  Serial.print(I);
//   Serial.print('\t');
//  Serial.print(D);
  
  
  prevError = error;
}
