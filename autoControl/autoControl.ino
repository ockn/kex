/*
Part of the Bachelor project for Marko Gvero and Cecil Knudsen
Code for the automatic control of a lawnmower, depends motorContrlo.h and 
perimeterSensor.h

last change: 2024-04-18

*/

#include "motorControl.h"
#include "perimeterSensor.h"
// Pins for the DC-Motors 
const byte enA = 9;
const byte in1 = 7;
const byte in2 = 6;

const byte enB = 3;
const byte in3 = 5;
const byte in4 = 4;

const byte pinAmount = 4;
byte motorPins[pinAmount] = {in1, in2, in3, in4};
// Pins for the perimeter sensors

const byte prmSensorA = 10; //Placeholders
const byte prmSensorB = 11;

void setup() {
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(motorPins[0], OUTPUT);
pinMode(motorPins[1], OUTPUT);
pinMode(motorPins[2], OUTPUT);
pinMode(motorPins[3], OUTPUT);

pinMode(prmSensorA, INPUT);
pinMode(prmSensorB, INPUT);

}
// TODO include this in a "Main file" that controls what control system
//is to be used
void loop() {
  if (perimeterSensor(prmSensorA) || perimeterSensor(prmSensorB)){
    //TODO KOD FÖR RANDOM RÖRELSE
    stop(motorPins);
    backward(motorPins);
    delay(5000);
    turnLeft(motorPins);
    delay(3000);


  } else{
    forward(motorPins);

  }
  

}
