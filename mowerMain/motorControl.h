/*
2024-04-17
File that handles the DC-Motors for the lawnmower
contains
forward, backward, turnLeft, turnRight and stop

The function is part of the Bachelor thesis of Marko Gvero and Cecil Knudsen

*/



#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

void stop(byte* motorPins) {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], LOW);
    //Logic Voltage
  digitalWrite(motorPins[4], LOW); //EnA
  digitalWrite(motorPins[5], LOW);//EnB
}

void forward(byte* motorPins) {
  digitalWrite(motorPins[0], HIGH);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], HIGH);
  digitalWrite(motorPins[3], LOW);

  //Logic Voltage
  digitalWrite(motorPins[4], HIGH); //EnA
  digitalWrite(motorPins[5], HIGH);//EnB
}

void backward(byte* motorPins) {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], HIGH);
    //Logic Voltage
  digitalWrite(motorPins[4], HIGH); //EnA
  digitalWrite(motorPins[5], HIGH);//EnB
}

void turnLeft(byte* motorPins, int turnTime) {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  digitalWrite(motorPins[2], HIGH);
  digitalWrite(motorPins[3], LOW);
    //Logic Voltage
  digitalWrite(motorPins[4], HIGH); //EnA
  digitalWrite(motorPins[5], HIGH);//EnB
  delay(turnTime);
  stop(motorPins);
}

void turnRight(byte* motorPins, int turnTime) {
  digitalWrite(motorPins[0], HIGH);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], HIGH);
    //Logic Voltage
  digitalWrite(motorPins[4], HIGH); //EnA
  digitalWrite(motorPins[5], HIGH);//EnB
  delay(turnTime);
  stop(motorPins);
}



#endif 
