const int pot_pin = A0;
const int led_pin = 11;

void setup() {
  pinMode(led_pin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Read potentiometer
  int analog_value = analogRead(pot_pin);

  // analogRead: 0~1023
  // analogWrite: 0~255
  int led_value = analog_value / 4;

  // Control LED brightness
  analogWrite(led_pin, led_value);

  // Print analog value
  Serial.print("Data is ");
  Serial.println(analog_value);

  delay(1000);
}
