#include <Arduino.h>
#include "StateFunctions.h"
#include "helper.h"
#include <QTRSensors.h>
#include "PU_Cases.h"
#include "Arm.h"
#include <IRremote.hpp> 
//#include <HCSR04.h>
void userInput(){
  IrReceiver.begin(IR_RECEIVE_PIN);
  
  while(inputsReceived != pattyNumber)
  {  
      
      // set up the LCD's number of columns and rows:
    if (IrReceiver.decode() && (inputsReceived != pattyNumber)) {
          IrReceiver.resume();
          int command = IrReceiver.decodedIRData.command;
            if((command == IR_BUTTON_1)&&(pressed1 == false)){
              Serial.println("Pressed on button 1");
              pattyLocation[inputsReceived] = 1;
              inputsReceived++;
              pressed1 = true;
            } else if((command == IR_BUTTON_2)&&(pressed2 == false)){
              Serial.println("Pressed on button 2");
              pattyLocation[inputsReceived] = 2;
              inputsReceived++;
              pressed2 = true;
            } else if((command == IR_BUTTON_3)&&(pressed3 == false)){
              Serial.println("Pressed on button 3");
              pattyLocation[inputsReceived] = 3;
              inputsReceived++;
              pressed3 = true;
            } else if((command == IR_BUTTON_4)&&(pressed4 == false)){
              Serial.println("Pressed on button 4");
              pattyLocation[inputsReceived] = 4;
              inputsReceived++;
              pressed4 = true;
            } else if((command == IR_BUTTON_5)&&(pressed5 == false)){
              Serial.println("Pressed on button 5");
              pattyLocation[inputsReceived] = 5;
              inputsReceived++;
              pressed5 = true;
            } else if((command == IR_BUTTON_6)&&(pressed6 == false)){
              Serial.println("Pressed on button 6");
              pattyLocation[inputsReceived] = 6;
              inputsReceived++;
              pressed6 = true;
            }
          }
  
            lcd.setCursor(0, 0);
            lcd.print("Enter Location:");
            lcd.setCursor(0, 1);
            lcd.print(pattyLocation[0]);
            lcd.setCursor(2, 1);
            lcd.print(pattyLocation[1]);
            lcd.setCursor(4, 1);
            lcd.print(pattyLocation[2]);
  
   
      }
}

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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Mode:");
            lcd.setCursor(0, 1);
            lcd.print("Calibration");
 
  
  for (uint16_t i = 0; i < 800; i++)
  {
    if (calCounter == 6)
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

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Calibration");
            lcd.setCursor(0, 1);
            lcd.print("Complete");
            
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
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Centered");

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

    

    Serial.println("Assembly mode");

    // follow line until reaches all black
     while(isBlack() == false)
     {
       lineFollowing();
     }


    analogWrite(BRpinEN, 0);
    analogWrite(FLpinEN, 0);
    analogWrite(BLpinEN, 0);
    analogWrite(FRpinEN, 0);
    
    
    for(int i = 0; i < 3; i++){
      pickUp(pattyLocation[i]);
      clawPickup();

      
      backtoStart();
    }
    // turn stepper pins off after assembly
    digitalWrite(RotPinEn, HIGH);
    digitalWrite(VertPinEn, HIGH);
    digitalWrite(StoragePinEn, HIGH);

    //backtoStart();
    //pickUp(pattyLocation2);
    //backtoStart();
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

    //clawSequence();

    // exit

}

void curvedSection(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Curved Section");
  delay(500);

  delay(500);
  while(getDistance() > 10)
  {
    Serial.print(getDistance());
    lineFollowing();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LineFollowing");
    lcd.setCursor(0, 1);
    lcd.print("LS:");
    lcd.setCursor(6, 1);
    lcd.print("RS:");
    lcd.setCursor(12,1);
    lcd.print("D:");
    lcd.setCursor(3, 1);
    lcd.print(abs(speedLeft));
    lcd.setCursor(9,1);
    lcd.print(abs(speedRight));
    lcd.setCursor(14,1);
    lcd.print(getDistance());
  }
  firstTurn();
  
  
}
