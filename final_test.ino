const int AIN1 = 11;
const int AIN2 = 12;
const int PWMA = 10;
const int BIN1 = 8;
const int BIN2 = 7;
const int PWMB = 9;
const int SOUND = 3;
const int StartButtonR = A1;
const int StartButtonG = A2;
//sensors
const int RtrigPin = 6;
const int RechoPin = 2;
long duration;
int distance;
int timesStopped = 0;
bool botRunning = false;
//light sensor
int i = 1;
int colors = A0;
int v = 0;
int w = 0;
int light = analogRead(A0);


void setup()
{
  //assign control pins
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(SOUND, OUTPUT);
  //  pinMode(STBY, OUTPUT);
  pinMode(StartButtonR, INPUT_PULLUP);
  pinMode(StartButtonG, INPUT_PULLUP);
  pinMode(3, OUTPUT);   //for speaker
  pinMode(RtrigPin, OUTPUT);
  pinMode(RechoPin, INPUT);
  pinMode(5, OUTPUT); //Green LED
  pinMode(13, OUTPUT); //RED LED
  pinMode(4, OUTPUT);//yellow led
  pinMode(A0, INPUT);

  Serial.begin(9600);
}

void printData() {
  while (true) {
    Serial.println(analogRead(A0));
  }
}

void loop()
{ Serial.println(RechoPin);
  //goto task4;

  colors = (analogRead (A0));



  if (digitalRead(StartButtonR) == LOW && digitalRead(StartButtonG) == LOW)
  {
    botRunning = !botRunning;
    timesStopped = 0;
    for (i; i <= 5; i++)
    {
      tone(3, 150 * i, 200);
      delay(234);
    }

    {
      //green
      digitalWrite(5, HIGH);

    }

    colors = (analogRead(A0));
    forward();
    delay(1600);
    stopMoving();
    delay(250);
    turnLeft(350);
    delay(500);
    while (analogRead(A0) < 400) {
      forward();
    }

    stopMoving();
    digitalWrite(13, HIGH);
    digitalWrite(5, LOW);
    delay(250);
    turnLeft(500);
    delay(250);
    forward();
    delay(500);
    stopMoving();
    forward();


    while (analogRead(A0) < 400)
    {
      digitalWrite(13, LOW);
      digitalWrite(5, HIGH);
    }

    stopMoving();
    delay(250);
    digitalWrite(13, HIGH);
    digitalWrite(5, LOW);

    // ^^ though task 3

    //task4:
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMA, 220);
    analogWrite(PWMB, 220);


    while (v == 0)
    {

      int light = analogRead(A0);
      if (light < 300)
      { //right turn
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
      }
      else if ((light > 375) && (light < 600))
      { //left turn
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
      }
      else
      {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
      }
      if (light > 600)
      {
        digitalWrite(4, HIGH);
        digitalWrite(13, LOW);
        stopMoving();
        v = 1;
      }
    }

  }

  //exit(0);
}



void stopMoving() {
  delay(200);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, LOW);
  analogWrite(PWMB, LOW);
  delay(700);
}

void turnRight(int turnTime) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
  delay(turnTime);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

void turnLeft(int turnTime) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
  delay(turnTime);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}
//
void forward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 225);//rightmotor
  analogWrite(PWMB, 220);//leftmotor
}

float getUltra() {
  digitalWrite(RtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(RtrigPin, LOW);
  float tempNum = ((pulseIn(RechoPin, HIGH)) / 2 ) * 0.01242;
  return tempNum;

}
