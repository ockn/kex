/*
2024-04-18
Function for the perimeter wire sensors.
Returns true if the sensors picks up the signal from the perimeter wire, returns false
otherwise.

The function is part of the Bachelor thesis of Marko Gvero and Cecil Knudsen

*/

int sensor;
bool perimeterSensor(int sensorPin){

  sensor = analogRead(sensorPin);
  const byte threshold = 10; // threshold value should be between 0 and 1023
  if (sensor > threshold) { 
    return 1;
  } else {
    return 0;
  }
}