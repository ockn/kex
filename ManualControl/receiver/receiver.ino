// Koden för att styra 2 motorer med en joystick
// RECEIVER / MOTTAGAREN

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 10); // CE, CSN

const byte address[6] = "00001";

int joyposVert;
int joyposHorz;

int enA = 9;
int in1 = 7;
int in2 = 6;

int enB = 3;
int in3 = 5;
int in4 = 4;

int MotorSpeed1 = 0; // Initialize motor speed variables
int MotorSpeed2 = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {


  if (radio.available()) {
    int data[2] = {0}; // Skapar data listan där den skickade datan ska lagras 

    radio.read(&data, sizeof(data)); // Läser av datan från sändaren

    joyposVert = data[0];
    joyposHorz = data[1];

    // Kontroll av motorer => enA och en B är enable: HIGH om motorn är på och LOW om motorn är avstängd
    // Framåt rörelse => in1 = HIGH och in2 = LOW för Motor A och in3 = HIGH och in4 = LOW för motor B
    // Bakåt rörelse => in1 = LOW och in2 = HIGH för Motor A och in3 = LOW och in4 = HIGH för motor B

  if (joyposVert < 460) {
    // Bakåtrörelse
    // Ställ motor A bakåt
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Ställ motor B bakåt
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Bestäm motorhastigheter
    MotorSpeed1 = map(joyposVert, 0, 460, 255, 0);
    MotorSpeed2 = map(joyposVert, 0, 460, 255, 0);
  } else if (joyposVert > 560) {
    // Framåtrörelse
    // Ställ motor A framåt
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Ställ motor B framåt
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Bestäm motorhastigheter
    MotorSpeed1 = map(joyposVert, 560, 1023, 0, 255);
    MotorSpeed2 = map(joyposVert, 560, 1023, 0, 255);
  } else {
    // Stanna motorenheterna när joysticken är i mitten
    MotorSpeed1 = 0;
    MotorSpeed2 = 0;
  }

  // Rörelse åt vänster och höger
  if (joyposHorz < 460) {
    // Rörelse mot vänster sida
    // Ändrningen beror på hur mycket joysticken är från mitten
    joyposHorz = map(joyposHorz, 0, 460, 255, 0);
    
    // Vänsterrörelse - minska vänster motorhastighet, öka höger motorhastighet
    MotorSpeed1 = MotorSpeed1 - joyposHorz;
    MotorSpeed2 = MotorSpeed2 + joyposHorz;
    
    // Överskrid inte intervallet 0-255 för motorhastigheter
    if (MotorSpeed1 < 0) MotorSpeed1 = 0;
    if (MotorSpeed2 > 255) MotorSpeed2 = 255;
  } else if (joyposHorz > 564) {
    // Rörelse mot höger sida
    // Ändrningen beror på hur mycket joysticken är från mitten
    joyposHorz = map(joyposHorz, 564, 1023, 0, 255);
    
    // Högerrörelse - öka vänster motorhastighet, minska höger motorhastighet
    MotorSpeed1 = MotorSpeed1 + joyposHorz;
    MotorSpeed2 = MotorSpeed2 - joyposHorz;
    
    // Överskrid inte intervallet 0-255 för motorhastigheter
    if (MotorSpeed1 > 255) MotorSpeed1 = 255;
    if (MotorSpeed2 < 0) MotorSpeed2 = 0;
  }

  // Sätt motorhastigheter
  analogWrite(enA, MotorSpeed1);
  analogWrite(enB, MotorSpeed2);
}
    Serial.print("Vertical position: ");
    Serial.print(joyposVert);
    Serial.print(" | Horizontal position: ");
    Serial.println(joyposHorz);
}