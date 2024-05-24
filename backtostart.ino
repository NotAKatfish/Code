// di
// Constants for sensor and motor pins
const int LEFT_SENSOR_PIN = 2;
const int RIGHT_SENSOR_PIN = 3;
const int REVERSE_MOTOR_PIN = 4;
const int TURN_MOTOR_PIN = 5;

// Function prototypes
void reverseUntilBlack();
void reverseTurnUntilWhite();
void keepTurningUntilBlack();
void reversePastRows(int rows);

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging

  // Setup sensor and motor pins
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);
  pinMode(REVERSE_MOTOR_PIN, OUTPUT);
  pinMode(TURN_MOTOR_PIN, OUTPUT);
}

void loop() {
  int currentRow = 3; // Example starting row

  reverseUntilBlack();
  reverseTurnUntilWhite();
  keepTurningUntilBlack();
  reversePastRows(currentRow);

  // Stop the loop for this example
  while (true);
}

void reverseUntilBlack() {
  Serial.println("Reversing until both sensors read black");
  while (digitalRead(LEFT_SENSOR_PIN) != HIGH || digitalRead(RIGHT_SENSOR_PIN) != HIGH) {
    digitalWrite(REVERSE_MOTOR_PIN, HIGH); // Activate reverse motor
  }
  digitalWrite(REVERSE_MOTOR_PIN, LOW); // Stop reverse motor
}

void reverseTurnUntilWhite() {
  Serial.println("Reversing turn until sensors read white");
  while (digitalRead(LEFT_SENSOR_PIN) != LOW || digitalRead(RIGHT_SENSOR_PIN) != LOW) {
    digitalWrite(REVERSE_MOTOR_PIN, HIGH); // Keep reversing
    digitalWrite(TURN_MOTOR_PIN, HIGH); // Activate turn motor
  }
  digitalWrite(REVERSE_MOTOR_PIN, LOW); // Stop reverse motor
  digitalWrite(TURN_MOTOR_PIN, LOW); // Stop turn motor
}

void keepTurningUntilBlack() {
  Serial.println("Turning until both sensors read black again");
  while (digitalRead(LEFT_SENSOR_PIN) != HIGH || digitalRead(RIGHT_SENSOR_PIN) != HIGH) {
    digitalWrite(TURN_MOTOR_PIN, HIGH); // Keep turning
  }
  digitalWrite(TURN_MOTOR_PIN, LOW); // Stop turn motor
}

void reversePastRows(int rows) {
  Serial.print("Reversing past ");
  Serial.print(rows);
  Serial.println(" rows");
  int blackCount = 0;

  while (blackCount < rows) {
    digitalWrite(REVERSE_MOTOR_PIN, HIGH); // Keep reversing

    // Check if both sensors read black
    if (digitalRead(LEFT_SENSOR_PIN) == HIGH && digitalRead(RIGHT_SENSOR_PIN) == HIGH) {
      delay(500); // Small delay to debounce the sensor reading
      blackCount++;

      // Wait for sensors to read white again before continuing
      while (digitalRead(LEFT_SENSOR_PIN) == HIGH && digitalRead(RIGHT_SENSOR_PIN) == HIGH) {
        // Do nothing, just wait
      }
    }
  }
  digitalWrite(REVERSE_MOTOR_PIN, LOW); // Stop reverse motor
}
