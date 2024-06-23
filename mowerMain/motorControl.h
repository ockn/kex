/*
2024-04-17
File that handles the DC-Motors for the lawnmower

This file contains code for following directions:
forward, backward, turn left, turn right and stop

The function is part of the Bachelor thesis of Marko Gvero and Cecil Knudsen

*/


#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

void forward(byte* motorPins) {
  digitalWrite(motorPins[0], HIGH);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], HIGH);
  digitalWrite(motorPins[4], HIGH); //EnA
  digitalWrite(motorPins[5], HIGH); //EnB
}

void backward(byte* motorPins) {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  digitalWrite(motorPins[2], HIGH);
  digitalWrite(motorPins[3], LOW);
  digitalWrite(motorPins[4], HIGH); //EnA
  digitalWrite(motorPins[5], HIGH); //EnB
}

void turnLeft(byte* motorPins) {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], HIGH);
  digitalWrite(motorPins[4], HIGH); //EnA
  digitalWrite(motorPins[5], HIGH); //EnB
}

void turnRight(byte* motorPins) {
  digitalWrite(motorPins[0], HIGH);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], HIGH);
  digitalWrite(motorPins[3], LOW);
  digitalWrite(motorPins[4], HIGH); //EnA
  digitalWrite(motorPins[5], HIGH); //EnB
}

void stop(byte motorPins[]) {
  for (byte i = 0; i < 4; i++) {
    digitalWrite(motorPins[i], LOW);
  }
  analogWrite(motorPins[4], 0);
  analogWrite(motorPins[5], 0);
}

#endif

