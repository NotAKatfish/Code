#include <QTRSensors.h>
#include "StateFunctions.h"
#include "helper.h"
// main file initializes sensors, sets up motor pins
// loop switches between different modes based on 'current mode'

QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

// Motor control pins
int FLpin1 = 22;
int FLpin2 = 23;
int FLpinEN = 10;
int FRpin1 = 24;
int FRpin2 = 25;
int FRpinEN = 11;
int BLpin1 = 28;
int BLpin2 = 29;
int BLpinEN = 12;
int BRpin1 = 26;
int BRpin2 = 27;
int BRpinEN = 13;

const float Nspeed = 60;
const float Kp = .2;
const float Ki = 0.0;
const float Kd = 0.0;

int error = 0;
int prevError = 0;
int speedLeft = Nspeed;
int speedRight = Nspeed;
int threshold = 100;

float P = 0;
float I = 0;
float D = 0;
float pid = 0;

enum Mode {
    LINE_FOLLOWING,
    PICKUP,
    RAMP
};

Mode currentMode = LINE_FOLLOWING;

void setup() {
    initializeAll();  // see helper.cpp
    Serial.begin(9600);
}

void loop() {

  // need to implement method to switch
  // switch between functions in state functions
    switch (currentMode) {
        case LINE_FOLLOWING:
            lineFollowing();
            break;
        case PICKUP:
            pickUp();
            break;
        case RAMP:
            ramp();
            break;
    }
}
