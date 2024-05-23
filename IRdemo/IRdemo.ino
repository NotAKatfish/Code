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



int FLpin1 = 22;
int FLpin2 = 23;
int FLpinEN = 13;

int FRpin1 = 24;
int FRpin2 = 25;
int FRpinEN = 12;

int BLpin1 = 28;
int BLpin2 = 29;
int BLpinEN = 11;

int BRpin1 = 26;
int BRpin2 = 27;
int BRpinEN = 10;

const float Nspeed = 80;
const float Kp = .2;
const float Ki = 0.0;
const float Kd = 0.2;

int error = 0;
int prevError = 0;
int speedLeft = Nspeed;
int speedRight = Nspeed;

int up_threshold = 150;
int low_threshold = -100;

int Lpin1 = 1;
int Lpin2 = 0;
int Rpin1 = 1;
int Rpin2 = 0;

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


  digitalWrite(FLpin1, Lpin1);
  digitalWrite(FLpin2, Lpin2);
  
  digitalWrite(FRpin1, Rpin1);
  digitalWrite(FRpin2, Rpin2);

  digitalWrite(BLpin1, Lpin1);
  digitalWrite(BLpin2, Lpin2);
  
  digitalWrite(BRpin1, Rpin1);
  digitalWrite(BRpin2, Rpin2);

  
  Serial.begin(9600);
}


void loop()
{
  // read raw sensor values
    getError();
    pid = (Kp * P) - (Ki * I) + (Kd * D);
    speedLeft = Nspeed - pid;
    speedRight = Nspeed + pid;
    if (speedLeft > up_threshold){speedLeft = up_threshold;}
    if (speedLeft < low_threshold){ speedLeft = low_threshold;}
    if (speedRight > up_threshold){ speedRight = up_threshold;}
    if (speedRight < low_threshold){ speedRight = low_threshold;}
    Serial.print('\t');
    Serial.print(pid);
    Serial.print('\t');
    Serial.print(speedLeft);
    Serial.print('\t');
    Serial.print(speedRight);
    Serial.println();

    if(speedLeft < 0)
    {
      Lpin1 = 0;
      Lpin2 = 1;
    } else if(speedLeft >= 0)
    {
      Lpin1 = 1;
      Lpin2 = 0;
    }
    if(speedRight < 0)
    {
      Rpin1 = 0;
      Rpin2 = 1;
    } else if(speedRight >= 0)
    {
      Rpin1 = 1;
      Rpin2 = 0;
    }

    digitalWrite(FLpin1, Lpin1);
    digitalWrite(FLpin2, Lpin2);
  
    digitalWrite(FRpin1, Rpin1);
    digitalWrite(FRpin2, Rpin2);

    digitalWrite(BLpin1, Lpin1);
    digitalWrite(BLpin2, Lpin2);
  
    digitalWrite(BRpin1, Rpin1);
    digitalWrite(BRpin2, Rpin2);

    analogWrite(BRpinEN, abs(speedRight));
    analogWrite(FLpinEN, abs(speedLeft));
    analogWrite(BLpinEN, abs(speedLeft));
    analogWrite(FRpinEN, abs(speedRight));


  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
 
//  analogWrite(BRpinEN, 255);
//  analogWrite(FRpinEN, 255);
//  analogWrite(BLpinEN, 255);
//  analogWrite(FLpinEN, 255);
//  
}

void getError()
{
   qtr.read(sensorValues);
   for (uint8_t i = 0; i < SensorCount; i++)
  {
    s[i] = (sensorValues[i]-offsetVal[i])*1000/normVal[i];
    if(s[i] < 0)
    {
      s[i] = 0; 
    }
//    Serial.print(s[i]);
//    Serial.print('\t');
  }
  error = 8*s[0]+4*s[1]+2*s[2]+s[3]-s[4]-2*s[5]-4*s[6]-8*s[7];

  
  P = error;
  I = I + error;
  D = error-prevError;
  Serial.print('\t');
  Serial.print(error);
//  Serial.print('\t');
//  Serial.print(P);
//   Serial.print('\t');
//  Serial.print(I);
//   Serial.print('\t');
//  Serial.print(D);
  
  
  prevError = error;
}
