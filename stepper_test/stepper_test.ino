/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */

// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(20000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(20000); 
  }
  delay(1000); // One second delay
  
}



//// more efficient coding
//// Define pin connections & motor's steps per revolution
// const int dirPin = 8;
// const int stepPin = 9;
// const int stepsPerRevolution = 200;

// void setup()
// {
// 	// Declare pins as Outputs
// 	pinMode(stepPin, OUTPUT);
// 	pinMode(dirPin, OUTPUT);
// }
// void loop()
// {
// 	// Set motor direction clockwise / up
// 	setStepperDir(dirPin, HIGH);
// 	stepperMove(stepPin, stepsPerRevolution);
// 	delay(1000); // Wait a second
	
// 	// Set motor direction counterclockwise
//   setStepperDir(dirPin, LOW);
// 	stepperMove(stepPin, stepsPerRevolution);
// 	delay(1000); // Wait a second
// }


// // HIGH is c / up, LOW is cc / down
// void setStepperDir(int dirPin, int LEVEL){
//   if(LEVEL == HIGH){digitalWrite(dirPin, HIGH);}
//   else{digitalWrite(dirPin, LOW);}
// }

// // dont need by reference & since we alrdy declared that int to be output
// void stepperMove(int stepPin, int stepsPerRevolution){
//   	for(int x = 0; x < stepsPerRevolution; x++){
//       digitalWrite(stepPin, HIGH);
//       delayMicroseconds(10);
//       digitalWrite(stepPin, LOW);
//       delayMicroseconds(10);  
//     }
// }
