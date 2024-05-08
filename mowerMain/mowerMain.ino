/*
Oliver Cecil Knudsen, Marko Gvero, 2024-05-08, degree project for BSc in Mechatronics.

This is the main program for the control of a robotic lawnmower which was built as a  final project for
a BSc in mechatronics.


*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "motorControl.h"
#include "perimeterSensor.h"
#include "manualControl.h"
#include "obstacleAhead.h"

//Radio pins and radio stuff
const byte CE_PIN  = 48;
const byte CSN_PIN = 49;

RF24 radio(CE_PIN, CSN_PIN); // CE, CSN
const byte address[6] = "00001";

//Pins for the driving motors

const byte ENA = 2;
const byte IN1 = 23;
const byte IN2 =22;

const byte ENB = 3;
const byte IN3 = 25;
const byte IN4 = 24;

const byte pinAmount = 6;
byte motorPins[pinAmount] = {IN1, IN2, IN3, IN4, ENA, ENB};


// Pins for the perimeter sensors

const byte prmSensorL = A0; 
const byte prmSensorR = A1;

//pins for range finders

const byte TRIGGER_RIGHT=10;
const byte ECHO_RIGHT=11;
const byte TRIGGER_LEFT=12;
const byte ECHO_LEFT = 13;

RangeFinder rangeFinderLeft = {TRIGGER_LEFT, ECHO_LEFT};
RangeFinder rangeFinderRight = {TRIGGER_RIGHT, ECHO_RIGHT};

// pins for eventual LEDs

const byte joyLED = 40;
const byte manualLED = 41;


//pins for the clipper

const byte CLPENA = 4;
const byte CLPIN1 = 31;
const byte CLPIN2 = 30;

int joyy, joyx;
bool ovrTgl = 0; // Flag to indicate manual override mode
bool joyTgl = 0;
void setup() {
  Serial.begin(9600);
  //LEDs
  pinMode(joyLED, OUTPUT);
  pinMode(manualLED, OUTPUT);

  //H-bridge motorPins
  for (int i = 0; i < sizeof(motorPins) / sizeof(motorPins[0]); i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  //clipper pins
  pinMode(CLPENA, OUTPUT);
  pinMode(CLPIN1, OUTPUT);
  pinMode(CLPIN2, OUTPUT);

  // perimeter sensors

  pinMode(prmSensorL, INPUT);
  pinMode(prmSensorR, INPUT);
  // range finders 

  pinMode(rangeFinderRight.trigPin,OUTPUT);
  pinMode(rangeFinderRight.echoPin,INPUT);
  pinMode(rangeFinderLeft.trigPin,OUTPUT);
  pinMode(rangeFinderLeft.echoPin,INPUT);



  //radio stuff
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  byte joyData[8]; // Array to store received data
  digitalWrite(joyLED, joyTgl);
  // Check if there is data available to read
  if (radio.available()) {
    // Read the incoming message into the joyData array
    radio.read(&joyData, sizeof(joyData));

    // Unpack the received data
    joyx = joyData[0] | (joyData[1] << 8);
    joyy = joyData[2] | (joyData[3] << 8);
    joyTgl = joyData[4];
    ovrTgl = joyData[5];
    delay(100);
    Serial.print("joy x: ");
    Serial.print(joyx);
    Serial.print(", joy y: ");
    Serial.println(joyy);

  }else{
    //ovrTgl = 0;
  
  }
    if (!ovrTgl) {
      digitalWrite(manualLED, ovrTgl);
      // Autonomous mode behavior
      // Check perimeter sensors
      

      // Perform autonomous behavior if perimeter detected
      if (perimeterSensor(prmSensorL) || perimeterSensor(prmSensorR) || obstacleAhead(rangeFinderLeft) || obstacleAhead(rangeFinderRight)){
        // Stop motors
        stop(motorPins);
        
       
        backward(motorPins); 
        delay(3000); 
        stop(motorPins);

        // Randomized direction change
        int randomTurnTime = random(10, 91)*100; // generate a random time between 1 and 9 seconds
        if (random(2) == 0) {
          turnLeft(motorPins, randomTurnTime);
        } else {
          turnRight(motorPins, randomTurnTime);
        }
        
        // Resume forward movement
       
        
      } else {
        forward(motorPins);

      }
      
    } else {
      // Manual override mode behavior
      // Control motors based on joystick input
      
      digitalWrite(manualLED, ovrTgl);
      manualControl(motorPins, joyx, joyy);
    }
  }

