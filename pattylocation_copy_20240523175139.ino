void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging
}

void loop() {
  int patty = 1;  // Example patty value
  initiateTurn(patty);
  
  patty = 6;  // Another example patty value
  initiateTurn(patty);

  patty = 3;  // Another example patty value
  initiateTurn(patty);

  while (true);  // Stop the loop for this example
}

void initiateTurn(int patty) {
  int row = 0;
  String turnDirection;

  if (patty == 1 || patty == 6) {
    row = 1;
    if (patty == 1) {
      turnDirection = "LEFT";
    } else if (patty == 6) {
      turnDirection = "RIGHT";
    }
  } else if (patty == 2 || patty == 5) {
    row = 2;
    if (patty == 2) {
      turnDirection = "LEFT";
    } else if (patty == 5) {
      turnDirection = "RIGHT";
    }
  } else if (patty == 3 || patty == 4) {
    row = 3;
    if (patty == 3) {
      turnDirection = "LEFT";
    } else if (patty == 4) {
      turnDirection = "RIGHT";
    }
  } else {
    row = 0;
    turnDirection = "NONE";
  }

  // Output the results to the serial monitor
  Serial.print("Row: ");
  Serial.print(row);
  Serial.print(", Direction: ");
  Serial.println(turnDirection);
}
