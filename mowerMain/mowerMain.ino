#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "motorControl.h"
#include "perimeterSensor.h"
#include "manualControl.h"

//Radio stuff
CE_pin  = 8;
CSN_pin = 10

RF24 radio(CE_pin, CSN_pin); // CE, CSN

const byte address[6] = "00001";

int joyposVert;
int joyposHorz;

const byte enA = 9;
const byte in1 = 7;
const byte in2 = 6;

const byte enB = 3;
const byte in3 = 5;
const byte in4 = 4;

const byte pinAmount = 6;
byte motorPins[pinAmount] = {in1, in2, in3, in4, enA, enB};


// Pins for the perimeter sensors

const byte prmSensorA = A1; 
const byte prmSensorB = A2;

bool manualOverrideMode = false; // Flag to indicate manual override mode

void setup() {


//H-bridge motorPins
pinMode(motorPins[0], OUTPUT);
pinMode(motorPins[1], OUTPUT);
pinMode(motorPins[2], OUTPUT);
pinMode(motorPins[3], OUTPUT);

//H Bridge enable pins
pinMode(motorPins[4], OUTPUT); //enA
pinMode(motorPins[5], OUTPUT); //enB


pinMode(prmSensorA, INPUT);
pinMode(prmSensorB, INPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    int data[3] = {0}; // Data array to store joystick and button states

    radio.read(&data, sizeof(data)); // Read data from the transmitter

    joyposVert = data[0];
    joyposHorz = data[1];
    manualOverrideMode = data[2];

    if (!manualOverrideMode) {
      // Autonomous mode behavior
      // Check perimeter sensors
      

      // Perform autonomous behavior if perimeter detected
      if (perimeterSensor(prmSensorA) || perimeterSensor(prmSensorB)) {
        // Stop motors
        stop(motorPins);
        
       
        backward(motorPins); 
        delay(3000); 
        stop(motorPins);

        // Randomized direction change
        int randomTurnTime = random(10, 91)*100; // generate a random time between 1 and 9 seconds
        if (random(2) == 0) {
          turnLeft(motorPins, turnTime);
        } else {
          turnRight(motorPins, turnTime);
        }
        
        // Resume forward movement
        forward(motorPins);
        
      } else {
        forward(motorPins);
      }
    } else {
      // Manual override mode behavior
      // Control motors based on joystick input
      manualControl(motorPins, joyposVert, joyposHorz);
    }
  }
}
