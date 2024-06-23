/*
Oliver Cecil Knudsen, Marko Gvero, 2024-05-08.

Function that handles the obstacle detection using HCSR04 distancs sensors.
Part of the degree project in mechatronics
*/

// Function to detect obstacles using two HC-SR04 ultrasonic sensors
bool obstacleAhead(int trigPin1, int echoPin1, int trigPin2, int echoPin2) {
    const float threshold = 10.0; // Threshold distance in centimeters

    // Functionality for the first sensor
    // Send a pulse to trigger the first sensor
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    // Measure the duration of the pulse on the echo pin of the first sensor
    float duration1 = pulseIn(echoPin1, HIGH);
    // Calculate the distance from the first sensor
    float distance1 = duration1 * 0.0343 / 2;
    
    // Functionality for the second sensor
    // Send a pulse to trigger the second sensor
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    // Measure the duration of the pulse on the echo pin of the second sensor
    float duration2 = pulseIn(echoPin2, HIGH);
    // Calculate the distance from the second sensor
    float distance2 = duration2 * 0.0343 / 2;

    // Check if either of the distances is less than the threshold
    bool tooClose = distance1 < threshold || distance2 < threshold;

    return tooClose; // Return true if obstacle detected by either sensor, false otherwise
}
