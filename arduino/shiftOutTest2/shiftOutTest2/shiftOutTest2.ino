//says what segment has what value ready to convert for inputting in a shift out register
int display1Digit1 = 255 - 1;
int display1Digit2 = 255 - 2;
int display1Digit3 = 255 - 4;
int display1Digit4 = 255 - 8;

int display2Digit1 = 255 - 16;
int display2Digit2 = 255 - 32;
int display2Digit3 = 255 - 64;
int display2Digit4 = 255 - 128;

//says what segment has what value ready to convert for inputting in a shift out register
int segmentA = 1;
int segmentB = 2;
int segmentC = 4;
int segmentD = 8;
int segmentE = 16;
int segmentF = 32;
int segmentG = 64;
int DecimalPoint = 128;

//variables to store the individual value of each digit
int display1Digit1Num = 2;
int display1Digit2Num = 3;
int display1Digit3Num = 4;
int display1Digit4Num = 5;

int display2Digit1Num = 6;
int display2Digit2Num = 7;
int display2Digit3Num = 8;
int display2Digit4Num = 9;

//defines datapins for the shift registers
int dataPin = 11;
int latchPin = 12;
int clockPin = 13;

unsigned long time;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  time = millis();
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(1));
  shiftOut(dataPin, clockPin, MSBFIRST, display1Digit1);
  digitalWrite(latchPin, HIGH);
   
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(2));
  shiftOut(dataPin, clockPin, MSBFIRST, display1Digit2);
  digitalWrite(latchPin, HIGH);
  

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(3));
  shiftOut(dataPin, clockPin, MSBFIRST, display1Digit3);
  digitalWrite(latchPin, HIGH);
  
   
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(4));
  shiftOut(dataPin, clockPin, MSBFIRST, display1Digit4);
  digitalWrite(latchPin, HIGH);
  

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(5));
  shiftOut(dataPin, clockPin, MSBFIRST, display2Digit1);
  digitalWrite(latchPin, HIGH);
   
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(6));
  shiftOut(dataPin, clockPin, MSBFIRST, display2Digit2);
  digitalWrite(latchPin, HIGH);
  

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(7));
  shiftOut(dataPin, clockPin, MSBFIRST, display2Digit3);
  digitalWrite(latchPin, HIGH);
  
   
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(8));
  shiftOut(dataPin, clockPin, MSBFIRST, display2Digit4);
  digitalWrite(latchPin, HIGH);
  
}

int valueToDisplay(int digitValue){
  int temp;
  if(digitValue == 1){
    temp = getNumToDisplay(display1Digit1Num);
  }else if(digitValue == 2){
    temp = getNumToDisplay(display1Digit2Num);
  }else if(digitValue == 3){
    temp = getNumToDisplay(display1Digit3Num);
  }else if(digitValue == 4){
    temp = getNumToDisplay(display1Digit4Num);
  }else if(digitValue == 5){
    temp = getNumToDisplay(display2Digit1Num);
  }else if(digitValue == 6){
    temp = getNumToDisplay(display2Digit2Num);
  }else if(digitValue == 7){
    temp = getNumToDisplay(display2Digit3Num);
  }else if(digitValue == 8){
    temp = getNumToDisplay(display2Digit4Num);
  }
  //TODO change valueX into the thing berkay will add that shows the current display digit
  if(digitValue ==  99){
    return temp + 128;
  }else{
    return temp;
  }
}

int getNumToDisplay(int digitValue){
  if(digitValue == 0){
    return segmentA + segmentB + segmentC + segmentD + segmentE + segmentF;
  }else if(digitValue == 1){
    return segmentB + segmentC;
  }else if(digitValue == 2){
    return segmentA + segmentB + segmentD + segmentE + segmentG;
  }else if(digitValue == 3){
    return segmentA + segmentB + segmentC + segmentD + segmentG;
  }else if(digitValue == 4){
    return segmentB + segmentC + segmentF + segmentG; 
  }else if(digitValue == 5){
    return segmentA + segmentC + segmentD + segmentF + segmentG;
  }else if(digitValue == 6){
    return segmentA + segmentC + segmentD + segmentE + segmentF + segmentG;
  }else if(digitValue == 7){
    return segmentA + segmentB + segmentC;
  }else if(digitValue == 8){
    return segmentA + segmentB + segmentC + segmentD + segmentE + segmentF + segmentG;
  }else if(digitValue == 9){
    return segmentA + segmentB + segmentC + segmentD + segmentF + segmentG;
  }else {
    return 0;
  }
}
