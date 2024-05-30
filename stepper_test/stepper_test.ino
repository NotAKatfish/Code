/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */

// defines pins numbers
const int stepPin1 = 51; //rotate 180 degrees
const int dirPin1 = 53; 

const int stepPin2 = 47; //go up or down
const int dirPin2 = 49; 

const int maxsteps1 = 1400; //200 steps per rotation, 7 complete rotations
const int maxsteps2 = 2000; //200 steps per rotation, 10 complete rotations
const int pulses = 200;
int stepcounter = 0;
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
}

//void loop() {
//  if (stepcounter <= maxsteps2){
//  digitalWrite(dirPin2,LOW); // Enables the motor to move in a particular direction //dirPin2, HIGH is going up  dirPin2, LOW is going down
//  // Makes 200 pulses for making one full cycle rotation
//  for(int x = 0; x < pulses; x++) {
//    digitalWrite(stepPin2,HIGH); 
//    delayMicroseconds(20000); 
//    digitalWrite(stepPin2,LOW); 
//    delayMicroseconds(2000); 
//    stepcounter++;
//  }
//  
//  delay(1000); // One second delay  
//}
//}

void loop() {
  if (stepcounter <= maxsteps1){
  digitalWrite(dirPin1,LOW); // Enables the motor to move in a particular direction //LOW = clockwise HIGH = counterclockwise 
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < pulses; x++) {
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(20000); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(2000); 
    stepcounter++;
  }}
  
  delay(1000); // One second delay  
}

// to go completely up from the bottom is 10 *200 = 2000 steps

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
