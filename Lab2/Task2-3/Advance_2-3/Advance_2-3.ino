const int buttonPinA = 2;
const int ledPinA = 11;

const int buttonPinB = 4;
const int ledPinB = 10;

volatile bool ledStateA = false;

bool ledStateB = false;
int previousButtonB = HIGH;

void setup() {
    pinMode(ledPinA, OUTPUT);
    pinMode(buttonPinA, INPUT_PULLUP);

    pinMode(ledPinB, OUTPUT);
    pinMode(buttonPinB, INPUT_PULLUP);

    attachInterrupt(
        digitalPinToInterrupt(buttonPinA),
        buttonISR,
        FALLING
    );
}

void buttonISR() {
    ledStateA = !ledStateA;
    digitalWrite(ledPinA, ledStateA);
}

void loop() {

    // Poll Button B
    int currentButtonB = digitalRead(buttonPinB);

    // Detect HIGH -> LOW transition
    if (previousButtonB == HIGH &&
        currentButtonB == LOW) {

        ledStateB = !ledStateB;

        digitalWrite(
            ledPinB,
            ledStateB
        );
    }

    previousButtonB = currentButtonB;

    // Simulate a busy/blocking system
    delay(2000);
}