#include "Ultrasonic.h"
#include <LiquidCrystal.h>
// Using without potentiometer 
// follow this tutorial https://www.youtube.com/watch?v=QS1rGdFrBd4
int Contrast=30;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
Ultrasonic ultrasonic( 9, 10 );
int distance;

void setup(){
  Serial.begin(9600);
//  analogWrite(6, Contrast);
  lcd.begin(16, 2);
  Serial.println("Measuring distance on HC-SR04");
  lcd.setCursor(0,0);
  lcd.print("Ready to Measure");
  delay(1);
}

void loop(){
  distance = ultrasonic.Ranging(INC);
  String message = "Dist: " + String(distance)  + " inch";
  lcd.clear();
  lcd.print(message);
  Serial.println(message);
//  Serial.println(distance);
  delay(1000);
}

