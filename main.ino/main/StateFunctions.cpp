#include "StateFunctions.h"
#include "helper.h"
#include <QTRSensors.h>

extern QTRSensors qtr;
extern const uint8_t SensorCount;
extern uint16_t sensorValues[];
extern const float Nspeed;
extern const float Kp;
extern const float Ki;
extern const float Kd;
extern int threshold;

extern int error;
extern int prevError;
extern int speedLeft;
extern int speedRight;

extern float P;
extern float I;
extern float D;
extern float pid;

extern int FLpinEN;
extern int FRpinEN;
extern int BLpinEN;
extern int BRpinEN;

void lineFollowing() {
    getError();
    pid = (Kp * P) - (Ki * I) + (Kd * D);
    speedLeft = Nspeed - pid;
    speedRight = Nspeed + pid;
    if (speedLeft > threshold){ speedLeft = threshold;}
    if (speedLeft < 0){ speedLeft = 0;}
    if (speedRight > threshold){ speedRight = threshold;}
    if (speedRight < 0){ speedRight = 0;}
    Serial.print('\t');
    Serial.print(pid);
    Serial.print('\t');
    Serial.print(speedLeft);
    Serial.print('\t');
    Serial.print(speedRight);
    Serial.println();

    analogWrite(BRpinEN, speedRight);
    analogWrite(FLpinEN, speedLeft);
    analogWrite(BLpinEN, speedLeft);
    analogWrite(FRpinEN, speedRight);
}


Void pickUp(){
    Serial.println("Pickup mode");

    // turn into designated quadrant

    // ultrasound detects wall, stop

    // clawSequence();  // grabs item, puts in storage box

    //


}

Void ramp(){
    Serial.println("ramp mode");

    // start when detect ultrasonic
    
    // increase torque, go over ramp
}

Void dropOff(){
    Serial.println("drop off");
    // turn 90 deg right into drop off bay

    //clawSequence();

    // exit

}

