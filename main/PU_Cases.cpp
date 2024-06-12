#include <Arduino.h>
#include "helper.h"
#include "PU_Cases.h"
#include "Arm.h"
#include <HCSR04.h>

int rowOfPatty(int pattyLocation)
//Takes in pattyLocation, gives the row it is in
{
  int rowAssignment[6] = {1 ,1, 2, 2, 3, 3};
  return rowAssignment[pattyLocation-1];
}

bool isOnLeft(int pattyLocation) {return ((pattyLocation + 1)%2 == 0);} // checks if its on the left or right
void pickUp(int pattyLocation){
  deadzone_speed = 65;
  
  int upOrDown = rowOfPatty(pattyLocation)-(currRow); //check if patty location is in front or behind current row
  lcd.setCursor(3,0);
  lcd.print(upOrDown);
  if(upOrDown > 0){ //if in front, move to destination row, increment currentRow when cross is detected
    bool onCross = false; // make sure each cross is registered only once
    while(currRow != rowOfPatty(pattyLocation)){ 
      lineFollowing();
      if((!onCross)&&(isBlack())) {
        currRow++;
        onCross = true;
        Serial.println(onCross);
      }
      if(!isBlack()) {onCross = false;}
      Serial.println(onCross);
      Serial.println(currRow);
    }
  } else if(upOrDown < 0){ //if behind, move to destination row, decrement currentRow when cross is detected
    bool onCross = false;
    while(currRow != rowOfPatty(pattyLocation)){
      setFullReverse();
      if((!onCross)&&(isBlack())) {
        currRow--;
        onCross = true;
      }
      if(!isBlack()) {onCross = false;}
    }
  }
    delay(150);
    stop();
    
    if(isOnLeft(pattyLocation)){pickUpLeft();} // checks if patty location is on the left or right
    else {pickUpRight();}
  
    backToCenter(pattyLocation);
  }



void pickUpLeft(){

  while(!isWhite()) { 
    // initiates left turn, forces it to read white space before centering to row
    setHardLeftTurn();
  }
  getError();
  
  Serial.println();
  
  while(sensorValues[1] <= 800){ // lock onto black row
   setHardLeftTurn(); 
   getError();
   Serial.println();
  }
  while (getDistance()>5){ // line follow until distance is met
    lineFollowing();
    updateLCDLF();
  }
  stop(); delay(1000);
  while(!isBlack()){ // back up to black line to give more room for line following and centering
    setFullReverse();
  }
  stop(); 
  setFullForward(); // move slightly infront of black lne
  delay(100);
//  
//  while (getDistance()>2){ // line follow until distance is met
//    lineFollowing();
//    updateLCDLF();
//  }
//  while(getDistance()>2){
//    for(int i = 0; i<3;){
//      if(getDistance() <=8){
//        i++;
//      lineFollowing();
//    }else{
//      i=0;
//    }
//  }
//  lineFollowing();
//  updateLCDLF();
//}
while(limitTouched(claw_limitSwitch)){
    proceed=false;
  }
  proceed=true;
while (!(limitTouched(claw_limitSwitch))){ 
    lineFollowing();
    updateLCDLF();
  }
  
 delay(100);
  stop();
  delay(1000); 
  clawPickup();
}
//    }
//  }
//  
//  }


void pickUpRight(){ // read pickUpLeft() 
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
while(limitTouched(claw_limitSwitch)){
    proceed=false;
  }
  proceed=true;
while (!(limitTouched(claw_limitSwitch))){ 
    lineFollowing();
    updateLCDLF();
  }
  delay(100);
  stop();
  delay(1000);
  clawPickup();
  //clawDropoff();
  //goDownAndGrab();
}

void dropOffRight(){ // read pickUpLeft() 
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
while(limitTouched(claw_limitSwitch)){
    proceed=false;
  }
  proceed=true;
while (!(limitTouched(claw_limitSwitch))){ 
    lineFollowing();
    updateLCDLF();
  }
  delay(100);
  stop();
  delay(1000);
  //clawPickup();
  clawDropoff();
  //goDownAndGrab();
}
 
void dropOff(int dropOffLocation){
  bool onT = false;
  while(currRow < dropOffLocation){
      lineFollowing();  
      if((!onT)&&(isHalfBlack())) {
        currRow++;
        onT = true;
      }
      if(!isHalfBlack()) {onT = false;}
  }
  delay(150);
  stop();
  dropOffRight();
  backToCenter(currRow);
    

}




void backToCenter(int pattyLocation) {
   //reverse straight until the sensors read all black
  while(!isBlack()) {setFullReverse();}
  stop();
  setFullForward();// move slightly infront of cross
  delay(550);
  stop();
  if(isOnLeft(pattyLocation)){ // check if exiting row is left or right, and make it face forward
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
  while (abs(getError())>500){
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
