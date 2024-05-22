int motor1pin3 = 23;
int motor1pin4 = 22;


void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin3, OUTPUT);
  pinMode(motor1pin4, OUTPUT);
//  pinMode(motor2pin1,   OUTPUT);
//  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(10,  OUTPUT); 
//  pinMode(10, OUTPUT);
  //(Optional)
}

void loop() {
   // put your main code here, to run repeatedly:

  //Controlling speed (0   = off and 255 = max speed):     
  //(Optional)
  digitalWrite(motor1pin3, HIGH);
  digitalWrite(motor1pin4, LOW);
  analogWrite(10, 150); //ENA   pin
  //(Optional)
  

//  digitalWrite(motor2pin1, HIGH);
//   digitalWrite(motor2pin2, LOW);
//  delay(3000);
//
//  digitalWrite(motor1pin1,   LOW);
//  digitalWrite(motor1pin2, HIGH);
//
//  digitalWrite(motor2pin1, LOW);
//   digitalWrite(motor2pin2, HIGH);
}
