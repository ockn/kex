/*
2024-04-17
File that handles the DC-Motors for the lawnmower
contains
forward, backward, turnLeft, turnRight and stop

The function is part of the Bachelor thesis of Marko Gvero and Cecil Knudsen

*/



#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>



void forward(byte* motorPins) {
  digitalWrite(motorPins[0], HIGH);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], HIGH);
  digitalWrite(motorPins[3], LOW);
}

void backward(byte* motorPins) {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], HIGH);
}

void turnLeft(byte* motorPins) {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  digitalWrite(motorPins[2], HIGH);
  digitalWrite(motorPins[3], LOW);
}

void turnRight(byte* motorPins) {
  digitalWrite(motorPins[0], HIGH);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], HIGH);
}

void stop(byte* motorPins) {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], LOW);
}

#endif 
