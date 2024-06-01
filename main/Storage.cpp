#include "Storage.h"

// defines pins numbers
const int stepPinStorage; 
const int dirPinStorage; 
const int servoL_Pin;
const int servoR_Pin;

// alignment angles for the servo motors
const int servoL_flat = 42;
const int servoL_away = 7;
const int servoR_flat = 8; 
const int servoR_away = 43; 



void goStorage(int n){
  away()

  move_disc(n);
 
  
  flat(); 
}

void flat(){
  servoL.write (servoL_flat);
  servoR.write (servoR_flat);
}

void away(){ 
  servoL.write(servoL_away);
  servoR.write(servoR_away);
}




// n is how many discs you want to move up or down by
void move_disc(int n){
  if (n > 0) // positive n makes platform  move up, negative n makes the platform move down
  {
    digitalWrite (dirPinStorage, LOW); // this makes the motor move up
  }
  else 
    {
    digitalWrite (dirPinStorage, HIGH); // this makes the motor move down
    }
  for(int x = 0; x < abs(n) * disc_steps ; x++) 
  {
    digitalWrite(stepPinStorage,HIGH); 
    delayMicroseconds(20000); 
    digitalWrite(stepPinStorage,LOW); 
    delayMicroseconds(20000); 
  }

}
