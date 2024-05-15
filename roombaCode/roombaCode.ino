#define LEFT_WHEEL_ENABLE 10
#define LEFT_WHEEL_IN1 11
#define LEFT_WHEEL_IN2 12

#define RIGHT_WHEEL_ENABLE 1
#define RIGHT_WHEEL_IN1 2
#define RIGHT_WHEEL_IN2 3

enum State {
  FORWARD,
  BACKWARD,
  TURN_LEFT,
  TURN_RIGHT
};

void setup() {
  // put your setup code here, to run once:
  pinMode(LEFT_WHEEL_ENABLE, OUTPUT);
  pinMode(LEFT_WHEEL_IN1, OUTPUT);
  pinMode(LEFT_WHEEL_IN2, OUTPUT);
  pinMode(RIGHT_WHEEL_ENABLE, OUTPUT);
  pinMode(RIGHT_WHEEL_IN1, OUTPUT);
  pinMode(RIGHT_WHEEL_IN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int speed;
  bool lFd, rFd;
  State state;
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
}
