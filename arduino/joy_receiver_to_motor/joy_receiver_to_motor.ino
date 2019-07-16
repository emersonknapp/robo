#include <RFM69.h>
#include <SPI.h>
#define FREQUENCY RF69_915MHZ

struct JoyMsg {
  int v1;
  int h1;
  int v2;
  int h2;
};

const int NETWORK_ID = 0;
const int NODE_ID = 2;
const int JOY_NODE_ID = 1;
const bool ENCRYPT = false;
const char * ENCRYPTKEY = "TOPSECRETPASSWRD";
const bool USEACK = true;

// NOTE pin 2 taken by RFM69
const int left_motor_forward_pin = 3;
const int left_motor_backward_pin = 5;
const int right_motor_forward_pin = 6;
const int rx_led_pos_pin = 7;
const int rx_led_gnd_pin = 8;
const int right_motor_backward_pin = 9;
// NOTE pins 10, 11, 12, 13 taken by RFM69

RFM69 radio;
JoyMsg joy_msg;

void blink(byte PIN, int DELAY_MS)
// Blink an LED for a given number of ms
{
  digitalWrite(PIN, HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN, LOW);
}

void blocking_blink_n(int pin, int on_ms, int off_ms, int reps) {
  for (int i = 0; i < reps; i++) {
    digitalWrite(pin, HIGH);
    delay(on_ms);
    digitalWrite(pin, LOW);
    delay(off_ms);
  }
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

void printJoyMsg(JoyMsg* msg) {
  Serial.print("Joy recv [");
  Serial.print(msg->v1);
  Serial.print(", ");
  Serial.print(msg->h1);
  Serial.print(", ");
  Serial.print(msg->v2);
  Serial.print(", ");
  Serial.print(msg->h2);
  Serial.println("]");
}

bool parseJoyMsg(byte* data, byte len, JoyMsg * out) {
  if (len != sizeof(JoyMsg)) return false;
  *out = *(JoyMsg *)data;
  printJoyMsg(out);
  return true;
}

void setup() {
  Serial.begin(9600);

  // Set up motor controller pins
  pinMode(left_motor_forward_pin, OUTPUT);
  pinMode(left_motor_backward_pin, OUTPUT);
  pinMode(right_motor_forward_pin, OUTPUT);
  pinMode(right_motor_backward_pin, OUTPUT);

  // Set up RX indicator LED
  pinMode(rx_led_pos_pin, OUTPUT);
  digitalWrite(rx_led_pos_pin, LOW);
  pinMode(rx_led_gnd_pin, OUTPUT);
  digitalWrite(rx_led_gnd_pin, LOW);

  // Initialize the RFM69HCW
  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  if (ENCRYPT) {
    radio.encrypt(ENCRYPTKEY);
  }

  // Initialize joy msg
  joy_msg.v1 = 0;
  joy_msg.v2 = 0;
  joy_msg.h1 = 0;
  joy_msg.h2 = 0;

  blocking_blink_n(rx_led_pos_pin, 250, 250, 3);

  Serial.print("Receiver Node ");
  Serial.print(NODE_ID, DEC);
  Serial.println(" ready.");
}

void loop() {
  static char sendbuffer[62];
  static int sendlength = 0;
  static int left_current = 0;
  static int left_desired = 0;
  static int right_current = 0;
  static int right_desired = 0;
  static unsigned long last_time = millis();

  // radio SENDING
  {
    // TODO - is there anything we need to send right now?
  }

  // radio RECEIVING
  bool msg_ok = false;
  if (radio.receiveDone()) {
    // Serial.print("Received msg from node ");
    // Serial.println(radio.SENDERID, DEC);
    msg_ok = parseJoyMsg(radio.DATA, radio.DATALEN, &joy_msg);

    // Serial.print(" - ");
    // Serial.print(radio.DATALEN, DEC);
    // Serial.print(" bytes, message [");
    // for (byte i = 0; i < radio.DATALEN; i++) {
    //   Serial.print((char)radio.DATA[i]);
    // }
    // Serial.print("], RSSI ");
    // Serial.println(radio.RSSI);

    if (radio.ACKRequested()) {
      radio.sendACK();
      // Serial.println("ACK sent");
    }
    blink(rx_led_pos_pin, 10);
  }

  // Motor control managment

  // // First lerp
  if (msg_ok) {
    if (abs(joy_msg.v1) >= 100) {
      left_current = joy_msg.v1;
    } else {
      left_current = 0;
    }
    if (abs(joy_msg.v2) >= 100) {
      right_current = joy_msg.v2;
    } else {
      right_current = 0;
    }
  }
  // // Finally write out the current motor speed
  if (left_current > 0) {
    analogWrite(left_motor_backward_pin, 0);
    analogWrite(left_motor_forward_pin, left_current);
  } else {
    analogWrite(left_motor_backward_pin, -left_current);
    analogWrite(left_motor_forward_pin, 0);
  }

  if (right_current > 0) {
    analogWrite(right_motor_backward_pin, 0);
    analogWrite(right_motor_forward_pin, right_current);
  } else {
    analogWrite(right_motor_backward_pin, -right_current);
    analogWrite(right_motor_forward_pin, 0);
  }
}
