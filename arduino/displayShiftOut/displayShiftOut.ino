boolean testList[8];

int higherButtonPin = 10;
int lowerButtonPin = 11;

int clockPin = 12;
int latchPin = 13;
 

void setup() {
  // put your setup code here, to run once:
  pinMode(higherButtonPin, INPUT);
  pinMode(lowerButtonPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
 testList[0] = 1;
 testList[1] = 1;
 testList[2] = 1;
 shiftOut(clockPin, latchPin, LSBFIRST, (255 >> 8));
 shiftOut(clockPin, latchPin, LSBFIRST, 255);
}

void shiftOutArray( int clockPin, int latchPin, boolean list[]){
  digitalWrite(latchPin, 0);
  digitalWrite(clockPin, 0);

  for(int i = 0; i < sizeof(list); i++){
    digitalWrite(clockPin, 0);
    digitalWrite(latchPin, list[i]);
    digitalWrite(clockPin, 1);
  }
}

