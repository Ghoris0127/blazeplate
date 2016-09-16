/*
    Controller for the 4x 7-segment display
*/
int digit1 = 13;
int digit2 = 10;
int digit3 = 9;
int digit4 = 7;

int segmentA = 12;
int segmentB = 8;
int segmentC = 5;
int segmentD = 3;
int segmentE = 2;
int segmentF = 11;
int segmentG = 6;

int DecimalPoint = 4;

int counter = 0;

int digit1Num = 9;
int digit2Num = 9;
int digit3Num = 9;
int digit4Num = 9;

unsigned long time = 0;

void setup() {
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(DecimalPoint, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Serial.print(digit1Num);
  if (digit1Num != 1) {
    setDigit(1);
  }
  delayMicroseconds(45);
  Serial.print(digit2Num);
  if (digit1Num != 1) {
    setDigit(2);
  }
  delayMicroseconds(45);
  Serial.print(digit3Num);
  if (digit1Num != 1) {
    setDigit(3);
  }
  delayMicroseconds(45);
  Serial.println(digit4Num);
  if (digit1Num != 1) {
    setDigit(4);
  }
  delayMicroseconds(45);
}



void setDigitNumber(int digit, int number) {
  switch (digit) {
    case 1: digit1Num = number; break;
    case 2: digit2Num = number; break;
    case 3: digit3Num = number; break;
    case 4: digit4Num = number; break;
  }
}

void setDigit(int x) {
  clearLEDs();
  switch (x) {
    case 1: select1(); setNumber(digit1Num); break;
    case 2: select2(); setNumber(digit2Num); break;
    case 3: select3(); setNumber(digit3Num); break;
    case 4: select4(); setNumber(digit4Num); break;
  }
}

void select1() {
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);
}

void select2() {
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);
}

void select3() {
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, HIGH);
}

void select4() {
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, LOW);
}

void setNumber(int x)
{
  if (x == -1) {
    clearLEDs();
  }
  else if (x == 1) {
    one();
  }
  else if (x == 2) {
    two();
  }
  else if (x == 3) {
    three();
  }
  else if (x == 4) {
    four();
  }
  else if (x == 5) {
    five();
  }
  else if (x == 6) {
    six();
  }
  else if (x == 7) {
    seven();
  }
  else if (x == 8) {
    eight();
  }
  else if (x == 9) {
    nine();
  }
  else {
    zero();
  }
}

void dispDec(int x)
{
  digitalWrite(DecimalPoint, HIGH);
}

void clearLEDs()
{
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
  digitalWrite(DecimalPoint, LOW);
}

void zero()
{
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, LOW);
}

void one()
{
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}

void two()
{
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, LOW);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, HIGH);
}

void three()
{
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, HIGH);
}

void four()
{
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void five()
{
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void six()
{
  digitalWrite(segmentA, LOW);
  digitalWrite(segmentB, LOW);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void seven()
{
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, LOW);
  digitalWrite(segmentG, LOW);
}

void eight()
{
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}

void nine()
{
  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, LOW);
  digitalWrite(segmentE, LOW);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);
}
