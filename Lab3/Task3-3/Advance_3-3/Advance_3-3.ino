#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX)
// Arduino D10 receives from HC-05 TX
// Arduino D9 sends to HC-05 RX
SoftwareSerial bluetooth(10, 9);

// External LED
const int ledPin = 11;

void setup()
{
    // External LED
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // USB Serial for debugging
    Serial.begin(9600);

    // HC-05 communication
    bluetooth.begin(9600);

    Serial.println("Bluetooth LED Control Ready");
}

void loop()
{
    // Check if HC-05 received data
    if (bluetooth.available() > 0)
    {
        String command = bluetooth.readStringUntil('\n');

        command.trim();

        // Show received command in Serial Monitor
        Serial.print("Received: ");
        Serial.println(command);

        if (command == "ON")
        {
            digitalWrite(ledPin, HIGH);

            bluetooth.println("LED ON");

            Serial.println("External LED ON");
        }
        else if (command == "OFF")
        {
            digitalWrite(ledPin, LOW);

            bluetooth.println("LED OFF");

            Serial.println("External LED OFF");
        }
        else
        {
            bluetooth.println("Unknown command");
        }
    }
}