const int ledPin = 11;

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == "ON") {
            digitalWrite(ledPin, HIGH);
            Serial.println("LED ON");
        }
        else if (command == "OFF") {
            digitalWrite(ledPin, LOW);
            Serial.println("LED OFF");
        }
    }
}