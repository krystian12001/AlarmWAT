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



TM1637Display display(DISP_DIO, DISP_CLK);

byte dispdata[] = {0xff, 0xff, 0xff, 0xff};
byte temp;


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
  
  digitalWrite(LED2, HIGH);

  snprintf(strBuff, MAX_BUFFER_SIZE, "%02d/%02d/%02d (dzien: %d) %02d:%02d:%02d", 
  now.year(), now.month(), now.day(), now.dayOfTheWeek(), now.hour(), now.minute(), now.second());

  dispdata[3] = display.encodeDigit(now.second()%10);
  //temp = now.second()/10;
  dispdata[2] = display.encodeDigit((byte)now.second()/10);
  //temp = temp/10;
  dispdata[1] = display.encodeDigit(now.minute()%10);
  //temp = temp/10;
  dispdata[0] = display.encodeDigit((byte)now.minute()/10);
  //temp = temp/10;

  display.setSegments(dispdata);
  
}