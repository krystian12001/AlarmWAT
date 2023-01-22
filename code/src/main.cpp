#include <Arduino.h>
#include <RTClib.h>
#include <SPI.h>
#include <TM1637Display.h>
#include <DS1307RTC.h>
#include <TimeLib.h>

#define LED2 15

#define DISP_CLK 7
#define DISP_DIO 6

#define MAX_BUFFER_SIZE 128
char strBuff[MAX_BUFFER_SIZE];

RTC_DS1307 rtc;

bool isSet = false;

int _minute = 0;

int _hour = 0;

TM1637Display display(DISP_DIO, DISP_CLK);

byte dispdata[] = {0xff, 0xff, 0xff, 0xff};
byte temp;

void setMode();

void unSetMode();

void setup() 
{
  pinMode(LED2, OUTPUT);
  pinMode(DISP_CLK, OUTPUT);
  pinMode(DISP_DIO, OUTPUT);

  if (rtc.begin())
  {
    Serial.println("RTC Found");
  }
  else
  {
    while (1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  display.setBrightness(0x01);
}

void loop() 
{
  DateTime now = rtc.now();
  
  snprintf(strBuff, MAX_BUFFER_SIZE, "%02d/%02d/%02d (dzien: %d) %02d:%02d:%02d", 
  now.year(), now.month(), now.day(), now.dayOfTheWeek(), now.hour(), now.minute(), now.second());
  //_minute = now.minute();
  //_hour = now.hour();
  
  if(isSet)
  {
    setMode();
  }
  else
  {
    unSetMode();
  }
}

void unSetMode()
{
  if(!isSet)
  {
    display.showNumberDecEx(_minute, 0, true, 2, 2);
    display.showNumberDecEx(_hour, 0x40, true, 2, 0);
    delay(500);
    display.clear();
    delay(500);
  }
}

void setMode()
{
  if(!isSet)
  {
    display.showNumberDecEx(_minute, 0, true, 2, 2);
    display.showNumberDecEx(_hour, 0x40, true, 2, 0);
  }
}