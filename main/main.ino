#include <QTRSensors.h>

#include <LiquidCrystal.h>
#include "StateFunctions.h"
#include "helper.h"
#include "PU_Cases.h"
#include "Arm.h"
#include "ezButton.h"
#include "Servo.h"
#include "Storage.h"

#include <HCSR04.h>

// initializing variablesvariables 
// IR sensors
  QTRSensors qtr;
  const uint8_t SensorCount = 8;
  uint16_t sensorValues[SensorCount];
  //const int32_t offsetVal[SensorCount] = {449, 227, 197, 180, 183, 247, 160, 373};
  //const int32_t normVal[SensorCount] = {525, 712, 734, 749, 747, 699, 774, 587};
  uint16_t s[SensorCount];   // array of calibrated sensor values


// all black all white detecting
  const int allBlackThreshold = 750; // Threshold for all sensors being considered "black"
  bool allGreaterThanBlack = true;
  const int allWhiteThreshold = 450; // Threshold for all sensors being considered "black"
  bool firstTurnDone = false;

  // pikcup and line
  int rows = 0;

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
  const float Nspeed = 10; //60
  const float Kp = 0.0070; //proportional 0-0.1
  const float Ki = 0.000; //offset  
  const float Kd = 0.02; //difference

//  const float Nspeed = 20 ; //30
//  const float Kp = 0.007; //proportional 0-0.1
//  const float Ki = 0.000; //offset  
//  const float Kd = 0.0; //difference

  float P = 0;
  float I = 0;
  float D = 0;
  float pid = 0;

  int error = 0;
  int32_t newError = 0;
  int prevError = 0;
  int speedLeft = Nspeed;
  int speedRight = Nspeed;

  // min and max power output
  //int up_threshold = 80;
  //int low_threshold = -40;
  int up_threshold = 20;
  int low_threshold = -50;
  int deadzone = 40;
  int deadzone_speed = 40;


  // switching to reverse
  int Lpin1 = 1;
  int Lpin2 = 0;
  int Rpin1 = 1;
  int Rpin2 = 0;


//Ultrasonic
  const byte TRIGGER_PIN_L = 43;
  const byte ECHO_PIN_L = 45;
  const byte TRIGGER_PIN_R = 42;
    const byte ECHO_PIN_R = 44;
  UltraSonicDistanceSensor sensorL(TRIGGER_PIN_L, ECHO_PIN_L);
  UltraSonicDistanceSensor sensorR(TRIGGER_PIN_R, ECHO_PIN_R);


// claw vars
  ezButton claw_limitSwitch(47);  // create ezButton object that attach to pin 7;
  ezButton bottom_limitSwitch(46); // underneath

  Servo claw_servo;  // create servo object to control a servo

  int start = 90;    // starting position
  int pos = start;
  bool go_right = true;
  int desired_pos = 17;


// stepper vars for arm
  const int stepPinRot = 52; //rotate 180 degrees
  const int dirPinRot = 53; 
  const int stepPinVert = 50; //go up or down
  const int dirPinVert = 51; 

  const int RotPinEn = 35;
  const int VertPinEn = 36;
  const int StoragePinEn = 37;

  const int maxstepsRot = 1400; //200 steps per rotation, 7 complete rotations
  const int maxstepsVert = 2000; //200 steps per rotation, 10 complete rotations
  int stepper_stepcounter = 0;    // always reset before each stepper action
  int vert_stepcounter = 0;
  const int vert_step = 1;
  

  bool armFaceFront = true; // arm default faces front


