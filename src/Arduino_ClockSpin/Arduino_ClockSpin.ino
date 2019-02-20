#include <Wire.h>
#include "RTClib.h"

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
//int Numbers[][5][3] = {Zero, One};
//int* Numbers[10] = {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};

int led[] =  {8, 9, 12, 11, 10}; // the number of the LED pin
RTC_DS1307 RTC;
int standard = 540;
int tolerance = 8;
int readPin = A0;

void setup() {
  Wire.begin();
  RTC.begin();

  int i = 0;
  while (i < 5) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
    i++;
  }
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

  /*Serial.print(LowMin);
  Serial.print(" ");
  Serial.print(HighMin);
  Serial.print(" ");
  Serial.print(LowHour);
  Serial.print(" ");
  Serial.print(HighHour);
  Serial.print(" ");*/
  
  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delay(0.5);
  }
  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      digitalWrite ( led[pin], Numbers[LowMin][pin][i] );
    }
    delay(2);
  }

  for ( int pin = 0; pin < 5; pin++ ) {
    digitalWrite( led[pin], 0);
  }
  delay(2);

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      digitalWrite ( led[pin], Numbers[HighMin][pin][i] );
    }
    delay(2);
  }

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      digitalWrite ( led[pin], Numbers[10][pin][i] );
    }
    delay(2);
  }

  for (int i = 2; i >= 0; i--) {
    for ( int pin = 0; pin < 5; pin++ ) {
      digitalWrite ( led[pin], Numbers[LowHour][pin][i] );
    }
    delay(2);
  }

  if( HighHour != 0 ){
    for ( int pin = 0; pin < 5; pin++ ) {
      digitalWrite( led[pin], 0);
    }
    delay (2);

    for (int i = 2; i >= 0; i--) {
      for ( int pin = 0; pin < 5; pin++ ) {
        digitalWrite ( led[pin], Numbers[HighHour][pin][i] );
      }
      delay(2);
    }
  }
  
  for ( int pin = 0; pin < 5; pin++ ) {
    digitalWrite( led[pin], 0);
    
  }


}
