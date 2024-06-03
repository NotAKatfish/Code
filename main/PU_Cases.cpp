#include <Arduino.h>
#include "helper.h"
#include "PU_Cases.h"
#include "Arm.h"
#include <HCSR04.h>

void pickUp(int pattyLocation){

  int rows = 0;

  // ROW 1
  if(pattyLocation == 1 || pattyLocation == 6)
  {
    // line follow while it passes the black row twice
    while(rows < 1){
      lineFollowing();
      if(isBlack() == true){
        while(isBlack() == true){
          lineFollowing();
        }
        rows++;
      }
    }    
      if (pattyLocation == 1){
        pickUpLeft();
      } else {
        pickUpRight();
      } 
  }
  

//ROW 2
  if(pattyLocation == 2 || pattyLocation == 5)
  {
    // line follow while it passes the black row twice
    while(rows < 2){
      lineFollowing();
      if(isBlack() == true){
        while(isBlack() == true){
          lineFollowing();
        }
        rows++;
      }
    }    
      if (pattyLocation == 2){
        pickUpLeft();
      } else {
        pickUpRight();
      } 
  }


  // ROW 3
  if(pattyLocation == 3 || pattyLocation == 4)
  {
    // line follow while it passes the black row twice
    while(rows < 3){
      lineFollowing();
      if(isBlack() == true){
        while(isBlack() == true){
          lineFollowing();
        }
        rows++;
      }
    }    
      if (pattyLocation == 3){
        pickUpLeft();
      } else {
        pickUpRight();
      } 
  }
}


//    // if 1 on left
//    if(pattyLocation == 1){
//
//      delay(10000);
//      
//
//      // once we see white in the left two sensors
//      // getError();
//
//      // hard left until see white in the left two sensors again
//
//      // then line follow
//      // lineFollowing();
//
//
//
//      // check ultrasonic to see if we can stop
//      //actual claw grab
//
//      // reverse until see all black
//
//      // hard right turn
//
//      // reverse back to starting point
//
//    }
//
//    // if 6 on right
//    if(pattyLocation == 6){
//      // setHardRightTurn();
//      Serial.println("Seeing all black");
//      delay(1000);
//    }


void pickUpLeft(){
  if (sensor1.measureDistanceCm()>25 && sensor2.measureDistanceCm()>25){
    setHardLeftTurn();
  } else if (sensor1.measureDistanceCm()>5 && sensor2.measureDistanceCm()>5){
    lineFollowing();
  }
}

void pickUpRight(){
  if (sensor1.measureDistanceCm()>25 && sensor2.measureDistanceCm()>25){
    setHardRightTurn();
  } else if (sensor1.measureDistanceCm()>5 && sensor2.measureDistanceCm()>5){
    lineFollowing();
  }
}

void dropOff(int n){
  while(rows < n){
      lineFollowing();
      if(isHalfBlack() == true){
        while(isHalfBlack() == true){
          lineFollowing();
        }
        rows++;
      }
    }
    if (sensor1.measureDistanceCm()>25 && sensor2.measureDistanceCm()>25){
    setHardRightTurn();
  } else if (sensor1.measureDistanceCm()>5 && sensor2.measureDistanceCm()>5){
    lineFollowing();
  } 
}
