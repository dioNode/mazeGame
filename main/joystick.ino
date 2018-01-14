

void displayJoyData(int angle) {
  
  if (angle > 45) {
      if (angle < 135) {
        // Right
        movePlayerRight();
        joystickStatus = 4;
      } else if (angle < 225) {
        // Down
        movePlayerDown()
        joystickStatus = 2;
      } else if (angle < 315) {
        // Left
        movePlayerLeft();
        joystickStatus = 3;
      } else {
        // Up
        movePlayerUp();
        joystickStatus = 1;
      } 
    } else {
      // Up
      joystickStatus = 1;
    }
  Serial.println(joystickStatus);
}

void processJoystick() {
  float x = analogRead(pinJoyX) - JOYMIDVALUE;
  float y = analogRead(pinJoyY) - JOYMIDVALUE;

  float norm = sqrt(sq(x)+sq(y));
  if (norm > 500 && joystickCounter == JOYDELAY) {
    float angle = atan(y/x)*360/(2*M_PI);
    if (x<0) {
      angle += 180;
    } else if (y<0 && x>0) {
      angle += 360;
    }
    joystickCounter = 0;
    displayJoyData(angle);
  } else {
    joystickStatus = 0;
  }
}

