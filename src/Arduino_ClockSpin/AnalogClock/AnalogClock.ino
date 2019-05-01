
#include <Adafruit_NeoPixel.h>

unsigned long LastTime;
unsigned long CurrentTime;
unsigned long PastTimes[] = {0, 0, 0};
unsigned long average;

int standard = 540;
int tolerance = 8;
int readPin = A0;

#define PIN 6
#define NUMPIXELS 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:

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

  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delay(0.5);
  }
  LastTime = CurrentTime;
  CurrentTime = millis();
  PastTimes[2] = PastTimes[1];
  PastTimes[1] = PastTimes[0];
  PastTimes[0] = LastTime-CurrentTime;
  
  average = ( PastTimes[0] + PastTimes[1] + PastTimes[2])/3;


  //Show Red quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 255, 0, 0));
  }
  pixels.show();


  //Show Yellow quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 255, 255, 140));
  }

  if( millis() < CurrentTime + average/4){
    delay( millis() - (CurrentTime+average/4 - 1));
  }
  pixels.show();


  //Show Green quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 255, 0));
  }

  if( millis() < CurrentTime + average/2){
    delay( millis() - (CurrentTime + average/2 - 1));
  }
  pixels.show();

  
  //Show Blue quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 0, 255));
  }

  if( millis() < CurrentTime + 3*average/2){
    delay( millis() - (CurrentTime + 3*average/2 - 1));
  }
  pixels.show();

  
}
