#ifndef STATEFUNCTIONS_H
#define STATEFUNCTIONS_H
#include <LiquidCrystal.h>
#include <QTRSensors.h>
//#include <HCSR04.h>
  #define IR_RECEIVE_PIN 9
  #define IR_BUTTON_1 12
  #define IR_BUTTON_2 24
  #define IR_BUTTON_3 94
  #define IR_BUTTON_4 8
  #define IR_BUTTON_5 28
  #define IR_BUTTON_6 90
  #define IR_BUTTON_7 66
  #define IR_BUTTON_8 86
  #define IR_BUTTON_9 74
  
  #define IR_BUTTON_ON_OFF 69
  #define IR_BUTTON_VOL_PLUS 70
  #define IR_BUTTON_VOL_MIN 21
  #define IR_BUTTON_FUNC_STOP 71
  
  #define IR_BUTTON_PLAY_PAUSE 64
  #define IR_BUTTON_BACK 68
  #define IR_BUTTON_FORWARD 67
  #define IR_BUTTON_DOWN 7
  #define IR_BUTTON_UP 9
  
  #define IR_BUTTON_EQ 25
  #define IR_BUTTON_ST 13

// IR sensors
extern QTRSensors qtr;
extern const uint8_t SensorCount;
extern uint16_t sensorValues[];
extern const int32_t offsetVal[];
extern const int32_t normVal[];
extern uint16_t s[];


// motor pins 
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

// steppers
  extern const int RotPinEn;
  extern const int VertPinEn;
  extern const int StoragePinEn;

  extern const int pattyNumber;
  extern int pattyLocation[];
  extern int inputsReceived;
  
  extern bool pressed1;
  extern bool pressed2;
  extern bool pressed3;
  extern bool pressed4;
  extern bool pressed5;
  extern bool pressed6;

  extern LiquidCrystal lcd;


void curvedSection();
void Assembly();
void ramp();
void dropOff();
void Calibration();

#endif
