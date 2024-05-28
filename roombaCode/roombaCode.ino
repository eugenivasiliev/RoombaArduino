#include <SoftwareSerial.h>

#define LEFT_WHEEL_ENABLE 10
#define LEFT_WHEEL_IN1 2
#define LEFT_WHEEL_IN2 3

#define RIGHT_WHEEL_ENABLE 11
#define RIGHT_WHEEL_IN1 4
#define RIGHT_WHEEL_IN2 5

#define out 8

#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3

#define PRESSURE A5

SoftwareSerial(13, 12);

enum State {
  FORWARD,
  BACKWARD,
  TURN_LEFT,
  TURN_RIGHT
};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Enter AT Commands");
  BTSerial.begin(9600);
  
  pinMode(LEFT_WHEEL_ENABLE, OUTPUT);
  pinMode(LEFT_WHEEL_IN1, OUTPUT);
  pinMode(LEFT_WHEEL_IN2, OUTPUT);
  pinMode(RIGHT_WHEEL_ENABLE, OUTPUT);
  pinMode(RIGHT_WHEEL_IN1, OUTPUT);
  pinMode(RIGHT_WHEEL_IN2, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(out, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int speed = 1023;
  bool lFd, rFd;
  State state = FORWARD;
  /*
  Forward -> lFd = rFd = true
  Backward -> lFd = rFd = false
  Left turn -> lFd = !rFd = false
  Right turn -> lFd = !rFd = true
  */
  switch(state) {
    case FORWARD:
    lFd = true;
    rFd = true;
    break;
    case BACKWARD:
    lFd = false;
    rFd = false;
    break;
    case TURN_LEFT:
    lFd = false;
    rFd = true;
    break;
    case TURN_RIGHT:
    lFd = true;
    rFd = false;
    break;
  }
  analogWrite(LEFT_WHEEL_ENABLE, map(abs(speed), 0, 1023, 0, 255));
  analogWrite(RIGHT_WHEEL_ENABLE, map(abs(speed), 0, 1023, 0, 255));
  digitalWrite(LEFT_WHEEL_IN1, (lFd) ? HIGH : LOW);
  digitalWrite(LEFT_WHEEL_IN2, (lFd) ? LOW : HIGH);
  digitalWrite(RIGHT_WHEEL_IN1, (rFd) ? HIGH : LOW);
  digitalWrite(RIGHT_WHEEL_IN2, (rFd) ? LOW : HIGH);

  digitalWrite(s2,  LOW);                                           //S2/S3 levels define which set  of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH  is for green 
  digitalWrite(s3, LOW);                                           
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);       //here we wait  until "out" go LOW, we start measuring the duration and stops when "out" is  HIGH again, if you have trouble with this expression check the bottom of the code
  delay(20);  
  digitalWrite(s3, HIGH);                                         //Here  we select the other color (set of photodiodes) and measure the other colors value  using the same techinque
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW  : HIGH);
  delay(20);  
  digitalWrite(s2, HIGH);  
  Green = pulseIn(out,  digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);

  BTSerial.write(Red + " " + Green + " " + Blue);

  int pressure = analogRead(PRESSURE);
  if(state = TURN_RIGHT) {
    delay(3000);
    state = FORWARD;
  }
  if(PRESSURE < 400) {
    state = TURN_RIGHT;
  }
  
}
