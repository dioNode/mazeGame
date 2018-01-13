// Analog input
int pinX = 1;
int pinY = 2;
int pinZ = 3;
int pinJoyX = 4;
int pinJoyY = 5;

// Digital input
int resetPin = 4;

// Joystick variables
int horizontalMovement = 0;
int verticalMovement = 0;
int lastMove = 0; // 0=still, 1=up, 2=down, 3=left, 4=right
int currentMove = 0;
const int JOYSTICKHIGH = 1000;
const int JOYSTICKLOW  = 20;

// Accelerometer variables
int baseX = 0;
int baseY = 0;
int baseZ = 0;

void setup() {
  Serial.begin(9600);
  pinMode(resetPin, INPUT);
}

void printData(int x, int y, int z, String motion, String indentor, String newLine) {
  Serial.print(x);
  Serial.print(indentor);
  Serial.print(y);
  Serial.print(indentor);
  Serial.print(z);
  Serial.print(indentor);
  Serial.print(motion);
  Serial.println(newLine);
  delay(50);
}

void loop() {
  while (Serial.available() == 0);

  //processAccelerometer();
  processJoystick();
  
}

void processJoystick() {
  int x = analogRead(pinJoyX);
  int y = analogRead(pinJoyY);
  if (x > JOYSTICKHIGH) {
    horizontalMovement = 1;
  } else if (x < JOYSTICKLOW) {
    horizontalMovement = -1;
  } else {
    horizontalMovement = 0;
  }

  if (y > JOYSTICKHIGH) {
    verticalMovement = 1;
  } else if (y < JOYSTICKLOW) {
    verticalMovement = -1;
  } else {
    verticalMovement = 0;
  }
  displayJoyData();
}

void displayJoyData() {
  if (horizontalMovement == 1) {
    Serial.print("right");
  } else if (horizontalMovement == -1) {
    Serial.print("left");
  }
  if (verticalMovement == 1) {
    Serial.print("up");
  } else if (verticalMovement == -1) {
    Serial.print("down");
  }
  Serial.println();
}

void processAccelerometer() {
  int x = analogRead(pinX);
  int y = analogRead(pinY);
  int z = analogRead(pinZ);
  int reset = digitalRead(resetPin);
  if (reset == HIGH) {
    baseX = x;
    baseY = y;
    baseZ = z;
  }
  int adjustedX = x-baseX;
  int adjustedY = y-baseY;
  int adjustedZ = z-baseZ;

  String status;
  float norm = sqrt(sq(float(adjustedX)) + sq(float(adjustedY)) + sq(float(adjustedZ)));
  
  if (norm < 100) {
    status = "No motion";
  } else {
    status = "Swing";
  }

  if (adjustedY > 120) {
    status = "Swipe right";
  } else if (adjustedY < -120) {
    status = "Swipe left";
  }
  
  printData(adjustedX, adjustedY, adjustedZ, status, "\t","\n");
}