// initialize storage
  Servo servoL;
  Servo servoR;
  // defines pins numbers
  const int stepPinStorage = 48; 
  const int dirPinStorage = 49; 
  const int servoL_Pin = 33;
  const int servoR_Pin = 34;

  // alignment angles for the servo motors
  const int servoL_flat = 42;
  const int servoL_away = 7;
  const int servoR_flat = 8; 
  const int servoR_away = 43; 

  // number of steps to move the platform by the height of a disc (0.5 in)
  const int disc_steps = 635;
  
  // initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
  const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  
  
  int distanceLeftUS = 99;
  int distanceRightUS = 99;
  //
  
  const int pattyNumber = 3;
  int pattyLocation[pattyNumber] = {1, 2, 3};
  int inputsReceived = 0;
  
  bool pressed1 = false;
  bool pressed2 = false;
  bool pressed3 = false;
  bool pressed4 = false;
  bool pressed5 = false;
  bool pressed6 = false;


enum Mode {
    CALIBRATION,
    LINE_FOLLOWING,
    ASSEMBLY,
    RAMP
};

Mode currentMode = CALIBRATION;

void setup() {
  // make all stepper poins HIGH (off before use)
    digitalWrite(RotPinEn, HIGH);
    digitalWrite(VertPinEn, HIGH);
    digitalWrite(StoragePinEn, HIGH);

  // storage initialization
    // define stepper step and direction pins
    pinMode (stepPinStorage,OUTPUT); 
    pinMode (dirPinStorage,OUTPUT);
    // define servo pins
    servoL.attach (servoL_Pin);
    servoR.attach (servoR_Pin);
    // move the aligners to their away position
    servoL.write (servoL_flat);
    servoR.write (servoR_flat);



  // Arm initialization
    // set claw pins
    claw_servo.attach(39);  // attaches the servo on pin 3 to the servo object
    claw_limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
    bottom_limitSwitch.setDebounceTime(50);


  // set stepper pins
    pinMode(stepPinRot,OUTPUT); 
    pinMode(dirPinRot,OUTPUT);
    pinMode(stepPinVert,OUTPUT); 
    pinMode(dirPinVert,OUTPUT);


  // IR pins
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A8, A9, A10, A11, A12, A13, A14, A15}, SensorCount);  // a8 left side
    qtr.setEmitterPin(2);

  
  // wheel pins

    pinMode(FLpin1, OUTPUT);
    pinMode(FLpin2, OUTPUT);
    pinMode(FLpinEN, OUTPUT);

    pinMode(FRpin1, OUTPUT);
    pinMode(FRpin2, OUTPUT);
    pinMode(FRpinEN, OUTPUT);

    pinMode(BLpin1, OUTPUT);
    pinMode(BLpin2, OUTPUT);
    pinMode(BLpinEN, OUTPUT);
    
    pinMode(BRpin1, OUTPUT);
    pinMode(BRpin2, OUTPUT);
    pinMode(BRpinEN, OUTPUT);

    digitalWrite(FLpin1, Lpin1);
    digitalWrite(FLpin2, Lpin2);
    
    digitalWrite(FRpin1, Rpin1);
    digitalWrite(FRpin2, Rpin2);

    digitalWrite(BLpin1, Lpin1);
    digitalWrite(BLpin2, Lpin2);
    
    digitalWrite(BRpin1, Rpin1);
    digitalWrite(BRpin2, Rpin2);


  Serial.begin(9600);

     lcd.begin(16, 2);
  // Print a message to the LCD.
    
    //userInput();
}

void loop() {

//sensorR.measureDistanceCm();
//Serial.println(sensorL.measureDistanceCm());
// Serial.println(getDistance());
  //goStorage();
 // moveArm();

    //Serial.println(getDistance());
  // goStorage();
  // moveArm();
  if(currentMode == CALIBRATION){
    Calibration();
    Serial.println("Calibrated");
    currentMode = LINE_FOLLOWING;
  }
     curvedSection();
     Assembly();
}
   
 
  //Assembly();
  



//    firstTurn();
//    if(firstTurnDone == true){currentMode = ASSEMBLY;}


//    if(assemblyDone == true && getDistance()< 4){currentMode = RAMP;}

// // State changer
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
//     }
