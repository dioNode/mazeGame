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


String processAccelerometer() {
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
  } else if (adjustedY < -120) {
    status = "Swipe left";
  }
  
  return status;
}
