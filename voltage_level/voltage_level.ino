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
  EPD.println("hello world!");
  delay(100);
}

void loop()
{

  int ADC_VALUE = analogRead(35);
  Serial.print("ADC VALUE = ");
  Serial.println(ADC_VALUE);
  int adc_percentage = int(100 * ADC_VALUE / 4095);
  //delay(1000);
  float voltage_value = (ADC_VALUE * 3.3 ) / (4095);
  Serial.print("Voltage = ");
  Serial.print(voltage_value);
  Serial.println(" volts");
  //delay(1000);


  EPD.clearBuffer();
  EPD.fillScreen(EPD_WHITE);
  EPD.setCursor(0,0);
  EPD.print(adc_percentage);
  EPD.println("%");
  EPD.setCursor(0,26);
  EPD.println(voltage_value);
  EPD.setCursor(0,52);
  EPD.println(ADC_VALUE);
  EPD.display();
  delay(60000);
}
