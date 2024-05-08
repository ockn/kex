
/*
2024-05-03
File that handles the manual control for the lawnmower
contains

The function is part of the Bachelor thesis of Marko Gvero and Cecil Knudsen

*/


#ifndef MANUALCONTROL_H
#define MANUALCONTROL_H

#include <Arduino.h>


void manualControl(byte* motorPins, int joyx, int joyy){

const short joyMax = 1023;
const short joyMin = 0;
const short maxSpeed = 255;
const short minSpeed = -255;

int mappedX = map(joyx, joyMin, joyMax, maxSpeed, minSpeed);
int mappedY = map(joyy, joyMin, joyMax, maxSpeed, minSpeed);

int leftMotor = mappedX + mappedY;
int rightMotor = mappedY - mappedX;

leftMotor = constrain(leftMotor, minSpeed,maxSpeed);
rightMotor = constrain(rightMotor, minSpeed, maxSpeed);


digitalWrite(motorPins[0], leftMotor >= 0 ? HIGH : LOW);
digitalWrite(motorPins[1], leftMotor < 0 ? HIGH : LOW);
digitalWrite(motorPins[3], rightMotor >= 0 ? HIGH : LOW); //due to wiring mistake 
digitalWrite(motorPins[2], rightMotor < 0 ? HIGH : LOW); // these two pins are switched

analogWrite(motorPins[4], abs(leftMotor));
analogWrite(motorPins[5], abs(rightMotor));



}
    
  #endif 
