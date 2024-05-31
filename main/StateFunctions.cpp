#include <Arduino.h>
#include "StateFunctions.h"
#include "helper.h"
#include <QTRSensors.h>
#include "PU_Cases.h"
//#include <HCSR04.h>


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
    
    // always starts at start line
    int pattyLocation1 = 1;
    int pattyLocation2 = 2;
    int pattyLocation3 = 3;
    //pickup patty, replace patty Location with patties want to grab
    pickUp(pattyLocation1);
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
