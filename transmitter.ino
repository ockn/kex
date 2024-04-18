#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 10); // CE, CSN

const byte address[6] = "00001";

int joyVert = A0; // Den vertikala delen av joysticken
int joyHorz = A1; // Den horisontella delen av joysticken

int joyposVert;
int joyposHorz;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  joyposVert = analogRead(joyVert);
  joyposHorz = analogRead(joyHorz);

  int data[2] = {joyposVert, joyposHorz};
  radio.write(&data, sizeof(data));

  delay(100); // Liten fördröjning för att undvika att överbelasta mottagaren
}