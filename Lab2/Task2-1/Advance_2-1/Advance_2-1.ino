const int PIN_1A = 7;
const int PIN_2A = 8;
const int ENABLE_PIN = 9;

const int POT_PIN = A0;

void setup() {
    pinMode(PIN_1A, OUTPUT);
    pinMode(PIN_2A, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);

    Serial.begin(9600);
}

void loop() {

    int potValue = analogRead(POT_PIN);

    Serial.println(potValue);

    if (potValue < 500) {

        // Counterclockwise
        digitalWrite(PIN_1A, LOW);
        digitalWrite(PIN_2A, HIGH);

        int speedValue = map(
            potValue,
            500, 0,
            0, 255
        );

        analogWrite(ENABLE_PIN, speedValue);
    }

    else if (potValue > 524) {

        // Clockwise
        digitalWrite(PIN_1A, HIGH);
        digitalWrite(PIN_2A, LOW);

        int speedValue = map(
            potValue,
            524, 1023,
            0, 255
        );

        analogWrite(ENABLE_PIN, speedValue);
    }

    else {

        // Stop
        analogWrite(ENABLE_PIN, 0);
    }
}