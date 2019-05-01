
#include <Adafruit_NeoPixel.h>

unsigned long LastTime = 0;
unsigned long CurrentTime = 0;
unsigned long PastTimes[] = {0, 0, 0};
unsigned long average;

int standard = 530;
int tolerance = 12;
int readPin = A0;

#define PIN 6
#define TRUEPIXELS 28
#define NUMPIXELS 14

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(TRUEPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin();
  
  int i = 0;
  while (i < TRUEPIXELS) {
    pixels.setPixelColor(i, pixels.Color(120,120,0));
    i++;
  }
  pixels.show();

  delay(500);
  pinMode(readPin, INPUT);
  Serial.begin(9600);

  delay(6000);

  i = 0;
  while (i < TRUEPIXELS) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    i++;
  }
  pixels.show();
  
  LastTime = millis();


}

void loop() {


  while ( abs( analogRead(readPin) - standard ) <= tolerance && millis() - LastTime > 8 ) {
    delay(1);
  }

  LastTime = CurrentTime;
  CurrentTime = millis();
  PastTimes[2] = PastTimes[1];
  PastTimes[1] = PastTimes[0];
  PastTimes[0] = CurrentTime - LastTime;


  average = ( PastTimes[0] + PastTimes[1] + PastTimes[2])/3;
  

  //Show Red segment
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 255, 0, 0));
  }
  pixels.show();


  //Show Blue segment
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 0, 255));
  }

  while( millis() < CurrentTime + 0.6*average){
    delay(1);
  }
  pixels.show();

}
