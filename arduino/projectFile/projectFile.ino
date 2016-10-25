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
int display1Digit1Num = 0;
int display1Digit2Num = 0;
int display1Digit3Num = 0;
int display1Digit4Num = 0;

int display2Digit1Num = 0;
int display2Digit2Num = 0;
int display2Digit3Num = 0;
int display2Digit4Num = 0;

//button pins with their variables
int onOffPin = 14;
  int onOffNewState = 0;
  int onOffOldState = 1;
  unsigned long onOffButtonTime = 0;
int childLockPin = 15;
  int childLockNewState = 0;
  int childLockOldState = 1;
  unsigned long childLockButtonTime = 0;
int higherPitPin = 16;
  int higherPitNewState = 0;
  int higherPitOldState = 1;
  unsigned long higherPitButtonTime = 0;
int lowerPitPin = 17;
  int lowerPitNewState = 0;
  int lowerPitOldState = 1;
  unsigned long lowerPitButtonTime = 0;
int nextPitPin = 18;
  int nextPitNewState = 0;
  int nextPitOldState = 1;
  unsigned long nextPitButtonTime = 0;
int previousPitPin = 19;
  int previousPitNewState = 0;
  int previousPitOldState = 1;
  unsigned long previousPitButtonTime = 0;

//led variables
int led1 = 3;
int led2 = 5;
int led3 = 6;
int led4 = 9;
int led5 = 10;
int led6 = 11;
int led7 = 12;
int led8 = 13;

//defines datapins for the shift registers
int dataPin = 8;
int latchPin = 2;
int clockPin = 4;

//variables
unsigned long time;
boolean onOffButtonState = false; //false = off, true = on
boolean childLockButtonState = false; //false = off, true = on
int currentChangePit = 1;
int currentChangePitSave = 0;
unsigned long led7Time;
unsigned long led8Time;
boolean alreadyOff = false;

//initialises pins and their modes.
void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  pinMode(onOffPin, INPUT);
  digitalWrite(onOffPin, HIGH);
  
  pinMode(childLockPin, INPUT);
  digitalWrite(childLockPin, HIGH);
  
  pinMode(higherPitPin, INPUT);
  digitalWrite(higherPitPin, HIGH);
  
  pinMode(lowerPitPin, INPUT);
  digitalWrite(lowerPitPin, HIGH);
  
  pinMode(nextPitPin, INPUT);
  digitalWrite(nextPitPin, HIGH);
  
  pinMode(previousPitPin, INPUT);
  digitalWrite(previousPitPin, HIGH);
  
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  Serial.begin(9600);
}

//keeps on ROLLING AND ROLLING AND ROLLING
void loop() {
  //inputs current time in #time
  time = millis();
  //check for the power button first
  /** one explanation for button mechanisme: first you check the current state of the button pin (LOW or HIGH) then you check if #newstate and #oldstate are not the same(edge detection).
   * if they are not the same and #time - #buttontime is longer then 300. this just prevents bounce back of the button.
   * then you check if #newstate is low, that means the button is in pressed state. then you execute your code.
   * after your code and all the if statements you set #oldstate to #newstate.
   */
  onOffNewState = digitalRead(onOffPin);
  if(onOffNewState != onOffOldState && time - onOffButtonTime >= 300){
    if(onOffNewState == LOW){
      onOffButtonState = !onOffButtonState;
      Serial.println("hey this is button state: " + onOffButtonState);
      onOffButtonTime = millis();
      if(onOffButtonState){
        alreadyOff = false;
      }
    }
  }
  onOffOldState = onOffNewState;
  
  //if 'the power is turned on'
  if(onOffButtonState){
  //too lazy to explain this thing but it checks if the childlock has been pressed between 1 and 3 seconds if you wanne turn off the childlock  
  childLockNewState = digitalRead(childLockPin);
  if(childLockNewState != childLockOldState && time - childLockButtonTime >= 300){
    if(childLockNewState == LOW){
      if(!childLockButtonState){
        childLockButtonState = true;
        Serial.println("turned on!");
      }
      childLockButtonTime = millis();
    }else if(time - childLockButtonTime > 1000 && time - childLockButtonTime < 3000 && childLockNewState == HIGH && childLockButtonState){
     childLockButtonState = false;
     currentChangePit = currentChangePitSave;
     Serial.println("turned off!");
     childLockButtonTime = millis();
    }
  }
  childLockOldState = childLockNewState;
      
    if(!childLockButtonState){  
      //everything to do with the device if its turned ON.
      changePitLevelChecker();
      changeCurrentPitChecker();
      writeOutDisplays();
      writeOutLeds();
    }else{
      //sets #currentChangePit to 10 once and saves the value temporarily.
      if(currentChangePit != 10){
        currentChangePitSave = currentChangePit;
        currentChangePit = 10;
      }
      writeOutDisplays();
      writeOutLeds();
    }
  }else{
    //shifts out 2 zeros so all the digits are off
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
    //resets the values of all the digits.
    display1Digit1Num = 0;
    display1Digit2Num = 0;
    display1Digit3Num = 0;
    display1Digit4Num = 0;
    
    display2Digit1Num = 0;
    display2Digit2Num = 0;
    display2Digit3Num = 0;
    display2Digit4Num = 0;
    currentChangePit = 1;
    if(!alreadyOff){
      writeOutDisplays();
      alreadyOff = true;
    }
  }
}

