// Pseudocode:
//1. move down until limit switch pressed
//2. set position as 0
//RAISE CODE: 

// 0 discs below: 11 rotations from bottom( go to this position when ready to receive shipment from claw)
// 1 disc below:  8 rotations from bottom
// 2 discs below: 5 rotations from bottom
// 3 discs below: 1 rotations from bottom
//SEQUENCE:
// STARTING POINT: platform exposed (0 discs below), aligners away

// 1. picking up first disc
//  a. remain at 0 discs below (plate exposed) / function: N/A (future: home)
//  * disc gets placed by claw*
//  b. move to 1 disc below (discs hidden) / function: move_disc_down(1)
//  c. align / function: align (consists of flat, delay, away)

// 2. picking up second disc
//  a. remain at 1 disc below (disc surface exposed) / function: N/A
//  * disc gets placed *
//  b. move to 2 discs below (discs hidden) / function: move_disc(-1)
//  c. align / function: align (consists of flat, delay, away)

// 3.picking up third disc
//  a. remain at 2 disce below (disc surface exposed) / function: N/A
//  * disc gets placed *
//  b. move to 3 discs below (discs hidden) / function: move_disc(-1)
//  c. align / function: align (consists of flat, delay, away)

// 4. exposing all discs to be picked up by claw
//  a. remain at 3 discs below (discs hidden) / function: N/A
//  b. move to 0 discs below (all discs exposed) / function: move_disc_up (1)

#include <Servo.h>

Servo servoL;
Servo servoR;

// defines pins numbers
const int stepPin = 10; 
const int dirPin = 11; 
const int servoL_Pin = 8;
const int servoR_Pin = 9;

// alignment angles for the servo motors
const int servoL_flat = 42;
const int servoL_away = 7;
const int servoR_flat = 8; 
const int servoR_away = 43; 

// number of steps to move the platform by the height of a disc (0.5 in)
const int disc_steps = 635;
 
void setup() {
// define stepper step and direction pins
  pinMode (stepPin,OUTPUT); 
  pinMode (dirPin,OUTPUT);
// define servo pins
  servoL.attach (servoL_Pin);
  servoR.attach (servoR_Pin);
// move the aligners to their away position
  servoL.write (servoL_away);
  servoR.write (servoR_away);
}
void loop() {
  // platform exposed at the start

  delay(10000); // PLACE FIRST DISC DURING THIS TIME (pretend to be the claw)
  move_disc(-1);// move it down to hide it, its top surface will be in line with the box
  delay(1000);
  align(); // align the 1 disc

  delay(10000); // PLACE THE SECOND DISC DURING THIS TIME
  move_disc(-1); // move the 2 discs down to align the top surface with the top of the box
  delay(1000);
  align(); // align the 2 discs

  delay(10000); // PLACE THE THIRD DISC DURING THIS TIME
  move_disc(-1); // move the three discs down to align the top surface with the box
  align(); // align the 3 discs
  delay(5000);
  move_disc(3); // this moves the platform so that all the discs are exposed and ready to be grabbed by the claw
  flat();
  delay(60000); // UNPLUG NOW, this is when the claw would pick up the discs
  away();
  
}









