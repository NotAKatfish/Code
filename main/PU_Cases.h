#ifndef PU_CASES
#define PU_CASES
#include <HCSR04.h>

// ultrasonic vars
 extern UltraSonicDistanceSensor sensor1;
 extern UltraSonicDistanceSensor sensor2;
 extern int currRow;
 extern int dropOffLocation;
 

void pickUp(int pattyLocation);
void pickUpLeft();
void pickUpRight();
void dropOff(int n);
void backToCenter(int pattyLocation);
void goToRow();
int rowOfPatty(int pattyLocation);
bool isOnLeft(int pattyLocation);



#endif
