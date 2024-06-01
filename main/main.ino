#include <QTRSensors.h>
#include "StateFunctions.h"
#include "helper.h"
#include "PU_Cases.h"
#include "Arm.h"
#include "ezButton.h"
#include "Servo.h"
#include "Storage.h"
#include <HCSR04.h>
// main file initializes sensors, sets up motor pins
// loop switches between different modes based on 'current mode'

QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
const int32_t offsetVal[SensorCount] = {449, 227, 197, 180, 183, 247, 160, 373};
const int32_t normVal[SensorCount] = {525, 712, 734, 749, 747, 699, 774, 587};
int32_t s[SensorCount];   // array of calibrated sensor values

// all black all white detected
const int allBlackThreshold = 750; // Threshold for all sensors being considered "black"
bool allGreaterThanBlack = true;
const int allWhiteThreshold = 450; // Threshold for all sensors being considered "black"
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


//Ultrasonic
const byte TRIGGER_PIN_1 = 13;
const byte ECHO_PIN_1 = 12;
const byte TRIGGER_PIN_2 = 14;
const byte ECHO_PIN_2 = 15;
UltraSonicDistanceSensor sensor1(TRIGGER_PIN_1, ECHO_PIN_1);
UltraSonicDistanceSensor sensor2(TRIGGER_PIN_2, ECHO_PIN_2);


// arm variables
// claw vars
ezButton claw_limitSwitch(45);  // create ezButton object that attach to pin 7;
ezButton bottom_limitSwitch(43); // underneath

Servo claw_servo;  // create servo object to control a servo



int start = 90;    // starting position
int pos = start;
bool go_right = true;
int desired_pos = 10;

// stepper vars
const int stepPinRot = 51; //rotate 180 degrees
const int dirPinRot = 53; 
const int stepPinVert = 47; //go up or down
const int dirPinVert = 49; 

const int maxstepsRot = 1400; //200 steps per rotation, 7 complete rotations
const int maxstepsVert = 2000; //200 steps per rotation, 10 complete rotations
int stepper_stepcounter = 0;    // always reset before each stepper action

bool armFaceFront = true; // arm default faces front


// initialize storage
Servo servoL;
Servo servoR;

// defines pins numbers
const int stepPinStorage = 10; 
const int dirPinStorage = 11; 
const int servoL_Pin = 8;
const int servoR_Pin = 9;

// alignment angles for the servo motors
const int servoL_flat = 42;
const int servoL_away = 7;
const int servoR_flat = 8; 
const int servoR_away = 43; 

// number of steps to move the platform by the height of a disc (0.5 in)
const int disc_steps = 635;

enum Mode {
    CALIBRATION,
    LINE_FOLLOWING,
    ASSEMBLY,
    RAMP
};

Mode currentMode = LINE_FOLLOWING;

void setup() {

  // storage initialization
  // define stepper step and direction pins
  pinMode (stepPinStorage,OUTPUT); 
  pinMode (dirPinStorage,OUTPUT);
  // define servo pins
  servoL.attach (servoL_Pin);
  servoR.attach (servoR_Pin);
  // move the aligners to their away position
  servoL.write (servoL_away);
  servoR.write (servoR_away);



  // Arm initialization
  // set claw pins
  claw_servo.attach(41);  // attaches the servo on pin 3 to the servo object
  claw_limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
  bottom_limitSwitch.setDebounceTime(50);


  // set stepper pins
  pinMode(stepPinRot,OUTPUT); 
  pinMode(dirPinRot,OUTPUT);
  pinMode(stepPinVert,OUTPUT); 
  pinMode(dirPinVert,OUTPUT);
  initializeAll();
  Serial.begin(9600);
}

void loop() {

  //goStorage();
  moveArm();


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


//    if(assemblyDone == true && getDistance()< 4){currentMode = RAMP;}


//      //State changer
//     switch (currentMode) {
//         case LINE_FOLLOWING:
// //            Serial.println("Line Following");
//             lineFollowing();
//             break;
//         case ASSEMBLY:
//             Assembly();
//             // after assembly is done
//             currentMode = LINE_FOLLOWING;
//             firstTurnDone = false;
//             break;
//         case RAMP:
//             ramp();
//             break;
    // }
  


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
