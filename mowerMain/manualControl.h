¨
/*
2024-04-19
File that handles the manual control for the lawnmower
contains

The function is part of the Bachelor thesis of Marko Gvero and Cecil Knudsen

*/


#ifndef MANUALCONTROL_H
#define MANUALCONTROL_H

#include <Arduino.h>
//void manualControl(byte* motorPins, int posVert, int posHori);

void manualControl(byte* motorPins, int joyposVert, int joyposHorz){
  int motorSpeed1;
  int motorSpeed2;
  if (joyposVert < 460) {
      // Bakåtrörelse
      // Ställ motor A bakåt
      digitalWrite(motorPins[0], LOW);
      digitalWrite(motorPins[1], HIGH);
      // Ställ motor B bakåt
      digitalWrite(motorPins[2], LOW);
      digitalWrite(motorPins[3], HIGH);
      // Bestäm motorhastigheter
      motorSpeed1 = map(joyposVert, 0, 460, 255, 0);
      motorSpeed2 = map(joyposVert, 0, 460, 255, 0);
    } else if (joyposVert > 560) {
      // Framåtrörelse
      // Ställ motor A framåt
      digitalWrite(motorPins[0], HIGH);
      digitalWrite(motorPins[1], LOW);
      // Ställ motor B framåt
      digitalWrite(motorPins[2], HIGH);
      digitalWrite(motorPins[3], LOW);
      // Bestäm motorhastigheter
      motorSpeed1 = map(joyposVert, 560, 1023, 0, 255);
      motorSpeed2 = map(joyposVert, 560, 1023, 0, 255);
    } else {
      // Stanna motorenheterna när joysticken är i mitten
      motorSpeed1 = 0;
      motorSpeed2 = 0;
    }

    // Rörelse åt vänster och höger
    if (joyposHorz < 460) {
      // Rörelse mot vänster sida
      // Ändrningen beror på hur mycket joysticken är från mitten
      joyposHorz = map(joyposHorz, 0, 460, 255, 0);
      
      // Vänsterrörelse - minska vänster motorhastighet, öka höger motorhastighet
      motorSpeed1 = motorSpeed1 - joyposHorz;
      motorSpeed2 = motorSpeed2 + joyposHorz;
      
      // Överskrid inte intervallet 0-255 för motorhastigheter
      if (motorSpeed1 < 0) motorSpeed1 = 0;
      if (motorSpeed2 > 255) motorSpeed2 = 255;
    } else if (joyposHorz > 564) {
      // Rörelse mot höger sida
      // Ändrningen beror på hur mycket joysticken är från mitten
      joyposHorz = map(joyposHorz, 564, 1023, 0, 255);
      
      // Högerrörelse - öka vänster motorhastighet, minska höger motorhastighet
      motorSpeed1 = motorSpeed1 + joyposHorz;
      motorSpeed2 = motorSpeed2 - joyposHorz;
      
      // Överskrid inte intervallet 0-255 för motorhastigheter
      if (motorSpeed1 > 255) motorSpeed1 = 255;
      if (motorSpeed2 < 0) motorSpeed2 = 0;

      analogWrite(motorPins[4], motorSpeed1);
      analogWrite(motorPins[5], motorSpeed2);
    }
  }
    
  #endif 
