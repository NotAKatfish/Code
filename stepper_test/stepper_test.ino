/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */

// defines pins numbers
const int stepPinRot = 51; //rotate 180 degrees
const int dirPinRot = 53; 

const int stepPinVert = 47; //go up or down
const int dirPinVert = 49; 

const int maxstepsRot = 1400; //200 steps per rotation, 7 complete rotations
const int maxstepsVert = 2000; //200 steps per rotation, 10 complete rotations
int stepcounter = 0;    // always reset before each stepper action
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPinRot,OUTPUT); 
  pinMode(dirPinRot,OUTPUT);
  pinMode(stepPinVert,OUTPUT); 
  pinMode(dirPinVert,OUTPUT);
}

void loop() {

  //rotation code

  // Set motor direction clockwise
  setStepperDir(dirPinRot, LOW);
  stepperMove(stepPinRot, stepcounter, maxstepsRot);

  // Set motor direction cc
  stepcounter = 0;  // reset step counter
  setStepperDir(dirPinRot, HIGH);
  stepperMove(stepPinRot, stepcounter, maxstepsRot);

  
  delay(1000); // One second delay  
}

// to go completely up from the bottom is 10 *200 = 2000 steps


// Low is c / up, High is cc / down
void setStepperDir(int dirPin, int LEVEL){
  if(LEVEL == HIGH){digitalWrite(dirPin, HIGH);}
  else{digitalWrite(dirPin, LOW);}
}

// stepper movement loop
void stepperMove(int stepPin, int &stepcounter, int maxsteps){
  for(; stepcounter < maxsteps; stepcounter++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);  
  }
  delay(2000);
}
