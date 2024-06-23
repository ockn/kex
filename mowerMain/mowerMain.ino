/*
Oliver Cecil Knudsen, Marko Gvero, 2024-05-08, degree project for BSc in Mechatronics.

This is the main program for the control of a robotic lawnmower which was built as a  final project for
a BSc in mechatronics.


*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "manualControl.h"
#include "obstacleAhead.h"
#include "motorControl.h"

// Pins and definitions for the radio communication
const byte CE_PIN = 48;
const byte CSN_PIN = 49;

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00003";

// Pins for the wheel motors
const byte ENA = 2;
const byte IN1 = 23;
const byte IN2 = 22;
const byte ENB = 3;
const byte IN3 = 25;
const byte IN4 = 24;

const byte pinAmount = 6;
byte motorPins[pinAmount] = {IN1, IN2, IN3, IN4, ENA, ENB};

// Pins for the perimeter sensors (coils)
const byte prmSensorL = A0;
const byte prmSensorR = A1;


// Pins for LEDs

const byte joyLED = 40;
const byte manualLED = 41;

// Joystick

int joyy, joyx;
bool ovrTgl = 0; // Flag to indicate manual override mode
bool joyTgl = 0;

// Pins for the ultrasonic sensors
const byte trigPin1 = 11;
const byte echoPin1 = 12;
const byte trigPin2 = 9;
const byte echoPin2 = 10;

// Pins for the clipper motor
const byte CLIPPER_EN = 4; // Enable pin for clipper motor H-bridge
const byte CLIPPER_IN1 = 5; // Input 1 pin for clipper motor H-bridge
const byte CLIPPER_IN2 = 6; // Input 2 pin for clipper motor H-bridge


enum State {
  MOVING_FORWARD,
  BACKING_UP,
  TURNING,
  PAUSING
};

State currentState = MOVING_FORWARD;
unsigned long stateStartTime = 0;
int randomTurnTime = 0;
int randomLeftOrRight = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
  
  pinMode(prmSensorL, INPUT);
  pinMode(prmSensorR, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);

  
  for (byte i = 0; i < pinAmount; i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  // Initialize clipper motor pins
  pinMode(CLIPPER_EN, OUTPUT);
  pinMode(CLIPPER_IN1, OUTPUT);
  pinMode(CLIPPER_IN2, OUTPUT);
  
  stop(motorPins);
}

void loop() {

    //Start the clipper motor
    analogWrite(CLIPPER_EN, 50); 
    digitalWrite(CLIPPER_IN1, HIGH);
    digitalWrite(CLIPPER_IN2, LOW);
  
    int sensorValueA0 = analogRead(prmSensorL);
    int sensorValueA1 = analogRead(prmSensorR);

    // Print sensor values and current state for debugging
    Serial.print("Current state: ");
    Serial.print(currentState);
    Serial.print(", Sensor L: ");
    Serial.print(sensorValueA0);
    Serial.print(", Sensor R: ");


    // Check for manual control input
    if (radio.available()) {
        Serial.println("We got connection");
        int data[4] = {0}; // Array to store received data from the controller
        radio.read(&data, sizeof(data));
        joyx = data[0];
        joyy = data[1];
        joyTgl = data[2];
        ovrTgl = data[3];

        if (ovrTgl) {
            Serial.println("Manual override mode is ON!!");
            Serial.print("joyx: ");
            Serial.print(joyx);
            Serial.print(", joyy: ");
            Serial.print(joyy);
            Serial.print(", Joy Toggle: ");
            Serial.print(joyTgl);
            Serial.print(", Override Toggle: ");
            Serial.println(ovrTgl);
            digitalWrite(manualLED, HIGH);

            // Execute manual control based on joystick input
            manualControl(motorPins, joyx, joyy);
            return;  // Exit the loop to avoid running autonomous code
        } else {
            digitalWrite(manualLED, LOW);
            //stop(motorPins);  // Ensure motors stop when not in manual override mode
        }
    }

    // Autonomous mode logic
    switch (currentState) {
        case MOVING_FORWARD:
            forward(motorPins);
            if (sensorValueA0 > 200 || sensorValueA1 > 200 || obstacleAhead(trigPin1, echoPin1, trigPin2, echoPin2) == true) {
                stop(motorPins);
                stateStartTime = millis();
                currentState = BACKING_UP;
                Serial.println("Transition to BACKING_UP");
            }
            break;

        case BACKING_UP:
            if (millis() - stateStartTime < 2000) {
                backward(motorPins);
            } else {
                stop(motorPins);
                currentState = PAUSING;
                stateStartTime = millis();
                Serial.println("Transition to PAUSING");
            }
            break;

        case PAUSING:
            if (millis() - stateStartTime >= 500) {
                randomTurnTime = random(500, 3500);
                randomLeftOrRight = random(2);
                currentState = TURNING;
                stateStartTime = millis();
                Serial.print("Transition to TURNING, Turn Time: ");
                Serial.print(randomTurnTime);
                Serial.print(", Direction: ");
                Serial.println(randomLeftOrRight == 0 ? "Left" : "Right");
            }
            break;

        case TURNING:
            if (randomLeftOrRight == 0) {
                turnLeft(motorPins);
            } else {
                turnRight(motorPins);
            }
            if (millis() - stateStartTime >= randomTurnTime) {
                stop(motorPins);
                currentState = MOVING_FORWARD;
                Serial.println("Transition to MOVING_FORWARD");
            }
            break;
    }
}


