# Canipulator

Use this repo to test out the functionality of your Canipulator (based on the ESP32-C6 platform).

## Requirements

* PlatformIO

## Setup

1. Connect your CAN buses according to the documentation to your existing CAN networks. Keep in mind that you may need to solder jumpers for the terminating resistors if your CAN network does not already have terminating resistors.
2. Flash the code `platformio run -t upload` or use the Upload and Monitor option from the Project Tasks panel of the PlatformIO extension. If there's no existing CAN traffic, you'll see a red LED illuminate.
3. Send messages on your CAN0 network - the green LED should light up.
4. Send messages on your CAN1 network - the blue LED should light up.
