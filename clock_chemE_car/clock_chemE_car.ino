/*
   THIS CODE IS USED FOR THE CLOCK USED IN UCI CHEME CAR CLUB ROOM. THE DESIGN IS INTENDED TO BE USED WITH WALL WART SUPPLY ONLY.
 */

#include <Wire.h>
#include "RTClib.h"//Library for ds1307 module from Adafruit
#include <LiquidCrystal.h>

#define MOUNTED_1307 1 //1 if the ds1307 is mounted directly on the Arduino, 0 if not.

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//pins required to operate the LCD display
RTC_DS1307 rtc;
void setup() {
        if(MOUNTED_1307)
        {
                pinMode(A3,OUTPUT);
                pinMode(A2,OUTPUT);
                digitalWrite(A3,HIGH);//A3 supplies to 5V
                digitalWrite(A2,LOW);//A2 acts as GND
        }
        lcd.begin(16, 2);
        Serial.begin(57600);
        if (!rtc.begin()) {
                Serial.println("Couldn't find RTC");
                while (1) ;
        }

        if (!rtc.isrunning()) {
                Serial.println("RTC is NOT running!");
                // following line sets the RTC to the date & time this sketch was compiled. Use this to adjust the time on the clock.
                rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
}

void loop() {
        DateTime now = rtc.now();

        //Begin of date printing
        lcd.setCursor(0, 0);//change cursor to first line
        lcd.print(now.month());
        lcd.print("/");
        lcd.print(now.day());
        lcd.print("/");
        lcd.print(now.year());

        //Begin of time printing
        lcd.setCursor(0, 1);//change cursor to the second line
        lcd.print(now.hour());
        lcd.print(":");
        lcd.print(now.minute());
        lcd.print(":");
        lcd.print(now.second());
        delay(100);//delay so that the number can be seen before clearing the screen. ALWAYS PUT THIS BEFORE lcd.clear()
        lcd.clear();


}
