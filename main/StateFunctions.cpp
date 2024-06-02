#include <Arduino.h>
#include "StateFunctions.h"
#include "helper.h"
#include <QTRSensors.h>
#include "PU_Cases.h"
#include "Arm.h"
//#include <HCSR04.h>

void Calibration(){
  uint16_t calCounter = 0;
  bool onWhite = false;
  bool isCentered = false;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  // analogRead() takes about 0.1 ms on an AVR.
  // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
  // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 800; i++)
  {
    if (calCounter == 2)
    {
      break;
    }
    if (calCounter % 2 == 0) {
      setLW_Forward();
      setRW_Forward();
      Serial.println("GoingForward");
    } else {
      setLW_Reverse();
      setRW_Reverse();
      Serial.println("GoingReverse");
    }
          analogWrite(BRpinEN, 60);
          analogWrite(FLpinEN, 60);
          analogWrite(BLpinEN, 60);
          analogWrite(FRpinEN, 60);
   
    qtr.calibrate();
    qtr.read(sensorValues);
    for (uint8_t i = 0; i < SensorCount; i++){
       s[i] = sensorValues[i];
       Serial.print(sensorValues[i]);
       Serial.print(' ');
    }
    if (onWhite == false)
    {
      if (isWhite() == true) {
        delay(200);
        calCounter++;
        Serial.println(calCounter);
        onWhite = true;
      }
    }
    if (isBlack() == true)
    {
      onWhite = false;
    }
  }
    while (isCentered == false){
      setLW_Forward();
      setRW_Reverse();
      qtr.readCalibrated(sensorValues);
       for (uint8_t i = 0; i < SensorCount; i++){
         Serial.print(sensorValues[i]);
         Serial.print(' ');
       }
        Serial.println();
      if (sensorValues[3] < 800){
        analogWrite(BRpinEN, 50);
        analogWrite(FLpinEN, 120);
        analogWrite(BLpinEN, 120);
        analogWrite(FRpinEN, 50);
      } else {
        analogWrite(BRpinEN, 0);
        analogWrite(FLpinEN, 0);
        analogWrite(BLpinEN, 0);
        analogWrite(FRpinEN, 0);
        isCentered = true;
        Serial.print("centered");
    }
    }
  
  // print the calibration minimum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(3000);

  
  }
  


void Assembly(){

    // turn on stepper pins before assembly
    digitalWrite(RotPinEn, LOW);
    digitalWrite(VertPinEn, LOW);
    digitalWrite(StoragePinEn, LOW);
    //goStorage(-1);  
    clawPickup();

    Serial.println("Assembly mode");

    // follow line until reaches all black
    // while(isBlack() == false)
    // {
    //   lineFollowing();
    // }
    
    // always starts at start line
    int pattyLocation1 = 1;
    int pattyLocation2 = 2;
    int pattyLocation3 = 3;
    //pickup patty, replace patty Location with patties want to grab
    pickUp(pattyLocation1);
    //clawPickup();
    // pickUp(pattyLocation2);
    // pickUp(pattyLocation3);

    // assembly ends at the starting location

    // assemblyDone = true;
}



void ramp(){
    Serial.println("ramp mode");

    // start when detect ultrasonic
    
    // increase torque, go over ramp
}

void dropOff(){
    Serial.println("drop off");
    // turn 90 deg right into drop off bay
    int dropoffLocation = 2;
    //if the robot sees black on the right most sensor, count the row
    //keep going straight
    //when row number=dropofflocation stop 
    //setHardRightTurn();
    //go straight until both ultrasonic sensors read about 3-4 cm
    //clawDropoff();
    // reverse until you see all black
    //setHardLeftTurn();
   

    // exit

}
