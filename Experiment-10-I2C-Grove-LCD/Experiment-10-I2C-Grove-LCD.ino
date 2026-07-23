#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 0;
const int colorG = 255;
const int colorB = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);

  lcd.setCursor(0, 0);
  lcd.print("Hello!");

  lcd.setCursor(0, 1);
  lcd.print("Arduino Nano");
}

void loop() {
  // Nothing to repeat
}