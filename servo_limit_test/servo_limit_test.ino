#include <Servo.h>
#include <ezButton.h>

// claw vars
ezButton claw_limitSwitch(45);  // create ezButton object that attach to pin 7;
ezButton bottom_limitSwitch(43); // underneath

Servo myservo;  // create servo object to control a servo

int start = 90;    // starting position
int pos = start;
bool go_right = true;
int desired_pos = 10;

// stepper vars
const int stepPinRot = 51; //rotate 180 degrees
const int dirPinRot = 53; 
const int stepPinVert = 47; //go up or down
const int dirPinVert = 49; 

const int maxstepsRot = 1400; //200 steps per rotation, 7 complete rotations
const int maxstepsVert = 2000; //200 steps per rotation, 10 complete rotations
int stepcounter = 0;    // always reset before each stepper action

bool armFaceFront = true; // arm default faces front


void setup() {
  
  Serial.begin(9600);

  // set claw pins
  myservo.attach(41);  // attaches the servo on pin 3 to the servo object
  claw_limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
  bottom_limitSwitch.setDebounceTime(50);


  // set stepper pins
  pinMode(stepPinRot,OUTPUT); 
  pinMode(dirPinRot,OUTPUT);
  pinMode(stepPinVert,OUTPUT); 
  pinMode(dirPinVert,OUTPUT);

}

void loop() {

  // claw
  if(limitTouched(bottom_limitSwitch)){
    myservo.write(pos); // every loop
    // once position hits position cap or limit switch is touched, stop
    if(go_right == true && !(pos == desired_pos || limitTouched(claw_limitSwitch)) ){
      myservo.write(pos--);
      delay(40);
    }
    else{go_right = false;}
  }

  if(limitTouched(claw_limitSwitch)){
    // rotation 
    // Set motor direction clockwise
    stepcounter = 0;
    setStepperDir(dirPinRot, LOW);
    stepperMove(stepPinRot, stepcounter, maxstepsRot);

    // reset claw position and make it open
    pos = start;
    myservo.write(pos);

    // Set motor direction cc
    stepcounter = 0;  // reset step counter
    setStepperDir(dirPinRot, HIGH);
    stepperMove(stepPinRot, stepcounter, maxstepsRot);
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
void stepperMove(int stepPin, int &stepcounter, int maxsteps){
  for(; stepcounter < maxsteps; stepcounter++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(10000);  
  }
  delay(2000);
}