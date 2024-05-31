# include "Arm.h"

void moveArm(){

  // claw
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
    stepper_stepcounter = 0;  // reset step counter
    setStepperDir(dirPinRot, HIGH);
    stepperMove(stepPinRot, stepper_stepcounter, maxstepsRot);
  }
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
void stepperMove(int stepPin, int &stepcounter, int desired_steps){
  for(; stepcounter < desired_steps; stepcounter++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(40000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(40000);  
  }
  delay(2000);
}