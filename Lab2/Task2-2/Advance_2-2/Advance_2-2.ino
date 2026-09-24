#include <Servo.h>

Servo myservo;

const int trigPin = 7;
const int echoPin = 6;
const int servoPin = 9;

int currentAngle = 90;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.attach(servoPin);
  myservo.write(currentAngle);

  Serial.begin(9600);
}

void loop() {

  // 1. Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // 2. Measure echo duration
  long duration = pulseIn(echoPin, HIGH, 30000);

  // pulseIn returns 0 if timeout
  if (duration > 0) {

    // 3. Convert time to distance
    float distance = duration * 0.0343 / 2.0;

    // 4. Only use reasonable distance
    if (distance >= 5 && distance <= 50) {

      currentAngle = map((int)distance, 5, 50, 0, 180);

      myservo.write(currentAngle);
    }

    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.print(" cm, Angle = ");
    Serial.println(currentAngle);
  }

  delay(100);
}