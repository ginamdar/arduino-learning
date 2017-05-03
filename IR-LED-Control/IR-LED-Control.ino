#include <IRremote.h>
//http://mertarduinotutorial.blogspot.ca/2017/01/arduino-tutorial-23-control-your-leds.html
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define BUTTON_1 0xFF1AE5 //R
#define BUTTON_2 0xFF9A65 //G
#define BUTTON_3 0xFFA25D //B
#define BUTTON_0 0xFF22DD //W
#define BUTTON_OK 0xFF02FD  //OFF

int blue_LED = 7;
int red_LED = 6;
int green_LED = 5;
int white_LED = 4;
bool isON = false;


void setup()
{
  pinMode(blue_LED, OUTPUT);
  pinMode(red_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(white_LED, OUTPUT);
  
  irrecv.enableIRIn();
}
void loop() {

  if (irrecv.decode(&results))
  {
    if (results.value == BUTTON_0)
    {
      digitalWrite(white_LED, HIGH);
    }
    if (results.value == BUTTON_1)
    {
      digitalWrite(blue_LED, HIGH);
    }
    if (results.value == BUTTON_2)
    {
      digitalWrite(red_LED, HIGH);
    }
    if (results.value == BUTTON_3)
    {
      digitalWrite(green_LED, HIGH);
    }
    if (results.value == BUTTON_OK)
    {
      digitalWrite(blue_LED, isON ? LOW : HIGH);
      digitalWrite(red_LED, isON ? LOW : HIGH);
      digitalWrite(green_LED, isON ? LOW : HIGH);
      digitalWrite(white_LED, isON ? LOW : HIGH);
      isON = !isON;
    }
    irrecv.resume();
  }
}