void writeOutLeds(){
  if(display2Digit3Num != 0){
    if(time - led7Time > map(display2Digit3Num, 1, 9, 500, 100)){
      digitalWrite(led7, HIGH);
      led7Time = millis();
    }
  }else{
    digitalWrite(led7, LOW);  
  }
  
  if(display2Digit4Num != 0){
    if(time - led8Time > map(display2Digit4Num, 1, 9, 500, 100)){
      digitalWrite(led8, HIGH);
      led8Time = millis();
    }
  }else{
    digitalWrite(led8, LOW);  
  }
}

//same button mechanisme with the code for changing the current pit one higher or one lower. checks for values higher then 8 and lower then 1
void changeCurrentPitChecker(){
  nextPitNewState = digitalRead(nextPitPin);
  if(nextPitNewState != nextPitOldState && time - nextPitButtonTime >= 300){
    if(nextPitNewState == LOW){
      if(currentChangePit < 8){
        currentChangePit++;
        Serial.println("wont go next?");
      }
      nextPitButtonTime = millis();
    }
  }
  nextPitOldState = nextPitNewState;
  
  previousPitNewState = digitalRead(previousPitPin);
  if(previousPitNewState != previousPitOldState && time - previousPitButtonTime >= 300){
    if(previousPitNewState == LOW){
      if(currentChangePit > 1){
        currentChangePit--;
        Serial.println("wont go previous?");
      }
      previousPitButtonTime = millis();
    }
  }
  previousPitOldState = previousPitNewState;
}

//sets the current pit one higher or lower. checking for values not getting too high is done in changepit()
void changePitLevelChecker(){
  higherPitNewState = digitalRead(higherPitPin);
  if(higherPitNewState != higherPitOldState && time - higherPitButtonTime >= 300){
    if(higherPitNewState == LOW){
      changePit(1);
      Serial.println("wont go higher?");
      higherPitButtonTime = millis();
    }
  }
  higherPitOldState = higherPitNewState;
  
  lowerPitNewState = digitalRead(lowerPitPin);
  if(lowerPitNewState != lowerPitOldState && time - lowerPitButtonTime >= 300){
    if(lowerPitNewState == LOW){
      changePit(-1);
      Serial.println("wont go lower?");
      lowerPitButtonTime = millis();
    }
  }
  lowerPitOldState = lowerPitNewState;
}

//raises or lowers the values by 1 and also checks that the value is between 0 and 9
void changePit(int value){
  int temp = 0;
  if(currentChangePit == 1){
    display1Digit1Num += value;
    if(display1Digit1Num > 9){
     display1Digit1Num = 9; 
    }else if(display1Digit1Num < 0){
      display1Digit1Num = 0;
    }
  }
  else if(currentChangePit == 2){
    display1Digit2Num += value;
    if(display1Digit2Num > 9){
     display1Digit2Num = 9; 
    }else if(display1Digit2Num < 0){
      display1Digit2Num = 0;
    }
  }
  else if(currentChangePit == 3){
    display1Digit3Num += value;
    if(display1Digit3Num > 9){
     display1Digit3Num = 9; 
    }else if(display1Digit3Num < 0){
      display1Digit3Num = 0;
    }
  }
  else if(currentChangePit == 4){
    display1Digit4Num += value;
    if(display1Digit4Num > 9){
     display1Digit4Num = 9; 
    }else if(display1Digit4Num < 0){
      display1Digit4Num = 0;
    }
  }
  else if(currentChangePit == 5){
    display2Digit1Num += value;
    if(display2Digit1Num > 9){
     display2Digit1Num = 9; 
    }else if(display2Digit1Num < 0){
      display2Digit1Num = 0;
    }
  }
  else if(currentChangePit == 6){
    display2Digit2Num += value;
    if(display2Digit2Num > 9){
     display2Digit2Num = 9; 
    }else if(display2Digit2Num < 0){
      display2Digit2Num = 0;
    }
  }
  else if(currentChangePit == 7){
    display2Digit3Num += value;
    if(display2Digit3Num > 9){
     display2Digit3Num = 9; 
    }else if(display2Digit3Num < 0){
      display2Digit3Num = 0;
    }
  }
  else if(currentChangePit == 8){
    display2Digit4Num += value;
    if(display2Digit4Num > 9){
     display2Digit4Num = 9; 
    }else if(display2Digit4Num < 0){
      display2Digit4Num = 0;
    }
  }
}

