/*
Oliver Cecil Knudsen, Marko Gvero, 2024-05-08.

Function that handles the obstacle detection using HCSR04 distancs sensors.
Part of the degree project in mechatronics
*/
struct RangeFinder {
  int trigPin;
  int echoPin;
};

bool obstacleAhead(RangeFinder sensor) {

  float threshold = 10.0; //threshold distance in CMs.
  // Send a pulse to trigger the sensor
  digitalWrite(sensor.trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor.trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor.trigPin, LOW);

  // Measure the duration of the pulse on the echo pin
  float duration = pulseIn(sensor.echoPin, HIGH);

  // Calculate the distance based on the speed of sound (343 m/s)
  float distance = duration * 0.0343 / 2;
  bool tooClose = threshold > distance;
  return tooClose; // Return the distance measured
}