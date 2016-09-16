int buttonPin = 9;
int newState = 0;
int oldState = 1;
unsigned long buttonTime = 0;

int counter = 0;

unsigned long time = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  time = millis();
  // put your main code here, to run repeatedly:
    //Serial.print(digitalRead(9));
    newState = digitalRead(buttonPin);
    if(newState != oldState && time - buttonTime >= 300){
      if(newState == LOW){
        counter++;
        Serial.println();
        buttonTime = millis();
      }
     Serial.println(counter);
    }
    oldState = newState;
}
