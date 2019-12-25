// voltage_level

#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>

/*D1 mini*/
/*
#define EPD_CS D0
#define EPD_DC D8
#define EPD_RST -1  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)
*/

/*D32 Pro*/
#define EPD_CS 14
#define EPD_DC 27
#define EPD_RST 33  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)

LOLIN_IL3897 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

// #define EPD_MOSI D7
// #define EPD_CLK D5
// LOLIN_IL3897 EPD(250,122, EPD_MOSI, EPD_CLK, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //IO

void setup()
{
  Serial.begin(115200);
  EPD.begin();
  EPD.setTextSize(3);
  EPD.clearBuffer();
  EPD.setTextColor(EPD_BLACK);
  delay(100);
}

void loop()
{

  // LOLIN D32 (no voltage divider need already fitted to board.
  // or NODEMCU ESP32 with 100K+100K voltage divider
  uint8_t percentage = 100;
  float voltage = analogRead(35) / 4096.0 * 7.23;
  percentage = 2808.3808 * pow(voltage, 4) - 43560.9157 * pow(voltage, 3) + 252848.5888 * pow(voltage, 2) - 650767.4615 * voltage + 626532.5703;
  if (voltage > 4.19) percentage = 100;
  else if (voltage <= 3.50) percentage = 0;

  EPD.clearBuffer();
  EPD.fillScreen(EPD_WHITE);
  EPD.setCursor(0,0);

  EPD.println(String(voltage)+"V " + String(percentage)+"%");

  EPD.display();

  delay(60000);
}
