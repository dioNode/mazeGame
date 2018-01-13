#ifndef SSDTIMER_H
#define SSDTIMER_H

#include "Arduino.h"

const static int deDigitSelect[4] = {14,15,16,17}; // Digit select pins, from 1 to 4
const static int deSsdPins[8] = {2,3,4,5,6,7,8,9}; // Pins in order from A to G then DP
const static int ssdNumbers[10] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110}; // How to display each digit from 0 - 9 w/ DP

class SSDTimer {
  public:
    int ssdPins[];
    int digitSelect[];
    SSDTimer();
    void setNum(int pin, int value);
    void displayTime(int millisTime);
    void updateTime();
  private:
    unsigned long start;
}

#endif