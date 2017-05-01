// include the library code:
#include <LiquidCrystal.h>
// Using without potentiometer 
// follow this tutorial https://www.youtube.com/watch?v=QS1rGdFrBd4
int Contrast=30;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
int distInch;
void setup() {
  Serial.begin(9600);
  analogWrite(6, Contrast);
  lcd.begin(16, 2);
  Serial.println("Measuring distance on HC-SR04");
  lcd.setCursor(0,0);
  lcd.print("Ready to Measure");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  distInch = distance * 0.39;
  // Speed of Sound 340 m/s i.e. 34000 cms/s and 10 microSeconds = 100000
  // 34000/100000
  lcd.clear();
  String message = "Distance: " + String(distInch)  + " inch";
  lcd.print(message);
  Serial.println(message);
//  Serial.println(distance);
  delay(1000);
}





