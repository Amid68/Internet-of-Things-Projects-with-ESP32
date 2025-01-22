# ESP32 Blinking

![Setup](./setup.png)

## Overview
This project demonstrates sequential LED blinking on an ESP32 microcontroller. Three LEDs cycle in order with 1-second intervals using FreeRTOS tasks.

## Features
- Sequential activation of 3 LEDs
- 1-second interval between LED changes
- FreeRTOS-based task management

## Hardware Requirements
- ESP32 development board
- 3x LEDs
- 3x 220Ω resistors
- Breadboard and jumper wires

## Connections
| ESP32 GPIO | Component |
|------------|-----------|
| GPIO25     | LED1 (+)  |
| GPIO26     | LED2 (+)  |
| GPIO27     | LED3 (+)  |
| GND        | LEDs (-)  |

## Installation & Usage
1. Clone repository:
```bash
git clone https://github.com/Amid68/Internet-of-Things-Projects-with-ESP32.git
cd blinking
```

2. Configure ESP-IDF environment:
```bash
source $HOME/esp/esp-idf/export.sh
```

3. Build and flash:
```bash
idf.py build
idf.py flash monitor
```

4. Exit monitor: `Ctrl+]`