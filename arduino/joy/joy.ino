// RFM69HCW Example Sketch
// Send serial input characters from one RFM69 node to another
// Based on RFM69 library sample code by Felix Rusu
// http://LowPowerLab.com/contact
// Modified for RFM69HCW by Mike Grusin, 4/16

// This sketch will show you the basics of using an
// RFM69HCW radio module. SparkFun's part numbers are:
// 915MHz: https://www.sparkfun.com/products/12775
// 434MHz: https://www.sparkfun.com/products/12823

// See the hook-up guide for wiring instructions:
// https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide

// Uses the RFM69 library by Felix Rusu, LowPowerLab.com
// Original library: https://www.github.com/lowpowerlab/rfm69
// SparkFun repository: https://github.com/sparkfun/RFM69HCW_Breakout

// Include the RFM69 and SPI libraries:

#include <RFM69.h>
#include <SPI.h>

// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     0   // Must be the same for all nodes
#define MYNODEID      1   // My node ID
#define TONODEID      2   // Destination node ID

// RFM69 frequency, uncomment the frequency of your module:

//#define FREQUENCY   RF69_433MHZ
#define FREQUENCY     RF69_915MHZ

// AES encryption (or not):

#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    "TOPSECRETPASSWRD" // Use the same 16-byte key on all nodes

// Use ACKnowledge when sending messages (or not):

#define USEACK        true // Request ACKs or not

const int j1_v_apin = 0;
const int j1_h_apin = 1;
const int j2_v_apin = 3;
const int j2_h_apin = 4;

// NOTE pin 2 used by RFM69
const int j1_sel_pin = 3;
const int j2_sel_pin = 4;
const int rx_led_gnd_pin = 8;
const int rx_led_pos_pin = 9;
// NOTE pins 10, 11, 12, 13 used by RFM69

struct JoyMsg {
  int v1;
  int h1;
  int v2;
  int h2;
};

RFM69 radio;

void blocking_blink_n(int pin, int on_ms, int off_ms, int reps) {
  for (int i = 0; i < reps; i++) {
    digitalWrite(pin, HIGH);
    delay(on_ms);
    digitalWrite(pin, LOW);
    delay(off_ms);
  }
}

// Blink an LED for a given number of ms
void blink(byte pin, int on_ms) {
  digitalWrite(pin, HIGH);
  delay(on_ms);
  digitalWrite(pin, LOW);
}

bool send(char * buffer, unsigned int len) {
  bool ret = true;
  if (USEACK) {
    ret = radio.sendWithRetry(TONODEID, buffer, len);
  } else {
    radio.send(TONODEID, buffer, len);
  }
  blink(rx_led_pos_pin, 10);
  return ret;
}

void readMsg(JoyMsg * msg) {
  int v1 = analogRead(j1_v_apin);
  int h1 = analogRead(j1_h_apin);
  int sel1 = digitalRead(j1_sel_pin);
  int v2 = analogRead(j2_v_apin);
  int h2 = analogRead(j2_h_apin);
  int sel2 = digitalRead(j2_sel_pin);

  int scale = 2;
  msg->v1 = (v1 - 511) / scale;
  msg->h1 = (h1 - 511) / scale;
  msg->v2 = (v2 - 511) / scale;
  msg->h2 = (h2 - 511) / scale;

}

void setup() {
  // Open a serial port so we can send keystrokes to the module:
  Serial.begin(9600);

  // Set up the indicator LED (optional):
  pinMode(rx_led_pos_pin ,OUTPUT);
  digitalWrite(rx_led_pos_pin, LOW);
  pinMode(rx_led_gnd_pin, OUTPUT);
  digitalWrite(rx_led_gnd_pin, LOW);

  // Initialize the RFM69HCW:
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setHighPower(); // Always use this for RFM69HCW
  if (ENCRYPT) {
    radio.encrypt(ENCRYPTKEY);
  }

  // Set up joystick pins
  pinMode(j1_sel_pin, INPUT);
  pinMode(j2_sel_pin, INPUT);

  // Blink to indicate setup complete
  blocking_blink_n(rx_led_pos_pin, 100, 50, 5);

  Serial.print("Joy Node ");
  Serial.print(MYNODEID, DEC);
  Serial.println(" ready");
}

void loop() {
  static char sendbuffer[62];
  static int sendlength = 0;
  JoyMsg msg;
  msg.v1 = 0;
  msg.h1 = 0;
  msg.v2 = 0;
  msg.h2 = 0;

  readMsg(&msg);
  send((char *)&msg, sizeof(JoyMsg));
  delay(100);
}
