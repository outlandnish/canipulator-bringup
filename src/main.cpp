#include <Arduino.h>
#include <SmartLeds.h>
#include <esp32_can.h>

const int LED_COUNT = 1;
const int DATA_PIN = 8;
const int CHANNEL = 0;

SmartLed leds(LED_WS2812B, LED_COUNT, DATA_PIN, CHANNEL, DoubleBuffer);

#define CAN0_SHUTDOWN 3
#define CAN0_STANDBY 0

#define CAN1_SHUTDOWN 2
#define CAN1_STANDBY 1

void setup() {
  Serial.begin(115200);

  // setup status LED
  leds[0] = Rgb { 255, 0, 0 };
  leds.show();
  leds.wait();

  // setup CAN pins
  pinMode(CAN0_SHUTDOWN, OUTPUT);
  pinMode(CAN0_STANDBY, OUTPUT);

  // enable CAN0 transceiver
  digitalWrite(CAN0_SHUTDOWN, LOW);
  digitalWrite(CAN0_STANDBY, LOW);

  pinMode(CAN1_SHUTDOWN, OUTPUT);
  pinMode(CAN1_STANDBY, OUTPUT);

  // enable CAN1 transceiver
  digitalWrite(CAN1_SHUTDOWN, LOW);
  digitalWrite(CAN1_STANDBY, LOW);

  // setup CAN buses
  CAN0.begin(500000);
  CAN1.begin(500000);

}

auto lastCan0Frame = 0;
auto lastCan1Frame = 0;

void loop() {
  // check for can messages on each bus
  CAN_FRAME frame;
  if (CAN0.available() && CAN0.read(frame)) {
    // print out bus and frame
    Serial.printf("CAN0 - ID: %08X, DLC: %d, Data: %02X %02X %02X %02X %02X %02X %02X %02X\n",
             frame.id, frame.length, frame.data.byte[0], frame.data.byte[1], frame.data.byte[2], frame.data.byte[3],
             frame.data.byte[4], frame.data.byte[5], frame.data.byte[6], frame.data.byte[7]);
    lastCan0Frame = millis();
  }
  
  if (CAN1.available() && CAN1.read(frame)) {
    // print out bus and frame
    Serial.printf("CAN1 - ID: %08X, DLC: %d, Data: %02X %02X %02X %02X %02X %02X %02X %02X\n",
             frame.id, frame.length, frame.data.byte[0], frame.data.byte[1], frame.data.byte[2], frame.data.byte[3],
             frame.data.byte[4], frame.data.byte[5], frame.data.byte[6], frame.data.byte[7]);
    lastCan1Frame = millis();
  }

  // show green led when receiving CAN0 and blue led when receiving CAN1
  auto now = millis();
  bool showGreen = now - lastCan0Frame < 1000;
  bool showBlue = now - lastCan1Frame < 1000;

  leds[0] = Rgb { showGreen || showGreen ? 0 : 255, showGreen ? 255 : 0, showBlue ? 255 : 0 };
  leds.show();
  leds.wait();
}
