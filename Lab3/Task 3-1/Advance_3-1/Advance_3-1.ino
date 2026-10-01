#include <TimerOne.h>

const int buttonPinA = 2;
const int ledPinA = 11;

const int buttonPinB = 4;
const int ledPinB = 10;

void setup() {
    pinMode(buttonPinA, INPUT_PULLUP);
    pinMode(ledPinA, OUTPUT);

    pinMode(buttonPinB, INPUT_PULLUP);
    pinMode(ledPinB, OUTPUT);

    // Timer interrupt every 50 ms
    Timer1.initialize(50000);

    // Run timerISR every time Timer1 expires
    Timer1.attachInterrupt(timerISR);
}

void timerISR() {
    int buttonStateA = digitalRead(buttonPinA);

    if (buttonStateA == LOW) {
        digitalWrite(ledPinA, HIGH);
    } else {
        digitalWrite(ledPinA, LOW);
    }
}

void loop() {
    int buttonStateB = digitalRead(buttonPinB);

    if (buttonStateB == LOW) {
        digitalWrite(ledPinB, HIGH);
    } else {
        digitalWrite(ledPinB, LOW);
    }

    delay(1000);
}