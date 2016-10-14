//says what segment has what value ready to convert for inputting in a shift out register
int display1digit1 = 1;
int display1digit2 = 2;
int display1digit3 = 4;
int display1digit4 = 8;

int display2digit1 = 16;
int display2digit2 = 32;
int display2digit3 = 64;
int display2digit4 = 128;

//says what segment has what value ready to convert for inputting in a shift out register
int segmentA = 1
int segmentB = 2;
int segmentC = 4;
int segmentD = 8;
int segmentE = 16;
int segmentF = 32;
int segmentG = 64;
int DecimalPoint = 128;

//variables to store the individual value of each digit
int display1digit1Num = 2;
int display1digit2Num = 5;
int display1digit3Num = 3;
int display1digit4Num = 4;

int display2digit1Num = 2;
int display2digit2Num = 5;
int display2digit3Num = 3;
int display2digit4Num = 4;

//defines datapins for the shift registers
int dataPin = 11;
int latchPin = 12;
int clockPin = 13;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 1);
  shiftOut(dataPin, clockPin, MSBFIRST, 255);
  digitalWrite(latchPin, HIGH);
}
