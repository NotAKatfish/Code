#include <Servo.h>
#include <ezButton.h>

ezButton claw_limitSwitch(7);  // create ezButton object that attach to pin 7;
Servo myservo;  // create servo object to control a servo

int start = 180;    // starting position
int pos = start;
bool go_right = true;
int desired_pos = 93;

void setup() {
  Serial.begin(9600);
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  claw_limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds

}

void loop() {

  myservo.write(pos); // every loop

  // once position hits position cap or limit switch is touched, stop
  if(go_right == true && !(pos == desired_pos || limitTouched(claw_limitSwitch)) ){
    myservo.write(pos--);
    delay(40);
  }
  else{go_right = false;}


}


//TODO: not sure if this is looped inside or if it must be called in a loop
// & makes the parameter passed by reference, so uses original object and not copy
bool limitTouched(ezButton &limitSwitch){
  limitSwitch.loop(); // MUST call the loop() function first for limit switch
  int state = limitSwitch.getState();
  if(state == HIGH){
    Serial.println("The limit switch: UNTOUCHED");
    return false;
  }
  else{
    Serial.println("The limit switch: TOUCHED");
    return true;
  }

}