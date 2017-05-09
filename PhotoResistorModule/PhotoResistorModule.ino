/*
  LiquidCrystal Library - Blink

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and makes the
 cursor block blink.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
   * ends to +5V and ground
   * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalBlink

 */

// include the library code:
#include <LiquidCrystal.h>

// Using without potentiometer 
// follow this tutorial https://www.youtube.com/watch?v=QS1rGdFrBd4

int Contrast=20;
int photoSensorPin = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

// LCD      Arduino/BreadBoard
// VSS        Ground
// VDD        5v (Arduino via breadboard)
// V0         6 (Arduino)
// RS         12 (Arduino)
// RW         Ground
// E          11 (Arduino) 
// D4.D6      5,4,3,2 (Arduino)
// A(LED+)    5v with 220 ohm (backlight)
// E(LED-)    Ground

void setup() {
  Serial.begin(9600);
  analogWrite(6, Contrast);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  Serial.println("Initalizing..");
  lcd.print("Ready");
  delay(500);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.clear();
  int value = analogRead(photoSensorPin);
  
  lcd.print("Value:" + String(value));
  delay(300);
}


