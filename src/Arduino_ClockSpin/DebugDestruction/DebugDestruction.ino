
#include <Adafruit_NeoPixel.h>

unsigned long LastTime = 0;
unsigned long CurrentTime = 0;
unsigned long PastTimes[] = {0, 0, 0};
unsigned long average;

int standard = 530;
int tolerance = 8;
int readPin = A0;

#define PIN 6
#define TRUEPIXELS 28
#define NUMPIXELS 14

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(TRUEPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin();
  
  int i = 0;
  while (i < TRUEPIXELS) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    i++;
  }
  pixels.show();
  delay(500);
  pinMode(readPin, INPUT);
  Serial.begin(9600);
  Serial.println("HUH");
  LastTime = millis();

  Serial.println(PastTimes[0]);
  Serial.println(PastTimes[1]);
  Serial.println(PastTimes[2]);
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

  //Serial.println("A");
  
  while ( abs( analogRead(readPin) - standard ) <= tolerance  ) {
    delay(0.5);
  }
  
  //Serial.println("B");
  
  LastTime = CurrentTime;
  CurrentTime = millis();
  PastTimes[2] = PastTimes[1];
  PastTimes[1] = PastTimes[0];
  PastTimes[0] = LastTime-CurrentTime;

  Serial.println(PastTimes[0]);
  Serial.println(PastTimes[1]);
  Serial.println(PastTimes[2]);

  //Check times are not close together
  
  average = ( PastTimes[0] + PastTimes[1] + PastTimes[2])/3;
  
  
  Serial.println(average);
  Serial.println(millis());
  
  //Show Red quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 255, 0, 0));
  }
  pixels.show();


  //Show Yellow quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 150, 50, 1204));
  }

  while( millis() < CurrentTime + average/4){
    //delay( millis() - (CurrentTime+average/4 - 1));
    delay(0.5);
  }
  pixels.show();


  //Show Green quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 255, 0));
  }

  while( millis() < CurrentTime + average/2){
    //delay( millis() - (CurrentTime + average/2 - 1));
    delay(0.5);
  }
  pixels.show();

  
  //Show Blue quarter
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color( 0, 0, 255));
  }

  while( millis() < CurrentTime + 3*average/2){
    //delay( millis() - (CurrentTime + 3*average/2 - 1));
    delay(0.5);
  }
  pixels.show();

 //Serial.println("C");
}
