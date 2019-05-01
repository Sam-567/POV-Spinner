
#include <Adafruit_NeoPixel.h>

unsigned long totalTime = 0;
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
  
  Serial.begin(9600);

  unsigned long test = 1234;
  unsigned long x =test/3;
  Serial.println(x);

  int i = 0;
  while (i < TRUEPIXELS) {
    pixels.setPixelColor(i, pixels.Color(120,120,0));
    i++;
  }
  pixels.show();

  delay(500);
  pinMode(readPin, INPUT);
  delay(10000);

  i = 0;
  while (i < TRUEPIXELS) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    i++;
  }
  pixels.show();
  
  average = averageSpin();
  Serial.println(average);
}

unsigned long averageSpin(){

  
  int i = 0;
  unsigned long lastTime = millis();
  unsigned long currentTime;
  while( i < 40 ){
    while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
      delay(1);
    }
    currentTime = millis();
    totalTime += currentTime - lastTime;
    lastTime = currentTime;
    delay(25);
    i++;
  }

  unsigned long average = totalTime / 40;
  return average;
}

void loop() {

  Serial.println(average);
  Serial.println(totalTime);

  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delayMicroseconds(100);
  }

  unsigned long CurrentTime = millis();
  
  //Show Red quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 255, 0, 0));
  }
  pixels.show();

  
  //Show Green segment
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 255, 0));
  }

  while( millis() < CurrentTime + average/3){
    delayMicroseconds(100);
  }
  pixels.show();

  //Show Blue segment
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 0, 255));
  }

  while( millis() < CurrentTime + (2*average)/3 ){
    delayMicroseconds(100);
  }
  pixels.show();


}
