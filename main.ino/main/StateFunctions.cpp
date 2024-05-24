#include <Arduino.h>
#include "StateFunctions.h"
#include "helper.h"
#include <QTRSensors.h>

void pickUp(){
    Serial.println("Pickup mode");
    lineFollowing();

    // always make starting point center between 1 and 2
    // cases for which number
    int case = 1;
    // if need to turn left
    // if see all black, turn left
    if(case == 1){
      case1();
    }

    goMove();
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

