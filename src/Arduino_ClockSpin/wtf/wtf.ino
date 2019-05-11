
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

unsigned long totalTime = 0;
double average;

int standard = 530;
int tolerance = 12;
int readPin = A0;

#define PIN 6
#define TRUEPIXELS 28
#define NUMPIXELS 14
#define CYCLESPERSPIN 24.0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(TRUEPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin();
  
  Serial.begin(9600);


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

double averageSpin(){

  
  int i = 0;
  unsigned long lastTime = micros();
  unsigned long currentTime;
  while( i < 40 ){
    while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
      delay(1);
    }
    currentTime = micros();
    totalTime += currentTime - lastTime;
    lastTime = currentTime;
    delay(25);
    i++;
  }

  double average = totalTime / 40.0;

  return average;
}

void loop() {
  
  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delayMicroseconds(100);
  }

  unsigned long CurrentTime = micros();


  for( double s = 0; s < CYCLESPERSPIN; s++){
    //Show Red Segment
    for (int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color( 100, 0, 0));
    }
    
    while( micros() < CurrentTime + (average/(CYCLESPERSPIN))*s ){
      delayMicroseconds(10);
    }
    pixels.show();

    
    //Show Green segment
    for (int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color( 0, 100, 0));
    }
  
    while( micros() < CurrentTime + (average/(3.0*CYCLESPERSPIN)) + (average/CYCLESPERSPIN)*s ){
      delayMicroseconds(10);
    }
    pixels.show();
  
    //Show Blue segment
    for (int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color( 0, 0, 100));
    }
  
    while( micros() < CurrentTime + (average/(3.0*CYCLESPERSPIN))*2.0 + (average/CYCLESPERSPIN)*s ){
      delayMicroseconds(10);
    }
    pixels.show();
  }
}
