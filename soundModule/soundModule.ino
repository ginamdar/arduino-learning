// include the library code:
#include <LiquidCrystal.h>

// Using without potentiometer 
// follow this tutorial https://www.youtube.com/watch?v=QS1rGdFrBd4

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int soundSensor = A5;
int threshold   = 600;

void setup() {
  Serial.begin(9600);
  pinMode(soundSensor, INPUT);
  lcd.print("Ready");
}

void loop() {
  lcd.clear();
  int read1 = analogRead(soundSensor);
  delay(50);
  int read2 = analogRead(soundSensor);
  Serial.println(String(read1) + ":" + String(read2));
  if(read2 - read1 > 1)
  {
    lcd.setCursor(0,2);
    lcd.print("Sound Detected!!");
    lcd.blink();
    delay(2000);
    lcd.clear();
  }
  
  delay(100);  
//  lcd.clear();
}
