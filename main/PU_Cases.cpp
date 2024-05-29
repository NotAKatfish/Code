#include <Arduino.h>
#include "helper.h"

void pickUp(int pattyLocation){

  int rows = 0;

  // if first line
  if(pattyLocation == 1 || pattyLocation == 6)
  {


    // line follow while it passes the black row
    // at the end of the black row stop
    while(isBlack() == true){lineFollowing();}

    // NOW INITIATE TURN

    // if 1 on left
    if(pattyLocation == 1){

      delay(10000);
      

      // once we see white in the left two sensors
      // getError();

      // hard left until see white in the left two sensors again

      // then line follow
      // lineFollowing();



      // check ultrasonic to see if we can stop
      //actual claw grab

      // reverse until see all black

      // hard right turn

      // reverse back to starting point

    }

    // if 6 on right
    if(pattyLocation == 6){
      // setHardRightTurn();
      Serial.println("Seeing all black");
      delay(1000);
    }
    

  }

  // row 2
  if(pattyLocation == 2 || pattyLocation == 5)
  {
    
    // go to second row
    while(rows < 2)
    {
      lineFollowing();

      // line follow while it passes the black row
      // at the end of the black row increment
      if(isBlack() == true){
        while(isBlack() == true){lineFollowing();}
        rows++;
      }
    }

    // turn at second row

  }





  // row 3
  if(pattyLocation == 3 || pattyLocation == 4)
  {

    // go to third row
    while(rows < 3)
    {
      lineFollowing();

      // line follow while it passes the black row
      // at the end of the black row increment
      if(isBlack() == true){
        while(isBlack() == true){lineFollowing();}
        rows++;
      }
    }

    // turn at third row
  }



}



void pickUpLeft(){

}

void pickUpRight(){
  
}




