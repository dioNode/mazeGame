#include "SSDTimer.h"

SSDTimer::SSDTimer() {
  int tempssd[8] = deSsdPins;
  int tempdig[4] = deDigitSelect;
  for (int pin = 0; pin < 8; pin++) {
    if (pin < 4) {
      digitSelect[pin] = tempdig[pin];
    }
    ssdPins[pin] = tempssd[pin];
  }
  for (int pin = 0; pin < 8; pin++) {
    if (pin < 4) {
      pinMode(digitSelect[pin], OUTPUT);
    }
    pinMode(ssdPins[pin], OUTPUT);
  }

  start = millis();	
}

void SSDTimer::setNum(int pin, int value) {
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
  
  int timeMod = pin == 2 ? 6 : 10;
  int toDisplay = ssdNumbers[value%timeMod];
  char out[32];
  for (int digit = 0; digit<7; digit++) {
    digitalWrite(ssdPins[digit], ((toDisplay>>(7-digit))%2)^1);
  }
  digitalWrite(ssdPins[7], 0);
}

void SSDTimer::displayTime(int millisTime) {
  for (int divisor = 0; divisor < 4; divisor++) {
  	if (divisor == 2) {
  	  millisTime/=6;
  	}
  	else {
      millisTime/=10;
    }
    setNum(3-divisor, millisTime);
  }
}

void SSDTimer::updateTime() {
    displayTime((int)((millis() - start)/100));
}