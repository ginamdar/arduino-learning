/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

void setup() {
  Serial.begin(57600);
  delay(10);
  Serial.println("Ready to Blink LED on PIN 13");
  pinMode(13, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, LOW); // Turn OFF  
  delay(1000);          // Wait for a second
  
  digitalWrite(13, HIGH);  // Turn the LED ON by making the voltage HIGH
  delay(4000);                      // Wait for 4 seconds (to demonstrate the active low LED)
}
