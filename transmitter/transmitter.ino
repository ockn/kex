/*
Oliver Cecil Knudsen, Marko Gvero, 2024-05-08.

Program that handles the remote control for a robotic lawnmower.
Part of the degree project for a BSc in mechatronis spring 2024.


*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN pins
const byte address[6] = "00003";

// Joystick Pins
const int JOYXPIN = A0;
const int JOYYPIN = A1;
const int JOYBTNPIN = 4;
const int OVRBTNPIN = 2;

int OVRLED = 5;
int JOYLED = 6;

bool ovrTgl = false; //Toggle for the manual override mode
bool joyTgl = false; //Toggle for joystick button

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
  
  if (!digitalRead(JOYBTNPIN)) { // Joystick button pressed
    joyTgl = !joyTgl; // Toggle joystick button
    delay(10); // Debounce delay
  }

  if (!digitalRead(OVRBTNPIN)) { // Override button pressed
    ovrTgl = !ovrTgl; // Toggle override mode
    delay(10); // Debounce delay
  }
  digitalWrite(OVRLED, ovrTgl);
  digitalWrite(JOYLED, joyTgl);
  // Prepare data array
  int data[4] = {joyx, joyy, joyTgl ? 1 : 0, ovrTgl ? 1 : 0};

  // Send data
  radio.write(data, sizeof(data));
  delay(50); // Adjust delay according to your application

  Serial.print("joyx: ");
  Serial.print(joyx);
  Serial.print(" | joyy: ");
  Serial.print(joyy);
  Serial.print(" | joyTgl: ");
  Serial.print(joyTgl);
  Serial.print(" | manualOverride: ");
  Serial.println(ovrTgl);
}


*/
