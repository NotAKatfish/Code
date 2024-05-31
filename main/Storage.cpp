#include "Storage.h"

void goStorage(){
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


void flat(){
  servoL.write (servoL_flat);
  servoR.write (servoR_flat);
}

void away(){ 
  servoL.write(servoL_away);
  servoR.write(servoR_away);
}

void align(){
  flat();
  delay(1000);
  away();

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




