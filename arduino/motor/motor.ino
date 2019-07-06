int left_motor_forward_pin = 3;
int left_motor_backward_pin = 5;
int right_motor_forward_pin = 6;
int right_motor_backward_pin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(left_motor_forward_pin, OUTPUT);
  pinMode(left_motor_backward_pin, OUTPUT);
  pinMode(right_motor_forward_pin, OUTPUT);
  pinMode(right_motor_backward_pin, OUTPUT);
}

void leftMotor(int val) {
  if (val < 0) {
    analogWrite(left_motor_backward_pin, -val);
  } else {
    analogWrite(left_motor_forward_pin, val);
  }
}

void rightMotor(int val) {
  if (val < 0) {
    analogWrite(right_motor_backward_pin, -val);
  } else {
    analogWrite(right_motor_forward_pin, val);
  }
}

void twist(int linear, int angular) {
  int left = 0;
  int right = 0;

  // TODO mix linear and angular
  left = angular;
  right = -angular;

  leftMotor(left);
  rightMotor(right);
}

void loop() {
  int mzero = 80;
  int mmax = 255;
  for (int i = -mzero; i > -mmax; i--) {
    twist(0, i);
    delay(20);
  }
  for (int i = -mmax; i < -mzero; i++) {
    twist(0, i);
    delay(20);
  }
  analogWrite(left_motor_forward_pin, 0);
  analogWrite(left_motor_backward_pin, 0);
  analogWrite(right_motor_forward_pin, 0);
  analogWrite(right_motor_backward_pin, 0);
  for (int i = mzero; i < mmax; i++) {
    twist(0, i);
    delay(20);
  }
  for (int i = mmax; i > mzero; i--) {
    twist(0, i);
    delay(20);
  }
  analogWrite(left_motor_forward_pin, 0);
  analogWrite(left_motor_backward_pin, 0);
  analogWrite(right_motor_forward_pin, 0);
  analogWrite(right_motor_backward_pin, 0);
}
