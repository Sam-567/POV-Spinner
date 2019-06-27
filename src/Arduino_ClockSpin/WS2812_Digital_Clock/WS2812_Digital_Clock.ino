#include <Wire.h>
#include "RTClib.h"

#include <Adafruit_DotStar.h>
#include <SPI.h>   
#define NUMPIXELS 28

int Numbers[][5][3] = {
{ { 1, 1, 1},
  { 1, 0, 1},
  { 1, 0, 1},
  { 1, 0, 1},
  { 1, 1, 1}
},

{ { 0, 1, 0},
  { 1, 1, 0},
  { 0, 1, 0},
  { 0, 1, 0},
  { 1, 1, 1}
},

{ { 0, 1, 0},
  { 1, 0, 1},
  { 0, 0, 1},
  { 0, 1, 0},
  { 1, 1, 1}
},
{ { 1, 1, 1},
  { 0, 0, 1},
  { 1, 1, 1},
  { 0, 0, 1},
  { 1, 1, 1}
},
{ { 1, 0, 1},
  { 1, 0, 1},
  { 1, 1, 1},
  { 0, 0, 1},
  { 0, 0, 1}
},

{ { 1, 1, 1},
  { 1, 0, 0},
  { 1, 1, 1},
  { 0, 0, 1},
  { 1, 1, 1}
},

{ { 1, 1, 1},
  { 1, 0, 0},
  { 1, 1, 1},
  { 1, 0, 1},
  { 1, 1, 1}
},

{ { 1, 1, 1},
  { 0, 0, 1},
  { 0, 0, 1},
  { 0, 0, 1},
  { 0, 0, 1}
},

{ { 1, 1, 1},
  { 1, 0, 1},
  { 1, 1, 1},
  { 1, 0, 1},
  { 1, 1, 1}
},
  { { 1, 1, 1},
  { 1, 0, 1},
  { 1, 1, 1},
  { 0, 0, 1},
  { 1, 1, 1}
},

{ { 0, 0, 0},
  { 0, 1, 0},
  { 0, 0, 0},
  { 0, 1, 0},
  { 0, 0, 0}
}};

Adafruit_DotStar strip(NUMPIXELS,DOTSTAR_BGR);

RTC_DS1307 RTC;
int standard = 700;
int tolerance = 50;
int readPin = A0;

void setup() {
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  Wire.begin();
  RTC.begin();
  strip.begin();
  
  int i = 0;
  while (i < 28) {
    strip.setPixelColor(i, strip.Color(0,0,0));
    i++;
  }
  strip.show();
  delay(500);
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  DateTime now = RTC.now();
  //Low min
 /* Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();*/ 
  
  int minute = now.minute();
  int hour = now.hour();
  if (hour > 12) { hour -= 12;}
  int LowMin = minute % 10;
  int HighMin = minute / 10;
  int LowHour = hour % 10;
  int HighHour = hour / 10;


  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delay(0.5);
  }
  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      strip.setPixelColor(pin, Numbers[LowMin][pin][i] * strip.Color(0,150,0));
    }
    strip.show();
    delay(2);
  }

  for ( int pin = 0; pin < 12; pin++ ) {
      strip.setPixelColor(pin, 0);
  }
  strip.show();
  delay(2);

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      strip.setPixelColor(pin,  strip.Color(0, Numbers[HighMin][pin][i] * 150,0));
    }
    strip.show();
    delay(2);
  }

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      strip.setPixelColor(pin, strip.Color(0, Numbers[10][pin][i] * 150,0));
    }
    strip.show();
    delay(2);
  }

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      strip.setPixelColor(pin, strip.Color(0, Numbers[LowHour][pin][i] * 150,0));
    }
    strip.show();
    delay(2);
  }

  if( HighHour != 0 ){
    for ( int pin = 0; pin < 12; pin++ ) {
      strip.setPixelColor(pin, 0 );
    }
    strip.show();
    delay (2);

    for (int i = 2; i >= 0; i--) {
      for ( int pin = 0; pin < 5; pin++ ) {
        strip.setPixelColor(pin, strip.Color(0, Numbers[HighHour][pin][i] * 150,0)); 
      }
      strip.show();
      delay(2);
    }
  }
  
  for ( int pin = 0; pin < 12; pin++ ) {
      strip.setPixelColor(pin, 0 );
  }
  strip.show();


}
