#include <Arduino.h>
#include <QTRSensors.h>
#include "helper.h"
#include "stateFunctions.h"

void initializeAll(){
    // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A8, A9, A10, A11, A12, A13, A14, A15}, SensorCount);
  qtr.setEmitterPin(2);

  
  pinMode(FLpin1, OUTPUT);
  pinMode(FLpin2, OUTPUT);
  pinMode(FLpinEN, OUTPUT);

  
  pinMode(FRpin1, OUTPUT);
  pinMode(FRpin2, OUTPUT);
  pinMode(FRpinEN, OUTPUT);

  pinMode(BLpin1, OUTPUT);
  pinMode(BLpin2, OUTPUT);
  pinMode(BLpinEN, OUTPUT);
  
  pinMode(BRpin1, OUTPUT);
  pinMode(BRpin2, OUTPUT);
  pinMode(BRpinEN, OUTPUT);

  pinMode(RtrigPin, OUTPUT); // Ultrasonic trig pin
  pinMode(RechoPin, INPUT); //Ultrasonic echo pin

//  pinMode(LtrigPin, OUTPUT); // Ultrasonic trig pin
//  pinMode(LechoPin, INPUT); //Ultrasonic echo pin

  digitalWrite(FLpin1, Lpin1);
  digitalWrite(FLpin2, Lpin2);
  
  digitalWrite(FRpin1, Rpin1);
  digitalWrite(FRpin2, Rpin2);

  digitalWrite(BLpin1, Lpin1);
  digitalWrite(BLpin2, Lpin2);
  
  digitalWrite(BRpin1, Rpin1);
  digitalWrite(BRpin2, Rpin2);


}


void lineFollowing() {
  // read raw sensor values
    getError();
    pid = (Kp * P) - (Ki * I) + (Kd * D);
    speedLeft = Nspeed - pid;
    speedRight = Nspeed + pid;

    // ensure value within limited power range
    if (speedLeft > up_threshold){speedLeft = up_threshold;}
    if (speedLeft < low_threshold){ speedLeft = low_threshold;}
    if (speedRight > up_threshold){ speedRight = up_threshold;}
    if (speedRight < low_threshold){ speedRight = low_threshold;}
    

    Serial.print('\t');
    Serial.print(pid);
    Serial.print('\t');
    Serial.print(speedLeft);
    Serial.print('\t');
    Serial.print(speedRight);
    Serial.println();

    if(speedLeft < 0){setLW_Reverse();}
    else if (speedLeft >= 0){setLW_Forward();}
    if(speedRight < 0){setRW_Reverse();}
    else if(speedRight >= 0){setRW_Forward();}


    // // do first turn
    // firstTurn();

    // Serial.println("NO MORE WHITE");
    goMove();
}

// first left turn state
void firstTurn(){
    // if see all white, turn
    while(isWhite() == true){
    setHardLeftTurn();
    Serial.println("Seeing all white");
    delay(1000);

    firstTurnDone = true;
    }

}

void setHardLeftTurn(){
  setLW_Reverse();
  setRW_Forward();

    analogWrite(BRpinEN, 120);
    analogWrite(FLpinEN, 120);
    analogWrite(BLpinEN, 120);
    analogWrite(FRpinEN, 120);
}

void setHardRightTurn(){
  setLW_Forward();
  setRW_Reverse();

    analogWrite(BRpinEN, 120);
    analogWrite(FLpinEN, 120);
    analogWrite(BLpinEN, 120);
    analogWrite(FRpinEN, 120);
}

// return true if all white
bool isWhite(){

    // must always get new error and sensor values even in loop
    // or else will never leave
//    getError();
    for(uint8_t i = 0; i < SensorCount; i++) {
      // if any are black, return false
      if(s[i] >= 750) {
        // Serial.println("Point2");
        // Serial.println(s[i]);
        // Serial.println(allWhiteThreshold);
          return false;
      }
    }

    Serial.println("Seeing all white");
    return true;

}

// return true if all black
bool isBlack(){
    // must always get new error and sensor values even in loop
    // or else will never leave
//    qtr.read(sensorValues);
    for(uint8_t i = 0; i < SensorCount; i++) {
      // if any don't hit the black threshold, return false
      if(s[i] <= 750) {
        // Serial.println("Point2");
        // Serial.println(s[i]);
        // Serial.println(allWhiteThreshold);
          return false;
      }

    }

    Serial.println("Seeing all black");
    return true;

}

// direction to make LW go backwards
// flip pin if less than 0
void setLW_Reverse(){

      // backward movement pins
      Lpin1 = 0;
      Lpin2 = 1;

    updateDirections();
}

void setLW_Forward(){

      // normal forward movement
      Lpin1 = 1;
      Lpin2 = 0;

    updateDirections();
}

void setRW_Forward(){
     // normal forward movement
      Rpin1 = 1;
      Rpin2 = 0;
      updateDirections();
}


// direction to make RW go backwards
// flip pin if less than 0
void setRW_Reverse(){
      // backward movement pins
      Rpin1 = 0;
      Rpin2 = 1;
    updateDirections();
}

// update pin directions with above
void updateDirections(){
    digitalWrite(FLpin1, Lpin1);
    digitalWrite(FLpin2, Lpin2);
  
    digitalWrite(FRpin1, Rpin1);
    digitalWrite(FRpin2, Rpin2);

    digitalWrite(BLpin1, Lpin1);
    digitalWrite(BLpin2, Lpin2);
  
    digitalWrite(BRpin1, Rpin1);
    digitalWrite(BRpin2, Rpin2);
}


// magnitude of motor speed
void goMove(){

    analogWrite(BRpinEN, abs(speedRight)+deadzone_speed);
    analogWrite(FLpinEN, abs(speedLeft)+deadzone_speed);
    analogWrite(BLpinEN, abs(speedLeft)+deadzone_speed);
    analogWrite(FRpinEN, abs(speedRight)+deadzone_speed);
}

// error function
void getError() {
//   qtr.read(sensorValues);
//   for (uint8_t i = 0; i < SensorCount; i++)
//  {
//    // normalizing into calibrated values
//    // absolute
//    s[i] = (sensorValues[i]-offsetVal[i])*1000/normVal[i];
//    if(s[i] < 0)
//    {
//      s[i] = 0; 
//    }
//     Serial.print(s[i]);
//     Serial.print('\t');
//  }

    uint16_t position = qtr.readLineBlack(sensorValues);
    for (uint8_t i = 0; i < SensorCount; i++)
    {
    // normalizing into calibrated values
    // absolute
    s[i] = sensorValues[i];
     Serial.print(s[i]);
     Serial.print('\t');
  }
  

       
      // delay(1000);

  // dark lines kinda above 600
  // under 100, white

    int error = 3500-position;

  
  P = error;
  I = I + error;
  D = error-prevError;
  // Serial.print('\t');
  // Serial.print(error);
  prevError = error;
}

int getDistanceR() {
  // Clears the trigPin
  digitalWrite(RtrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(RtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(RtrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  Rduration = pulseIn(RechoPin, HIGH);
  // Calculating the distance
  Rdistance = Rduration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Right Distance: ");
  Serial.println(Rdistance);
  return Rdistance;
}


//servo_limit_test
void grab() {
  //raise the claw up to shelf
  //open claw
  //close claw until disk is secured/hits the sensor
  //set pattycount = 1
}
