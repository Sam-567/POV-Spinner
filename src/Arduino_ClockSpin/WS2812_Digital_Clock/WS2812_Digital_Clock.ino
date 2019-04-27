#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>
#define PIN 6
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

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

RTC_DS1307 RTC;
int standard = 530;
int tolerance = 8;
int readPin = A0;

void setup() {
  Wire.begin();
  RTC.begin();
  pixels.begin();
  
  int i = 0;
  while (i < 28) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    i++;
  }
  pixels.show();
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
      pixels.setPixelColor(pin, Numbers[LowMin][pin][i] * pixels.Color(0,150,0));
    }
    pixels.show();
    delay(2);
  }

  for ( int pin = 0; pin < 12; pin++ ) {
      pixels.setPixelColor(pin, 0);
  }
  pixels.show();
  delay(2);

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      pixels.setPixelColor(pin,  pixels.Color(0, Numbers[HighMin][pin][i] * 150,0));
    }
    pixels.show();
    delay(2);
  }

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      pixels.setPixelColor(pin, pixels.Color(0, Numbers[10][pin][i] * 150,0));
    }
    pixels.show();
    delay(2);
  }

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      pixels.setPixelColor(pin, pixels.Color(0, Numbers[LowHour][pin][i] * 150,0));
    }
    pixels.show();
    delay(2);
  }

  if( HighHour != 0 ){
    for ( int pin = 0; pin < 12; pin++ ) {
      pixels.setPixelColor(pin, 0 );
    }
    pixels.show();
    delay (2);

    for (int i = 2; i >= 0; i--) {
      for ( int pin = 0; pin < 5; pin++ ) {
        pixels.setPixelColor(pin, pixels.Color(0, Numbers[HighHour][pin][i] * 150,0)); 
      }
      pixels.show();
      delay(2);
    }
  }
  
  for ( int pin = 0; pin < 12; pin++ ) {
      pixels.setPixelColor(pin, 0 );
  }
  pixels.show();


}
