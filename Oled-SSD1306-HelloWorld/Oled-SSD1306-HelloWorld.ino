#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if defined(ARDUINO_AVR_UNO)
#define OLED_RESET 4
#define BAUD_RATE 9600
#define WELCOME_MSG "Hello Arduino"
#else
//assume nodemcu
#define OLED_RESET 16 //https://forums.adafruit.com/viewtopic.php?f=22&t=86345&p=434831&hilit=OLED+nodemcu#p434831
#define BAUD_RATE 115200
// NodeMcu 
// D1 => SCL
// D2 => SDA
#define WELCOME_MSG "Hello NodeMcu"
#endif

#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Adafruit_SSD1306 display(OLED_RESET);

//End
void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("hello");
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
//  display.display();
//  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
}

void loop() {
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(WELCOME_MSG);
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); 
  display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
  display.clearDisplay();  
}
