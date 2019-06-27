
#include <Adafruit_DotStar.h>
#include <SPI.h>   

unsigned long totalTime = 0;
double average;
unsigned long currentTime = 0;

int standard = 530;
int tolerance = 12;
int readPin = A0;


#define PIN 6
#define TRUEPIXELS 27
#define NUMPIXELS 14

Adafruit_DotStar strip(TRUEPIXELS,DOTSTAR_BGR);




void setup() {  
  
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
  
  Serial.begin(9600);


  int i = 0;
  while (i < TRUEPIXELS) {
    strip.setPixelColor(i, strip.Color(60,60,0));
    i++;
  }
  strip.show();

  pinMode(readPin, INPUT);
  delay(10000);

  i = 0;
  while (i < TRUEPIXELS) {
    strip.setPixelColor(i, strip.Color(0,0,0));
    i++;
  }
  strip.show();
  
  average = averageSpin();
}


double averageSpin(){
  int i = 0;
  unsigned long lastTime = micros();
  unsigned long currentTime;

  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delayMicroseconds(100);
  }
  currentTime = micros();
  totalTime += currentTime - lastTime;
  lastTime = currentTime;
  delay(25);
  i++;

  return average;
}


void loop() {

  
  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delayMicroseconds(100);
  }
  
  currentTime = micros();



  int a = 0;
  uint32_t magenta = strip.Color(100, 0, 100);
  uint32_t green = strip.Color(0, 100, 0);
  for (int arg = 0; arg < NUMTURNS; arg++) {
    for (int mod = 0; mod < NUMPIXELS; mod++) {
      strip.setPixelColor( 13 - mod, pgm_read_byte(&(image[0][arg][mod])), pgm_read_byte(&(image[1][arg][mod])), pgm_read_byte(&(image[2][arg][mod])) );
    }
    while ( micros() - currentTime <  ((double) arg)*(average/(NUMTURNS))){
      delayMicroseconds(100);
    }
    strip.show();
  }
  
  /*int i = 0;
  while (i < TRUEPIXELS) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    i++;
  }
  pixels.show();*/
}
