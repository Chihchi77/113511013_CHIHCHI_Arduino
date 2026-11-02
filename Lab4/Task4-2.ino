
#include <Servo.h>

// ============================================
// Ball and Beam PID + Sensor Escape
// ============================================

// ---------- Pins ----------
const byte TRIG_PIN = 7;
const byte ECHO_PIN = 8;
const byte SERVO_PIN = 9;

Servo beamServo;

// ============================================
// Track and Servo
// ============================================

const float TRACK_LENGTH_CM = 30.0f;
const float TARGET_CM = TRACK_LENGTH_CM / 2.0f;

const int LEVEL_ANGLE = 119;

// Increasing servo angle lowers sensor side,
// so reverse normal PID direction.
const int SERVO_DIRECTION = 1;

const float MAX_TILT_DEG = 12.0f;

// ============================================
// Escape Function Settings
// ============================================

// Trigger escape when ball is within 12 cm.
const float ESCAPE_DISTANCE_CM = 10.0f;

// 119 - 14 = 105
// This should raise the sensor side.
const int ESCAPE_ANGLE = 157;

// On sensor failure, escape for at most 400 ms.
// Then level the beam for safety.
const unsigned long ESCAPE_TIMEOUT_MS = 800;

// ============================================
// PID Parameters
// ============================================

float Kp = 1.4f;
float Ki = 0.0f;
float Kd = 1.0f;

// ============================================
// Sensor Settings
// ============================================

const unsigned long SAMPLE_PERIOD_MS = 60;
const unsigned long ECHO_TIMEOUT_US = 12000;

const float MIN_VALID_CM = 2.0f;
const float MAX_VALID_CM = TRACK_LENGTH_CM - 2.0f;

const float FILTER_ALPHA = 0.35f;
const float INTEGRAL_LIMIT = 70.0f;

// ============================================
// Controller State
// ============================================

unsigned long lastSampleMs = 0;

// Tracks when a continuous sensor failure began.
unsigned long sensorLostStartMs = 0;
bool sensorLost = false;

bool tracking = false;

float positionCm = TARGET_CM;
float previousPositionCm = TARGET_CM;
float accumulatedError = 0.0f;

// ============================================
// Ultrasonic Sensor
// ============================================

float measureDistanceCm() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  unsigned long echoUs =
      pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);

  if (echoUs == 0) {
    return -1.0f;
  }

  float distanceCm = echoUs * 0.0343f / 2.0f;

  if (distanceCm < MIN_VALID_CM ||
      distanceCm > MAX_VALID_CM) {
    return -1.0f;
  }

  return distanceCm;
}

// ============================================
// Reset PID
// ============================================

void resetPID() {

  tracking = false;
  accumulatedError = 0.0f;
}

// ============================================
// Level Track
// ============================================

void levelAndReset() {

  beamServo.write(LEVEL_ANGLE);
  resetPID();
}

// ============================================
// NEW: Escape From Sensor
// ============================================

void escapeFromSensor() {

  // Raise the sensor side.
  // Ball should roll away from sensor.
  beamServo.write(ESCAPE_ANGLE);

  // Prevent old PID error from interfering.
  resetPID();
}

// ============================================
// Setup
// ============================================

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  beamServo.attach(SERVO_PIN);

  levelAndReset();

  delay(1000);

  lastSampleMs = millis();

  Serial.println("Ball and Beam PID Started");
}

// ============================================
// Main Loop
// ============================================

void loop() {

  unsigned long now = millis();

  if (now - lastSampleMs < SAMPLE_PERIOD_MS) {
    return;
  }

  float dt = (now - lastSampleMs) / 1000.0f;
  lastSampleMs = now;

  if (dt <= 0.0f) {
    return;
  }

  // ==========================================
  // 1. Read Distance
  // ==========================================

  float rawCm = measureDistanceCm();

  // ==========================================
  // 2. Sensor Cannot Detect Ball
  // ==========================================

  if (rawCm < 0.0f) {

    // Start a new continuous sensor-loss event.
    if (!sensorLost) {
      sensorLost = true;
      sensorLostStartMs = now;
    }

    unsigned long lostDuration =
        now - sensorLostStartMs;

    if (lostDuration < ESCAPE_TIMEOUT_MS) {

      escapeFromSensor();

      Serial.println(
        "SENSOR LOST -> ESCAPE 105"
      );

    } else {

      // Unknown ball position:
      // stop the forced tilt after timeout.
      levelAndReset();

      Serial.println(
        "SENSOR LOST TOO LONG -> LEVEL 119"
      );
    }

    return;
  }

  // ==========================================
  // 3. Valid Sensor Reading
  // ==========================================

  // A valid reading ends the sensor-loss event.
  sensorLost = false;

  // ==========================================
  // 4. Ball Too Close to Sensor
  // ==========================================

  if (rawCm <= ESCAPE_DISTANCE_CM) {

    escapeFromSensor();

    Serial.print("TOO CLOSE | Distance:");
    Serial.print(rawCm, 1);
    Serial.println(" | Servo:105");

    return;
  }

  // ==========================================
  // 5. Normal PID
  // ==========================================

  if (!tracking) {

    positionCm = rawCm;
    previousPositionCm = rawCm;

    accumulatedError = 0.0f;
    tracking = true;

  } else {

    positionCm =
        FILTER_ALPHA * rawCm +
        (1.0f - FILTER_ALPHA) * positionCm;
  }

  // ------------------------------------------
  // Error
  // ------------------------------------------

  float errorCm = TARGET_CM - positionCm;

  // ------------------------------------------
  // Velocity
  // ------------------------------------------

  float velocityCmPerSec =
      (positionCm - previousPositionCm) / dt;

  previousPositionCm = positionCm;

  // ------------------------------------------
  // Integral
  // ------------------------------------------

  accumulatedError += errorCm * dt;

  accumulatedError = constrain(
    accumulatedError,
    -INTEGRAL_LIMIT,
    INTEGRAL_LIMIT
  );

  // ------------------------------------------
  // PID Terms
  // ------------------------------------------

  float Pvalue = Kp * errorCm;

  float Ivalue = Ki * accumulatedError;

  float Dvalue = -Kd * velocityCmPerSec;

  float control =
      Pvalue + Ivalue + Dvalue;

  // ------------------------------------------
  // Limit Tilt
  // ------------------------------------------

  control = constrain(
    control,
    -MAX_TILT_DEG,
    MAX_TILT_DEG
  );

  // ------------------------------------------
  // Servo Angle
  // ------------------------------------------

  int servoAngle = (int)roundf(
    LEVEL_ANGLE +
    SERVO_DIRECTION * control
  );

  servoAngle = constrain(
    servoAngle,
    LEVEL_ANGLE - (int)MAX_TILT_DEG,
    LEVEL_ANGLE + (int)MAX_TILT_DEG
  );

  beamServo.write(servoAngle);

  // ==========================================
  // 6. Serial Debug
  // ==========================================

  Serial.print("PID | Position:");
  Serial.print(positionCm, 1);

  Serial.print(" Target:");
  Serial.print(TARGET_CM, 1);

  Serial.print(" Error:");
  Serial.print(errorCm, 1);

  Serial.print(" Velocity:");
  Serial.print(velocityCmPerSec, 2);

  Serial.print(" Servo:");
  Serial.println(servoAngle);
}
