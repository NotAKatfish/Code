#include <QTRSensors.h>
#include "StateFunctions.h"
#include "helper.h"
// main file initializes sensors, sets up motor pins
// loop switches between different modes based on 'current mode'

QTRSensors qtr;
const uint8_t SensorCount = 8;
int sensorValues[SensorCount];
const int32_t offsetVal[SensorCount] = {449, 227, 197, 180, 183, 247, 160, 373};
const int32_t normVal[SensorCount] = {525, 712, 734, 749, 747, 699, 774, 587};
int32_t s[SensorCount];   // array of calibrated sensor values

// all black all white detected
const int allBlackThreshold = 750; // Threshold for all sensors being considered "black"
bool allGreaterThanBlack = true;
const uint8_t allWhiteThreshold = 450; // Threshold for all sensors being considered "black"

// Motor control pins
int FLpin1 = 22;
int FLpin2 = 23;
int FLpinEN = 13;

int FRpin1 = 24;
int FRpin2 = 25;
int FRpinEN = 12;

int BLpin1 = 28;
int BLpin2 = 29;
int BLpinEN = 11;

int BRpin1 = 26;
int BRpin2 = 27;
int BRpinEN = 10;


// speed vars, pid
const float Nspeed = 80;
const float Kp = .2;
const float Ki = 0.0;
const float Kd = 0.2;
float P = 0;
float I = 0;
float D = 0;
float pid = 0;

int error = 0;
int prevError = 0;
int speedLeft = Nspeed;
int speedRight = Nspeed;

// min and max power output
int up_threshold = 150;
int low_threshold = -100;

// switching to reverse
int Lpin1 = 1;
int Lpin2 = 0;
int Rpin1 = 1;
int Rpin2 = 0;


enum Mode {
    LINE_FOLLOWING,
    PICKUP,
    RAMP
};

Mode currentMode = LINE_FOLLOWING;

void setup() {
  initializeAll();
  Serial.begin(9600);
}

void loop() {


    // State changer
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
  


  // // check if its time to go into pickup mode from line following
  // // all 8 sensors black
  // if(currentMode == LINE_FOLLOWING){
  //   for(int i = 0; i < 8; i++) {
  //     if(s[i] <= allBlackThreshold) {
  //         allGreaterThanBlack = false;
  //         break;
  //     }

  //   }
  // }

  // // Switch to PICKUP mode if all sensors are black
  // if (currentMode == LINE_FOLLOWING && allGreaterThanBlack) {
  //     currentMode = PICKUP;
  // }
}
