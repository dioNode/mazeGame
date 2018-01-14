
// Analog input
int pinX = 1;
int pinY = 2;
int pinZ = 3;

// Digital input
int resetPin = 4;

// Accelerometer variables
int baseX = 0;
int baseY = 0;
int baseZ = 0;

void setup() {
  Serial.begin(9600);
  pinMode(resetPin, INPUT);
  Serial.println("Finished setup");
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
  //while (Serial.available() == 0);
  processAccelerometer();
  
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
  float norm = sqrt(sq(float(adjustedX)) + sq(float(adjustedY)));
  
  if (norm < 100) {
    status = "No motion";
  } else {
    status = "Swing";
  }

  if (adjustedY > 120) {
    status = "Swipe right";
    printData(adjustedX, adjustedY, adjustedZ, status, "\t","\n");
  } else if (adjustedY < -120) {
    status = "Swipe left";
    printData(adjustedX, adjustedY, adjustedZ, status, "\t","\n");
  }
  
  
}
