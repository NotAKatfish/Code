#ifndef ARM_H
#define ARM_H

#include <Servo.h>
#include <ezButton.h>

// claw vars
extern ezButton claw_limitSwitch;  // create ezButton object that attach to pin 7;
extern ezButton bottom_limitSwitch; // underneath

extern Servo myservo;  // create servo object to control a servo

extern int start;    // starting position
extern int pos;
extern bool go_right;
extern int desired_pos;

// stepper vars
extern const int stepPinRot; //rotate 180 degrees
extern const int dirPinRot; 
extern const int stepPinVert; //go up or down
extern const int dirPinVert; 

extern const int maxstepsRot; //200 steps per rotation, 7 complete rotations
extern const int maxstepsVert; //200 steps per rotation, 10 complete rotations
extern int stepper_stepcounter;    // always reset before each stepper action

extern bool armFaceFront; // arm default faces front

void moveArm();
bool limitTouched(ezButton &limitSwitch);
void setStepperDir(int dirPin, int LEVEL);
void stepperMove(int stepPin, int &stepcounter, int maxsteps);

#endif