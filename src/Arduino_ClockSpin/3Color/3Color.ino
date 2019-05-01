
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

int BackgroundMagnetism(){
  long startTime = millis();

  int Occurances[40];
  //Find mode as that is what background will be
  //Safe to assume background value will be between 400-600 so other can be ommitted
  while( millis() - startTime < 3000){
    int SimplifiedValue = (analogRead(readPin)-300) / 5;
    if ( SimplifiedValue > 0 && SimplifiedValue < 40){
      Occurances[SimplifiedValue]++;
    }
  }

  //Find mode of Occurances
  int LargestNum = Occurances[0];
  int IndexOfNum = 1;
  for(int i = 1; i < 40; i++){
    if ( Occurances[i] > LargestNum){
      IndexOfNum = i;
      LargestNum = Occurances[i];
    }
  }

  int Mode = IndexOfNum*5 + 300 + 1;
  return Mode;
}

void loop() {


  while ( abs( analogRead(readPin) - standard ) <= tolerance) {
    delay(1);
  }

  LastTime = CurrentTime;
  CurrentTime = millis();
  PastTimes[2] = PastTimes[1];
  PastTimes[1] = PastTimes[0];
  PastTimes[0] = CurrentTime - LastTime;

  // TODO Check times are not close together
  
  average = ( PastTimes[0] + PastTimes[1] + PastTimes[2])/3;
  
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 0, 0));
  }
  pixels.show();
  delay(3);
  
  //Show Red quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 100, 0, 0));
  }
  pixels.show();


  //Show Green quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 100, 0));
  }

  while( millis() < CurrentTime + average/3){
    //delay( millis() - (CurrentTime + average/3));
    delay(1);
  }
  pixels.show();

  
  //Show Blue quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 0, 100));
  }

  while( millis() < CurrentTime + (2*average/3)-16){
    //delay( millis() - (CurrentTime + 2*average/3));
    delay(1);
  }
  pixels.show();

  Serial.println(average);
}
