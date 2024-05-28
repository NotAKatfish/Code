#ifndef HELPER_H
#define HELPER_H

#include <QTRSensors.h>
// #include <HCSR04.h>

extern QTRSensors qtr;
extern const uint8_t SensorCount;
extern int sensorValues[];
extern const int32_t offsetVal[];
extern const int32_t normVal[];
extern int32_t s[];

// sensor, all black all whtie
// all black all white detected
extern const int allBlackThreshold; // Threshold for all sensors being considered "black"
extern bool allGreaterThanBlack;
extern const uint8_t allWhiteThreshold; // Threshold for all sensors being considered "black"
extern bool firstTurnDone;

// // ultrasonic
// // Initialize sensor that uses digital pins 13 and 12.
// const byte triggerPin = 2;
// const byte echoPin = 3;
// UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);


// car
extern int FLpin1;
extern int FLpin2;
extern int FLpinEN;

extern int FRpin1;
extern int FRpin2;
extern int FRpinEN;

extern int BLpin1;
extern int BLpin2;
extern int BLpinEN;

extern int BRpin1;
extern int BRpin2;
extern int BRpinEN;


// speed vars, pid
extern const float Nspeed;
extern const float Kp;
extern const float Ki;
extern const float Kd;
extern float P;
extern float I;
extern float D;
extern float pid;

extern int error;
extern int prevError;
extern int speedLeft;
extern int speedRight;

// min and max power output
extern int up_threshold;
extern int low_threshold;

// switching to reverse
extern int Lpin1;
extern int Lpin2;
extern int Rpin1;
extern int Rpin2;

void initializeAll();
void lineFollowing();

void setLW_Reverse();
void setRW_Reverse();
void setLW_Forward();
void setRW_Forward();
void updateDirections();
void goMove();

void getError();

void setHardLeftTurn();
bool isWhite();
bool isBlack();

void firstTurn();

#endif