#include <QTRSensors.h>
#include "StateFunctions.h"
#include "helper.h"
#include "PU_Cases.h"
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
bool firstTurnDone = false;

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

//Right Ultrasonic Pins
const int RtrigPin = 9;
const int RechoPin = 8;
long Rduration;
int Rdistance;

////Left Ultrasonic Pins
//const int LtrigPin = 9;
//const int LechoPin = 8;
//long Lduration;
//int Ldistance;


// speed vars, pid
//const float Nspeed = 40; //60
//const float Kp = 0.002; //proportional 0-0.1
//const float Ki = 0.000; //offset  
//const float Kd = 0.05; //difference

const float Nspeed = 25 ; //30
const float Kp = 0.003; //proportional 0-0.1
const float Ki = 0.000; //offset  
const float Kd = 0.015; //difference

float P = 0;
float I = 0;
float D = 0;
float pid = 0;

int error = 0;
int prevError = 0;
int speedLeft = Nspeed;
int speedRight = Nspeed;

// min and max power output
//int up_threshold = 80;
//int low_threshold = -40;
int up_threshold = 55;
int low_threshold = -50;
int deadzone = 40;
int deadzone_speed = 35;


// switching to reverse
int Lpin1 = 1;
int Lpin2 = 0;
int Rpin1 = 1;
int Rpin2 = 0;



enum Mode {
    LINE_FOLLOWING,
    ASSEMBLY,
    RAMP
};

Mode currentMode = LINE_FOLLOWING;

void setup() {
  initializeAll();
  Serial.begin(9600);
}

void loop() {
    //getDistanceR();
    //if first turn done
    // change to pickup mode

    // setLW_Reverse();
    // setRW_Reverse();

    // setLW_Forward();
    // setRW_Forward();

    // goMove();



//    firstTurn();
//    if(firstTurnDone == true){currentMode = ASSEMBLY;}



     //State changer
    switch (currentMode) {
        case LINE_FOLLOWING:
//            Serial.println("Line Following");
            lineFollowing();
            break;
        case ASSEMBLY:
            Assembly();
            // after assembly is done
            currentMode = LINE_FOLLOWING;
            firstTurnDone = false;
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
