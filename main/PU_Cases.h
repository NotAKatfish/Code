#ifndef PU_CASES
#define PU_CASES
#include <HCSR04.h>

// ultrasonic vars
  extern UltraSonicDistanceSensor sensor1;
  extern UltraSonicDistanceSensor sensor2;

void pickUp(int pattyLocation);
void pickUpLeft();
void pickUpRight();




#endif
