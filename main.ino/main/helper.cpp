#include "helper.h"
#include <QTRSensors.h>


extern QTRSensors qtr;
extern const uint8_t SensorCount;
extern uint16_t sensorValues[];


extern int FLpin1;
extern int FLpin2;
extern int FLpinEN;
extern int FRpin1;
extern int FRpin2;
extern int FRpinEN;
extern int BLpin1;
extern int BLpin2;
extern int BLpinEN;
extern int BRpin1;
extern int BRpin2;
extern int BRpinEN;

extern int error;
extern int prevError;

extern float P;
extern float I;
extern float D;


void initializeAll(){
      // configure the sensors
    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A8, A9, A10, A11, A12, A13, A14, A15}, SensorCount);
    qtr.setEmitterPin(2);
    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    for (uint16_t i = 0; i < 400; i++) {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(9600);
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);


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

    digitalWrite(FLpin1, LOW);
    digitalWrite(FLpin2, HIGH);

    digitalWrite(FRpin1, LOW);
    digitalWrite(FRpin2, HIGH);

    digitalWrite(BLpin1, HIGH);
    digitalWrite(BLpin2, LOW);

    digitalWrite(BRpin1, HIGH);
    digitalWrite(BRpin2, LOW);
}


// error function
void getError() {
    qtr.read(sensorValues);
    for (uint8_t i = 0; i < SensorCount; i++) {
        Serial.print(sensorValues[i]);
        Serial.print('\t');
    }
    int s0 = sensorValues[0];
    int s1 = sensorValues[1];
    int s2 = sensorValues[2];
    int s3 = sensorValues[3];
    int s4 = sensorValues[4];
    int s5 = sensorValues[5];
    int s6 = sensorValues[6];
    int s7 = sensorValues[7];
    error = 4 * s0 + 3 * s1 + 2 * s2 + s3 - s4 - 2 * s5 - 3 * s6 - 4 * s7;

    P = error;
    I = I + error;
    D = error - prevError;
    Serial.print(error);

    prevError = error;
}

// grab item
void clawSequence(){
  Serial.println("claw sequence");
}

void turnRight90(){
  Serial.println("claw sequence");
}

void turnLeft90(){

}