//shifts out the right value for each digit.
void writeOutDisplays(){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(1));
  shiftOut(dataPin, clockPin, MSBFIRST, display1Digit1);
  digitalWrite(latchPin, HIGH);
  analogWrite(led1, map(display1Digit1Num, 0, 9, 0, 255));

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(2));
  shiftOut(dataPin, clockPin, MSBFIRST, display1Digit2);
  digitalWrite(latchPin, HIGH);
  analogWrite(led2, map(display1Digit2Num, 0, 9, 0, 255));

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(3));
  shiftOut(dataPin, clockPin, MSBFIRST, display1Digit3);
  digitalWrite(latchPin, HIGH);
  analogWrite(led3, map(display1Digit3Num, 0, 9, 0, 255));

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(4));
  shiftOut(dataPin, clockPin, MSBFIRST, display1Digit4);
  digitalWrite(latchPin, HIGH);
  analogWrite(led4, map(display1Digit4Num, 0, 9, 0, 255));

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(5));
  shiftOut(dataPin, clockPin, MSBFIRST, display2Digit1);
  digitalWrite(latchPin, HIGH);
  analogWrite(led5, map(display2Digit1Num, 0, 9, 0, 255));

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(6));
  shiftOut(dataPin, clockPin, MSBFIRST, display2Digit2);
  digitalWrite(latchPin, HIGH);
  analogWrite(led6, map(display2Digit2Num, 0, 9, 0, 255));

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(7));
  shiftOut(dataPin, clockPin, MSBFIRST, display2Digit3);
  digitalWrite(latchPin, HIGH);


  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, valueToDisplay(8));
  shiftOut(dataPin, clockPin, MSBFIRST, display2Digit4);
  digitalWrite(latchPin, HIGH);
}

//gets the right value to display(value is made for the shiftOut function)
int valueToDisplay(int digitValue){
  int temp;
  if(digitValue == 1){
    temp = getNumToDisplay(display1Digit1Num);
  }
  else if(digitValue == 2){
    temp = getNumToDisplay(display1Digit2Num);
  }
  else if(digitValue == 3){
    temp = getNumToDisplay(display1Digit3Num);
  }
  else if(digitValue == 4){
    temp = getNumToDisplay(display1Digit4Num);
  }
  else if(digitValue == 5){
    temp = getNumToDisplay(display2Digit1Num);
  }
  else if(digitValue == 6){
    temp = getNumToDisplay(display2Digit2Num);
  }
  else if(digitValue == 7){
    temp = getNumToDisplay(display2Digit3Num);
  }
  else if(digitValue == 8){
    temp = getNumToDisplay(display2Digit4Num);
  }
  if(currentChangePit == 10){
    return temp + 128;
  }else if(digitValue == currentChangePit){
    return temp + 128; 
  }else{
    return temp;
  }
}

//returns the value of all the segments so that the right symbole is displayed
int getNumToDisplay(int digitValue){
  if(digitValue == 0){
    return segmentA + segmentB + segmentC + segmentD + segmentE + segmentF;
  }
  else if(digitValue == 1){
    return segmentB + segmentC;
  }
  else if(digitValue == 2){
    return segmentA + segmentB + segmentD + segmentE + segmentG;
  }
  else if(digitValue == 3){
    return segmentA + segmentB + segmentC + segmentD + segmentG;
  }
  else if(digitValue == 4){
    return segmentB + segmentC + segmentF + segmentG; 
  }
  else if(digitValue == 5){
    return segmentA + segmentC + segmentD + segmentF + segmentG;
  }
  else if(digitValue == 6){
    return segmentA + segmentC + segmentD + segmentE + segmentF + segmentG;
  }
  else if(digitValue == 7){
    return segmentA + segmentB + segmentC;
  }
  else if(digitValue == 8){
    return segmentA + segmentB + segmentC + segmentD + segmentE + segmentF + segmentG;
  }
  else if(digitValue == 9){
    return segmentA + segmentB + segmentC + segmentD + segmentF + segmentG;
  }
  else {
    return 0;
  }
}


