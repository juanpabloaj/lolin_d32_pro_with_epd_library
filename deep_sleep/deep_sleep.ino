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


long SleepDurationMinutes = 1;
int StartTime, CurrentHour = 0, CurrentMin = 0, CurrentSec = 0;
RTC_DATA_ATTR int wakeUpCounter = 0;

void setup()
{
  Serial.begin(115200);
  EPD.begin();
  EPD.setTextSize(2);
  EPD.clearBuffer();
  EPD.setTextColor(EPD_BLACK);
  EPD.fillScreen(EPD_WHITE);
  EPD.setCursor(0,0);

  showVoltagePercentage();
  
  EPD.println("wake up counter " + String(++wakeUpCounter));
  
  EPD.display();
  delay(2000);
  
  BeginSleep();
}

void loop()
{
}

void BeginSleep() {

  EPD.println("sleeping...");
  EPD.display();
  delay(1000);
  
  // Some ESP32 are too fast to maintain accurate time
  long SleepTimer = (SleepDurationMinutes * 60 - ((CurrentMin % SleepDurationMinutes) * 60 + CurrentSec)) + 5;
  esp_sleep_enable_timer_wakeup(SleepTimer * 1000000LL);

  Serial.println("Entering " + String(SleepTimer) + "-secs of sleep time");
  Serial.println("Awake for : " + String((millis() - StartTime) / 1000.0, 3) + "-secs");
  Serial.println("Starting deep-sleep period...");
  esp_deep_sleep_start();
}

void showVoltagePercentage() {
  float voltage = analogRead(35) / 4096.0 * 7.23;
  uint8_t percentage = PercentageFromVoltage(voltage);

  EPD.println(String(voltage)+"V " + String(percentage)+"%");
}

uint8_t PercentageFromVoltage(float voltage) {
  // LOLIN D32 (no voltage divider need already fitted to board.
  // or NODEMCU ESP32 with 100K+100K voltage divider
  uint8_t percentage;
  percentage = 2808.3808 * pow(voltage, 4) - 43560.9157 * pow(voltage, 3) + 252848.5888 * pow(voltage, 2) - 650767.4615 * voltage + 626532.5703;
  if (voltage > 4.19) percentage = 100;
  else if (voltage <= 3.50) percentage = 0;

  return percentage;
}
