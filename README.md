# ESP32 Bluetooth Controlled Robot Car

## Project Description
This project is designed to control a robot car using an ESP32 development board and the Dabble Bluetooth GamePad application.

The ESP32 receives commands from a smartphone through Bluetooth and controls two DC motors using the L298N motor driver.

## Components Required
- ESP32 Development Board
- L298N Motor Driver
- 2 DC Motors
- Robot Car Chassis
- Battery
- Smartphone
- Dabble Mobile Application

## Pin Connections

| ESP32 GPIO | L298N |
|---|---|
| GPIO 22 | ENA |
| GPIO 26 | IN1 |
| GPIO 27 | IN2 |
| GPIO 23 | ENB |
| GPIO 18 | IN3 |
| GPIO 19 | IN4 |

## Features
- Bluetooth communication
- Forward movement
- Backward movement
- Left turn
- Right turn
- PWM-based motor speed control

## Software Requirements
- Arduino IDE
- ESP32 Board Package
- DabbleESP32 Library

## Bluetooth Device Name
`MyBluetoothCar`

## Working Principle
1. Connect the smartphone to the ESP32 using the Dabble application.
2. Press the GamePad buttons.
3. ESP32 receives the commands through Bluetooth.
4. ESP32 controls the L298N motor driver.
5. Motors rotate according to the selected direction.

## Programming Language
C
