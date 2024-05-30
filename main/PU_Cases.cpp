#include <Arduino.h>
#include "helper.h"
#include "PU_Cases.h"

void pickUp(int pattyLocation){

  int rows = 0;

  // ROW 1
  if(pattyLocation == 1 || pattyLocation == 6)
  {
    // line follow while it passes the black row
    // at the end of the black row stop
    while(isBlack() == true){
      lineFollowing();
    }
    //Turn until we are 10 cm from the wall
    if (getDistanceR()>10){
      if (pattyLocation == 1){
      setHardLeftTurn();
      } else {
        setHardRightTurn();
      }
    } else if (getDistanceR()>3) { //line follow until we are 3 cm from the wall or line follow until the sensor touches the wall
      lineFollowing();
    } else {
      //turn off motors
    }
    //grab(); //sevo_limit_test
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
  if (getDistanceR()>10){
    setHardLeftTurn();
  } else if (getDistanceR()>1){
    lineFollowing();
  }
}

void pickUpRight(){
  if (getDistanceR()>10){
    setHardRightTurn();
  } else if (getDistanceR()>1){
    lineFollowing();
  }
}
