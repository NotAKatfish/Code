#include <Arduino.h>
#include "helper.h"
#include "PU_Cases.h"
#include "Arm.h"
#include <HCSR04.h>

void pickUp(int pattyLocation){

  // ROW 1
  if(pattyLocation == 1 || pattyLocation == 6)
  {
//    // line follow while it passes the black row twice
//    while(rows < 1){
//      lineFollowing();
//      if(isBlack() == true){
//        while(isBlack() == true){
//          lineFollowing();
//        }
//        rows++;
//      }
        
      if (pattyLocation == 1){
        pickUpLeft();
      } else {
        pickUpRight();
      } 
  }
}
// //ROW 2
//   if(pattyLocation == 2 || pattyLocation == 5)
//   {
//     // line follow while it passes the black row twice
//     while(rows < 2){
//       lineFollowing();
//       if(isBlack() == true){
//         while(isBlack() == true){
//           lineFollowing();
//         }
//         rows++;
//       }
//     }    
//       if (pattyLocation == 2){
//         pickUpLeft();
//       } else {
//         pickUpRight();
//       } 
//   }


//   // ROW 3
//   if(pattyLocation == 3 || pattyLocation == 4)
//   {
//     // line follow while it passes the black row twice
//     while(rows < 3){
//       lineFollowing();
//       if(isBlack() == true){
//         while(isBlack() == true){
//           lineFollowing();
//         }
//         rows++;
//       }
//     }    
//       if (pattyLocation == 3){
//         pickUpLeft();
//       } else {
//         pickUpRight();
//       } 
//   }
// }


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
  if (getDistance() > 25){
    setHardLeftTurn();
  } else if (getDistance()>2){
    lineFollowing();
  }
  analogWrite(BRpinEN, 0);
  analogWrite(FLpinEN, 0);
  analogWrite(BLpinEN, 0);
  analogWrite(FRpinEN, 0);
  delay(1000);
}

void pickUpRight(){
  if (getDistance() > 25){
    setHardRightTurn();
  } else if (getDistance()>2){
    lineFollowing();
  }
  analogWrite(BRpinEN, 0);
  analogWrite(FLpinEN, 0);
  analogWrite(BLpinEN, 0);
  analogWrite(FRpinEN, 0);
  delay(1000);
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




void backtoStart() {
   //reverse straight until the sensors read all black
  while(isBlack()==false){
    //setFullReverse();
  }

  // turns to avoid middle black line
  setHardLeftTurn();
  delay(500);
  while(s[3] <= 800 && s[4]<= 800){ //or until we get a certain distacne away from the shelf
    setHardLeftTurn();
  }
  while(rows > -1){
    lineFollowing();
    if(isBlack() == true){
        while(isBlack() == true){
          lineFollowing();
        }
        rows--;
    }
  }
  // if rows > -1
  rows = 0;
  
  //roatate 180 degrees
  //delay for 1 second
  //stop rotating when the middle two sensors read black
  setHardLeftTurn();
  delay(2000);



}
