/*
Oliver Cecil Knudsen, Marko Gvero, 2024-05-08.

Program that handles the remote control for a robotic lawnmower.
Part of the degree project for a BSc in mechatronis spring 2024.


*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN pins UNO
//RF24 radio(48, 49); // CE, CSN pins MEGA
const byte address[6] = "00001";

// Joystick Pins
const byte JOYXPIN = A0;
const byte JOYYPIN = A1;
const byte JOYBTNPIN = 4;
const byte OVRBTNPIN = 2;

const byte OVRLED = 5;
const byte JOYLED = 6;

bool ovrTgl = 0;
bool joyTgl = 0;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  pinMode(JOYBTNPIN, INPUT_PULLUP);
  pinMode(OVRBTNPIN, INPUT_PULLUP);
  pinMode(OVRLED, OUTPUT);
  pinMode(JOYLED, OUTPUT);
}

void loop() {
  int joyx = analogRead(JOYXPIN);
  int joyy = analogRead(JOYYPIN);
  if (!digitalRead(JOYBTNPIN)){ //Inverted due to pullup resistor.
    
    joyTgl = !joyTgl;
    delay(80);
  }
    if (!digitalRead(OVRBTNPIN)){
    
    ovrTgl = !ovrTgl;
    delay(80);
  }
  
  digitalWrite(OVRLED, ovrTgl);
  digitalWrite(JOYLED, joyTgl);

  // Pack the joystick data into a byte array
  byte joyData[8];
  joyData[0] = joyx & 0xFF;          // Lower byte of joyx
  joyData[1] = (joyx >> 8) & 0xFF;   // Upper byte of joyx
  joyData[2] = joyy & 0xFF;          // Lower byte of joyy
  joyData[3] = (joyy >> 8) & 0xFF;   // Upper byte of joyy
  joyData[4] = joyTgl ? 1 : 0;    // Convert bool to byte
  joyData[5] = ovrTgl ? 1 : 0;


  
  // Send the joystick data
  
  radio.write(&joyData, sizeof(joyData));
  delay(100);
}
/*
  // Print joystick data for debugging
  Serial.print("joyx: ");
  Serial.print(joyx);
  Serial.print(", joyy: ");
  Serial.print(joyy);
  Serial.print(", Toggle: ");
  Serial.print(ovrTgl);
  Serial.print(", joystick toggle: ");
  Serial.println(joyTgl);

  delay(1000); // Adjust delay according to your application
}
*/