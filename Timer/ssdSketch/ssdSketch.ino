int digitSelect[4] = {14,15,16,17}; // Digit select pins, from 1 to 4
int ssdPins[8] = {2,3,4,5,6,7,8,9}; // Pins in order from A to G then DP
int ssdNumbers[10] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110}; // How to display each digit from 0 - 9 w/ DP
// Add 1 to ssd number to initiate DP

void setNum(int pin, int value) {
  // Multiplexes to a digit on the display, modulo 4
  // Takes pin 0 to 3
  for (int pin = 0; pin < 8; pin++) {
    digitalWrite(ssdPins[pin], HIGH);  
  }
  for (int pout = 0; pout < 4; pout++) {
    if (pout == pin) {
      digitalWrite(digitSelect[pout], HIGH);
    }
    else {
      digitalWrite(digitSelect[pout], LOW);
    }
  }
  
  int toDisplay = ssdNumbers[value%10];
  char out[32];
  for (int digit = 0; digit<7; digit++) {
    digitalWrite(ssdPins[digit], ((toDisplay>>(7-digit))%2)^1);
  }
  digitalWrite(ssdPins[7], 0);
}

void displayTime(int millisTime) {
  for (int divisor = 0; divisor < 4; divisor++) {
    millisTime/=10;
    setNum(3-divisor, millisTime);
  }
}

unsigned long start;
int curr;

void setup() {
  // put your setup code here, to run once:
  for (int pin = 0; pin < 8; pin++) {
    if (pin < 4) {
      pinMode(digitSelect[pin], OUTPUT);
    }
    pinMode(ssdPins[pin], OUTPUT);
  }

  start = millis();
}

void updateTime() {
    displayTime((int)((millis() - start)/100));
}

void loop() {
  // put your main code here, to run repeatedly:
  updateTime();
}
