#include <Servo.h>

Servo panServo;
Servo tiltServo;

#define panServoPin 5
#define tiltServoPin 6

#define panServoBias -8
#define tiltServoBias -7

#define laserPin 2

void shootAction(int panAngle, int tiltAngle){ 
  panServo.write(panAngle + panServoBias);
  tiltServo.write(tiltAngle + tiltServoBias);

  digitalWrite(laserPin, LOW);
  delay(1000);
  digitalWrite(laserPin, HIGH);
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  
  panServo.attach(panServoPin);
  tiltServo.attach(tiltServoPin);
  
  // Initialize servos to a default position
  panServo.write(90 + panServoBias);
  tiltServo.write(90 + tiltServoBias);

  pinMode(laserPin, OUTPUT);
}

void loop() {
  delay(200);
  if (Serial.available() > 0) {
    // Data comes in form of string "theta1,theta2\n"
    String data = Serial.readStringUntil('\n'); // Read until newline character
    int commaIndex = data.indexOf(',');
    
    if (commaIndex > 0) {
      int pan = data.substring(0, commaIndex).toInt(); // Extract pan angle
      int tilt = data.substring(commaIndex + 1).toInt(); // Extract tilt angle

      // Shoot with desired angles
      shootAction(pan, tilt);
    }
  }
}
