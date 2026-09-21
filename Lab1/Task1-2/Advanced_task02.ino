const int red_pin = 9;
const int green_pin = 10;
const int blue_pin = 11;

const int button_pin = 2;
const int pot_pin = A0;

int green_state = 0;

void setup() {
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

  pinMode(button_pin, INPUT_PULLUP);

  Serial.begin(9600);

  Serial.println("RGB LED Controller");
  Serial.println("Enter 1 to turn GREEN on");
  Serial.println("Enter 0 to turn GREEN off");
}

void loop() {

  // =========================
  // 1. BLUE: Variable resistor
  // =========================

  int analog_value = analogRead(pot_pin);

  // analogRead(): 0~1023
  // analogWrite(): 0~255
  int blue_value = map(analog_value, 0, 1023, 0, 255);

  analogWrite(blue_pin, blue_value);


  // =========================
  // 2. RED: Button
  // =========================

  if (digitalRead(button_pin) == LOW) {
    // button pressed
    digitalWrite(red_pin, HIGH);
  }
  else {
    // button released
    digitalWrite(red_pin, LOW);
  }


  // =========================
  // 3. GREEN: Serial Monitor
  // =========================

  if (Serial.available() > 0) {

    char input = Serial.read();

    if (input == '1') {
      green_state = 1;
    }

    if (input == '0') {
      green_state = 0;
    }
  }


  if (green_state == 1) {
    digitalWrite(green_pin, HIGH);
  }
  else {
    digitalWrite(green_pin, LOW);
  }


  delay(10);
}
