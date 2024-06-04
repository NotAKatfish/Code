#include <Arduino.h>
#include "helper.h"
#include "PU_Cases.h"
#include "Arm.h"
#include <HCSR04.h>

int rowOfPatty(int pattyLocation)
{
  int rowAssignment[6] = {1 ,2, 3, 3, 2, 1};
  return rowAssignment[pattyLocation-1];
}

bool isOnLeft(int pattyLocation) {return ((pattyLocation + 3) <= 6);}
void pickUp(int pattyLocation){
  
  int upOrDown = rowOfPatty(pattyLocation)-(currRow);
  lcd.setCursor(3,0);
  lcd.print(upOrDown);
  if(upOrDown > 0){
    while(currRow != rowOfPatty(pattyLocation)){
      lineFollowing();
      bool onCross = false;
      Serial.print("point1");
      if((!onCross)&&(isBlack())) {
        currRow++;
        onCross = true;
        Serial.println(onCross);
      }
      if(!isBlack()) {onCross = false;}
      Serial.println(onCross);
      Serial.println(currRow);
    }
  } else if(upOrDown < 0){
    while(currRow != rowOfPatty(pattyLocation)){
      setFullReverse();
      bool onCross = false;
      if((!onCross)&&(isBlack())) {
        currRow--;
        onCross = true;
      }
      if(!isBlack()) {onCross = false;}
    }
  }
    delay(150);
    stop();
    
    if(isOnLeft(pattyLocation)){pickUpLeft();}
    else {pickUpRight();}
    
    backToCenter(pattyLocation);
  }

 


void pickUpLeft(){

  while(!isWhite()){
    setHardLeftTurn();
  }
  getError();
  
  Serial.println();
  
  while(sensorValues[1] <= 800){
   setHardLeftTurn(); 
   getError();
   Serial.println();
  }
  while (getDistance()>5){
    lineFollowing();
    updateLCDLF();
  }
  stop(); delay(1000);
  while(!isBlack()){
    setFullReverse();
  }
  stop(); 
  setFullForward();
  delay(100);
  
  while (getDistance()>2){
    lineFollowing();
    updateLCDLF();
  }
  delay(100);
  stop();
  delay(1000);
  }


void pickUpRight(){
  while(!isWhite()){
    setHardRightTurn();
  }
  getError();
  Serial.println();
  
  while(sensorValues[6] <= 800){
   setHardRightTurn(); 
   getError();
   Serial.println();
  }
  while (getDistance()>5){
    lineFollowing();
    updateLCDLF();
  }
  stop(); delay(1000);
  while(!isBlack()){
    setFullReverse();
  }
  stop(); 
  setFullForward();
  delay(100);
  
  while (getDistance()>2){
    lineFollowing();
    updateLCDLF();
  }
  delay(100);
  stop();
  delay(10000);
}

void dropOff(int n){
//  while(rows < n){
//      lineFollowing();
//      if(isHalfBlack() == true){
//        while(isHalfBlack() == true){
//          lineFollowing();
//        }
//        rows++;
//      }
//    }
//    if (sensor1.measureDistanceCm()>25 && sensor2.measureDistanceCm()>25){
//    setHardRightTurn();
//  } else if (sensor1.measureDistanceCm()>5 && sensor2.measureDistanceCm()>5){
//    lineFollowing();
//  } 
}




void backToCenter(int pattyLocation) {
   //reverse straight until the sensors read all black
  while(!isBlack()) {setFullReverse();}
  stop();
  setFullForward();
  delay(550);
  stop();
  if(isOnLeft(pattyLocation)){
    while(!isWhite()){setHardRightTurn();}
    getError();
    Serial.println();
    while(sensorValues[6] <= 800){
      setHardRightTurn(); 
      getError();
      Serial.println(); 
    }
  } else {
    while(!isWhite()){setHardLeftTurn();}
    getError();
    Serial.println();
    while(sensorValues[1] <= 800){
      setHardLeftTurn(); 
      getError();
      Serial.println(); 
    }
  }
  while (abs(getError())>1200){
    lineFollowing();
    updateLCDLF();
//    bool onCross = false;
//      if((!onCross)&&(isBlack())) {
//        currRow++;
//        onCross = true;
//      }
//      if(!isBlack()) {onCross = false;}
    
  }
  while(!isBlack()) {setFullReverse();}
  setFullForward();
  Serial.print("point2");
  delay(500);
  
  stop(); delay(1000);
  
}

  
//
//  // turns to avoid middle black line
//  setHardLeftTurn();
//  delay(500);
//  while(sensorValues[3] <= 800 && sensorValues[4]<= 800){ //or until we get a certain distacne away from the shelf
//    setHardLeftTurn();
//  }
//  while(rows > -1){
//    lineFollowing();
//    if(isBlack() == true){
//        while(isBlack() == true){
//          lineFollowing();
//        }
//        rows--;
//    }
//  }
//  // if rows > -1
//  rows = 0;
//  
//  //roatate 180 degrees
//  //delay for 1 second
//  //stop rotating when the middle two sensors read black
//  setHardLeftTurn();
//  delay(2000);
