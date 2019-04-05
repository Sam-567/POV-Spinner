void setup() {
  // put your setup code here, to run once:

}

unsigned long LastTime;
unsigned long CurrentTime;
unsigned long[3] PastTimes = {0, 0, 0};
unsigned long average;

void loop() {

  while ( abs( analogRead(readPin) - standard ) <= tolerance ) {
    delay(0.5);
  }
  LastTime = CurrentTime;
  CurrentTime = millis();
  PastTimes[1] = PastTimes[0];
  PastTimes[2] = PastTimes[1];
  PastTimes[0] = LastTime-CurrentTime;
  
  average = ( PastTimes[0] + PastTimes[1] + PastTimes[2])/3;

  
}
