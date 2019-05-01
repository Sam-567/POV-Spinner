
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 28

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int standard = 530;
int tolerance = 8;
int readPin = A0;

void setup() {

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
  noInterrupts();
}

void loop() {

  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delay(0.5);
  }
  int i = 0;
  while (i < 14) {
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    i++;
  }
  pixels.show();

  i = 0;
  while (i < 14) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    i++;
  }
  delay(0.5);
  pixels.show();
  
  delay(10);
  
}
