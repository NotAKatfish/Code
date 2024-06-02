#ifndef STORAGE_H
#define STORAGE_H

#include <Servo.h>
#include "Arduino.h"
extern Servo servoL;
extern Servo servoR;

// vars
  // defines pins numbers
  extern const int stepPinStorage; 
  extern const int dirPinStorage; 
  extern const int servoL_Pin;
  extern const int servoR_Pin;

  // alignment angles for the servo motors
  extern const int servoL_flat;
  extern const int servoL_away;
  extern const int servoR_flat; 
  extern const int servoR_away; 

  // number of steps to move the platform by the height of a disc (0.5 in)
  extern const int disc_steps;


void goStorage(int n);
void flat();
void away();
void move_disc(int n);


#endif
