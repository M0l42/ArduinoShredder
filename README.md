# Project Title: Paper Shredder Automation with Arduino

## Description

This project implements a paper shredder automation system using an Arduino microcontroller. The system features automatic detection of paper, shredding functionality, and safety mechanisms like basket-full detection. It uses various sensors and indicators to provide an efficient and user-friendly experience.

## Features

1. **Automatic Paper Detection**:
    - An IR sensor detects when paper is inserted into the shredder.
    - Initiates shredding automatically when paper is detected.

2. **Shredding Mechanism**:
    - Two DC motors operate the shredding mechanism.
    - Motors are controlled using enable pins and directional terminals to manage the rotation.

3. **Basket Full Detection**:
    - An ultrasonic sensor detects the fullness of the paper basket.
    - A red LED indicates when the basket is full, stopping the shredder for safety.

4. **Status Indicators**:
    - **Green LED**: Indicates readiness for shredding.
    - **Blue LED**: Indicates the shredding process is active.
    - **Red LED**: Alerts when the basket is full.

5. **Safety Features**:
    - Stops shredding when the basket is full or there is no paper detected.

## Components Used

1. **Arduino Board**
2. **IR Sensor**:
    - Detects the presence of paper.
3. **Ultrasonic Sensor**:
    - Measures the distance to detect if the basket is full.
4. **DC Motors**:
    - Operate the shredder mechanism.
5. **LED Indicators**:
    - Green, Blue, and Red LEDs for status indication.
6. **Power Supply**
7. **Connecting Wires and Resistors**

## Pin Configuration

| **Component**         | **Arduino Pin**       |
|-----------------------|---------------------|
| Motor Terminal 1      | 2                   |
| Motor Terminal 2      | 3                   |
| Motor Terminal 3      | 4                   |
| Motor Terminal 4      | 5                   |
| Motor Enable Pin 1    | 6                   |
| Motor Enable Pin 2    | 7                   |
| IR Sensor Pin         | 11                  |
| Ultrasonic Echo Pin   | 12                  |
| Ultrasonic Trigger Pin| 13                  |
| Green LED             | 8                   |
| Blue LED              | 9                   |
| Red LED               | 10                  |

## Functionality Overview

### 1. **Shredding Process**
- When paper is detected by the IR sensor, the motors are activated to shred the paper.
- A blue LED lights up to indicate shredding is in progress.
- When shredding is complete or no paper is detected, the shredder stops, and the green LED turns on for standby mode.

### 2. **Basket Full Detection**
- The ultrasonic sensor continuously measures the distance to determine if the basket is near full.
- A threshold of 10 cm distance is used. If the distance is less than the threshold, the basket is marked as full.
- The red LED turns on, and shredding stops until the basket is emptied.

### 3. **Indicators**
- **Green LED**: On when the shredder is ready.
- **Blue LED**: On when shredding is occurring.
- **Red LED**: On when the paper basket is full.

## Arduino Code Overview

The code controls the entire system, performing the following tasks:

1. **Setup**:
    - Configures pin modes for LEDs, motors, and sensors.
    - Initializes all devices and starts with a basket-fullness check.

2. **IR Sensor**:
    - Detects the presence of paper and triggers the shredding process.

3. **Ultrasonic Sensor**:
    - Measures the distance to the basket and determines whether it is full.

4. **Shredding Control**:
    - Functions control the motors for shredding and turning on/off the indicators.

5. **Safety Handling**:
    - Stops shredding when the basket is full or no paper is detected.

6. **Loop**:
    - Continuously checks the state of the IR sensor for paper detection or ultrasonic sensor for basket fullness. It adjusts the shredder and indicator LEDs accordingly.

## How to Run the System

1. **Hardware Setup**:
    - Assemble the components as per the pin configuration table.
    - Connect the motors and power supply to the Arduino board.

2. **Upload Code**:
    - Upload the provided Arduino code to the microcontroller using the Arduino IDE.

3. **Operation**:
    - Power on the system.
    - Insert paper into the shredder. IR detection will initiate shredding automatically.
    - The ultrasonic sensor will monitor the basket fullness, and the system will stop shredding if the basket is full.

4. **Emptying the Basket**:
    - Remove shredded material from the basket to reset the basket-full alert and resume normal operation.

## Enhancements and Future Plans

- Add a buzzer for audio alerts when the basket is full.
- Introduce speed control for the DC motors.
- Integrate a display for status information.
- Incorporate wireless monitoring and control using Bluetooth/Wi-Fi.

## Conclusion

This Arduino project effectively automates a paper shredder with real-time controls and safety mechanisms. It is a robust solution for hands-free paper shredding while ensuring the system remains safe and user-friendly.
