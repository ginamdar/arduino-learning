/*----------------------------------------------------------------------*
 * Demonstrates usage of the alarm interrupt for alarm 1 and alarm 2.   *
 *                                                                      *
 * 26 December 2014.                                                    *
 *                                                                      *
 * Tested with Arduino 1.5.8, Arduino Nano w/ ATmega328, DS3231.        *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/ 
#include <DS3232RTC.h>        //http://github.com/JChristensen/DS3232RTC
#include <Time.h>              //http://playground.arduino.cc/Code/Time
#include <TimeLib.h>
#include <Wire.h>             //http://arduino.cc/en/Reference/Wire
#include <Streaming.h>        //http://arduiniana.org/libraries/streaming/

#define SQW_PIN 2

void repeatAlarm() {
  time_t time = RTC.get();
  int mi = minute(time);
  int hr = hour(time);
  hr++;
//  if (mi > 58){
//    mi = 2;
//    hr++;
//  }else {
//    mi += 2;
//  }
  if (hr == 24) {
    hr = 2;
  }
  Serial<<"New Time(hr:mm):" << _DEC(hr)<< ":"<<_DEC(mi)<<endl;
  RTC.setAlarm(ALM2_MATCH_HOURS, 0, hr, 1);    //daydate parameter should be between 1 and 7
  RTC.alarm(ALARM_2);                   //ensure RTC interrupt flag is cleared
  RTC.alarmInterrupt(ALARM_2, true);
}

void setup(void)
{
    Serial.begin(115200);

    //setSyncProvider() causes the Time library to synchronize with the
    //external RTC by calling RTC.get() every five minutes by default.
    setSyncProvider(RTC.get);
    Serial << "RTC Sync";
    if (timeStatus() != timeSet){
        Serial << " FAIL!";
    }
    Serial << endl;

    printDateTime( RTC.get() );
    Serial << " --> Current RTC time." << endl;

    //Disable the default square wave of the SQW pin.
    RTC.squareWave(SQWAVE_NONE);

    //Attach an interrupt on the falling of the SQW pin.
    pinMode(SQW_PIN, INPUT_PULLUP);
//    attachInterrupt(INT0, alarmIsr, FALLING);
    attachInterrupt(digitalPinToInterrupt(SQW_PIN), alarmIsr, FALLING);

    //Set an alarm at every 20th second of every minute.
//    RTC.setAlarm(ALM1_MATCH_SECONDS, 20, 0, 0, 1);    //daydate parameter should be between 1 and 7
    RTC.alarm(ALARM_1);                   //ensure RTC interrupt flag is cleared
    RTC.alarmInterrupt(ALARM_1, false);

    //Set an alarm every minute.
    repeatAlarm();
}

volatile boolean alarmIsrWasCalled = false;

void alarmIsr()
{
    alarmIsrWasCalled = true;
}

float getTemp(){
  int t = RTC.temperature();
  float celsius = t / 4.0;  
  return celsius;
}

void loop(void)
{
    if (alarmIsrWasCalled){
        if (RTC.alarm(ALARM_1)) {
            printDateTime( RTC.get() );
            Serial << " --> Alarm 1!" << endl;
        }
        if (RTC.alarm(ALARM_2)) {
            printDateTime( RTC.get() );
            Serial << " --> Alarm 2!" << endl;
            Serial << "Temp:" << getTemp() << endl;
            repeatAlarm();
        }
        alarmIsrWasCalled = false;
    }
}

void printDateTime(time_t t)
{
    Serial << ((day(t)<10) ? "0" : "") << _DEC(day(t)) << ' ';
    Serial << monthShortStr(month(t)) << " " << _DEC(year(t)) << ' ';
    Serial << ((hour(t)<10) ? "0" : "") << _DEC(hour(t)) << ':';
    Serial << ((minute(t)<10) ? "0" : "") << _DEC(minute(t)) << ':';
    Serial << ((second(t)<10) ? "0" : "") << _DEC(second(t));
}
