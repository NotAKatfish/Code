# include "Arm.h"

void moveArm(){

  // claw closes
  if(limitTouched(bottom_limitSwitch)){
    claw_servo.write(pos); // every loop
    
    // once position hits position cap or limit switch is touched, stop
    if(go_right == true && !(pos == desired_pos || limitTouched(claw_limitSwitch)) ){
      claw_servo.write(pos--);
      delay(40);
    }
    else{go_right = false;}
  }

  if(limitTouched(claw_limitSwitch)){
    // rotation 
    // Set motor direction clockwise
    stepper_stepcounter = 0;
    setStepperDir(dirPinRot, LOW);
    stepperMove(stepPinRot, stepper_stepcounter, maxstepsRot);

    // reset claw position and make it open
    pos = start;
    claw_servo.write(pos);

    // Set motor direction cc
    stepper_stepcounter = 0; // reset step counter
    setStepperDir(dirPinRot, HIGH);
    stepperMove(stepPinRot, stepper_stepcounter, maxstepsRot);
    
  }
}


//pos = 90

void clawPickup() {
  
//  while (!limitTouched(claw_limitSwitch)) {
    Serial.println("entered clawpickup");
    goDownAndGrab();
    Serial.println("After goDownAndGrab()");
    pos = start; // reset claw position value in preparation to open again
    
    setStepperDir(dirPinVert, HIGH);//  set direction up
    Serial.println(vert_stepcounter);
    stepper_stepcounter = 0;
    stepperMove (stepPinVert, stepper_stepcounter, vert_stepcounter); // move the claw back up to the top
  //}
  vert_stepcounter = 0;
  stepper_stepcounter = 0;
  setStepperDir(dirPinRot, LOW); // rotate clockwise 
  stepperMove(stepPinRot, stepper_stepcounter, maxstepsRot); // rotate back to storage
  
  
  claw_servo.write(pos); // open the claw
  

  stepper_stepcounter = 0;
  setStepperDir(dirPinRot, HIGH); // rotate counterclockwise 
  stepperMove(stepPinRot, stepper_stepcounter, maxstepsRot); // rotate back to storage
  goStorage(-1);
  Serial.println("DISC PICKED UP");
}

void goDownAndGrab(){
  Serial.println("godownandgrab");
  claw_servo.write(90); // opens claw
  vert_stepcounter = 0; // initialize step counter
  setStepperDir (dirPinVert, LOW); // direction: down
  Serial.println(limitTouched(bottom_limitSwitch));
  while (limitTouched(bottom_limitSwitch) == false){ 
    Serial.println(limitTouched(bottom_limitSwitch));
    // moves claw down to platform until bottom limit switch is touched 
    //incremental_step();
    stepper_stepcounter = 0;
    stepperMove (stepPinVert, stepper_stepcounter, 1);
   // Serial.println("step moved");
      
    vert_stepcounter++;
    
    Serial.println(vert_stepcounter);
  
    
  }
  // for the raising distance, if limit_limit switch pressed_ move one step. else 
  while (!(pos == desired_pos || limitTouched(claw_limitSwitch))){ 
    // close claw
    claw_servo.write(pos--);
    delay(40);
  }
}

void clawDropoff() {
    claw_servo.write(pos); // opens claw
    stepper_stepcounter = 0; 
    vert_stepcounter = 0;
    setStepperDir(dirPinRot, LOW); // rotate clockwise 
    stepperMove(stepPinRot, stepper_stepcounter, 1300); // rotate partially 
    setStepperDir(dirPinVert, LOW);//  set direction down 

    while (!limitTouched(bottom_limitSwitch)){ // moves claw down to platform until bottom limit switch is touched 
    stepper_stepcounter = 0;
    stepperMove (stepPinVert, stepper_stepcounter, 1);
    vert_stepcounter++;
   }
   stepperMove(stepPinRot, stepper_stepcounter, maxstepsRot-1300);// rotate back to storage
   goStorage(3);
   //digitalWrite(StoragePinEn, HIGH); //Turn off storage enable
   while (!(pos == desired_pos || limitTouched(claw_limitSwitch))){ // close claw
    claw_servo.write(pos--);
   }
   setStepperDir(dirPinVert, LOW);//  set direction up
   stepper_stepcounter = 0; 
   stepperMove (stepPinVert, stepper_stepcounter, vert_stepcounter); // move the claw back up to the top
   setStepperDir(dirPinRot, HIGH); // rotate counterclockwise
   stepper_stepcounter = 0;
   stepperMove(stepPinRot, stepper_stepcounter, maxstepsRot); // rotate counter clockwise back to front position 
   setStepperDir(dirPinVert, HIGH);//  set direction down

   vert_stepcounter = 0;
   while (!limitTouched(bottom_limitSwitch)){ // moves claw down to platform until bottom limit switch is touched 
   stepper_stepcounter = 0;
    stepperMove (stepPinVert, stepper_stepcounter, 1);
   vert_stepcounter++;
   }
   delay(40);
   claw_servo.write(pos); // opens claw
}

//TODO: not sure if this is looped inside or if it must be called in a loop
// & makes the parameter passed by reference, so uses original object and not copy
bool limitTouched(ezButton &limitSwitch){
  limitSwitch.loop(); // MUST call the loop() function first for limit switch
  int state = limitSwitch.getState();
  if(state == HIGH){
    // Serial.println("The limit switch: UNTOUCHED");
    return false;
  }
  else{
    // Serial.println("The limit switch: TOUCHED");
    return true;
  }

}


// to go completely up from the bottom is 10 *200 = 2000 steps
// Low is c / up, High is cc / down
void setStepperDir(int dirPin, int LEVEL){
  if(LEVEL == HIGH){digitalWrite(dirPin, HIGH);}
  else{digitalWrite(dirPin, LOW);}
}

// stepper movement loop
void stepperMove(int stepPin, int &stepcounter, int desired_steps) {

  for(; stepcounter < desired_steps; stepcounter++){

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(40000); // Delay maybe too high
    digitalWrite(stepPin, LOW);
    delayMicroseconds(40000);  
  }
  //delay(2000);
} 


void incremental_step(int stepPin){
  digitalWrite(stepPin, HIGH);
    delayMicroseconds(40000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(40000); 
}


//PICKUP
// put claw manually at the top
// 1. arrive at the platform (as determined by the ultrasonic sensor)
//2. open the claw fully
//3. lower until bottom limit switch triggered
// 4. close claw until disc is secure
// 5. raise back to top (-step_counter)
// 7. rotate back to storage
// 8. open claw
// 9. rotate back to front


// DROP OFF (variation 1)
// 1. raise claw back to top
// 2. open claw
// 3. rotate claw until botttom limit switch is over disc
// 4. lower until bottom limit switch is pressed
// 5. rotate the rest of the way until the claw is grabbing position
// 6. go_storage(3)
// 7. close claw until the bottom disc is secure
// 8. move claw back to the top
// 9. rotate 180 degrees (back to front)
// 10. lower until the bottom limit switch is triggered
// 11. open the dayum claw
// 12. release fireworks
