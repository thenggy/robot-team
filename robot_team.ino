#include<Wire.h>

bool flag = false;
volatile byte buf[32];
int numBuf = 0;
//const int button1 = 4;
//const int button2 = 7;
//const int button3 = 8;
const int dirPin = 9;
const int stepPin = 10;
const int ren = 2;
const int rpwm = 3;
const int len = 5;
const int lpwm = 6;
const int limitBackWard=12;
const int limitStopMotor=13;

int stepperRevolution = 3200;
//int buttonState1 = 0;
//int buttonState2 = 0;
//int buttonState3 = 0;
int limitState1=0;
int limitState2=0;
int lastState1 = 0;
int lastState2 = 0;
int speed2 = 75;
int speed = 100;

bool goForward = false;
bool backWard = false;
bool iPress = false;
bool bPress = false;

unsigned long n;
unsigned long currentTime;

void setup() {
  Serial.begin(115200);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);

   //pinMode(buf[6], INPUT);
  //pinMode(buf[7], INPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ren, OUTPUT);
  pinMode(len, OUTPUT);
  pinMode(rpwm, OUTPUT);
  pinMode(lpwm, OUTPUT);
  //pinMode(buf[8], INPUT);
  pinMode(limitBackWard, INPUT); // use limitSwitch
  pinMode(limitStopMotor, INPUT); // use limitSwitch

  digitalWrite(ren, HIGH);
  digitalWrite(len, HIGH);
  pinMode(rpwm, LOW);
  pinMode(lpwm, LOW);



}

void receiveEvent(int howMany)
{
  for (int i = 0; i < howMany; i++)
  {
    buf [i] = Wire.read ();
  }
  numBuf = howMany;
  flag = true;
}
void loop() {
  if (flag == true)
  {
    flag = false;
    Serial.print("numBuf = ");
    Serial.print(numBuf);
    Serial.print(" :");
    for ( int i = 0; i < numBuf; i++ )
    {
      Serial.print(buf[i]);
      Serial.print(" ");
    }
    Serial.println(" end!");
  }
   //buttonState3 = digitalRead(buf[8]);
   limitState1=digitalRead(limitBackWard);
   limitState2=digitalRead(limitStopMotor);
  n = millis() - currentTime;
  if (buf[8] == HIGH) {
    analogWrite(rpwm, speed);
    analogWrite(lpwm, 0);
    currentTime = millis();
  }
  if (limitState1 == LOW) {
    analogWrite(rpwm, 0);
    analogWrite(lpwm, speed2);
  }
  if (limitState2 == LOW) {
    analogWrite(rpwm, 0);
    analogWrite(lpwm, 0);
  }
  goForward = false;
  backWard = false;
 // buttonState1 = digitalRead(buf[6]);
  //buttonState2 = digitalRead(buf[7]);

  if (p1ButtonPress()) {
    Serial.println("dir1");
    digitalWrite(dirPin, HIGH);

    //delay(100);

  }
  if ( p2ButtonPress ()) {
    digitalWrite(dirPin, LOW);
    //delay(100);

  }
  if (goForward || backWard) {
    for (int x = 0; x < stepperRevolution; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
    }
  }
}
bool p1ButtonPress() {
  bool iPress = false;
  if (buf[6] != lastState1) {
    if (buf[6] == LOW) {
      iPress = true;
      bPress = true;
      Serial.println("Hi3:");
    } else {
      digitalWrite(dirPin, HIGH);
      goForward = true;
      Serial.println("Hello3:");
    }
   // delay(5);
  }
  lastState1 = buf[6];
  return iPress;

}
bool p2ButtonPress () {
  bool iPress = false;
  if (buf[7] != lastState2) {
    if (buf[7] == LOW) {
      iPress = true;
      bPress = true;
      Serial.println("bitch:)");
    } else {
      digitalWrite(dirPin, LOW);
      backWard = true;
      Serial.println("Shit:)");
    }
   // delay(5);
  }
  lastState2 = buf[7];
  return iPress;
}
