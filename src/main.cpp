#include <Arduino.h>

// Constants for pins
#define MOTOR_ENABLE_PIN_1 2
#define MOTOR_TERMINAL_1 3
#define MOTOR_TERMINAL_2 4
#define MOTOR_TERMINAL_3 5
#define MOTOR_TERMINAL_4 6
#define MOTOR_ENABLE_PIN_2 7
#define GREEN_LED 8
#define BLUE_LED 9
#define RED_LED 10
#define IR_SENSOR_PIN 11
#define ULTRASONIC_ECHO_PIN 12
#define ULTRASONIC_TRIG_PIN 13

// Constants for ultrasonic sensor and threshold
#define BASKET_FULL_THRESHOLD_CM 10.0
#define US_DELAY_SHORT 2
#define US_DELAY_LONG 10

// Global state variables
bool isShredding = false;
bool isBasketFull = false;

// Helper function to calculate distance using ultrasonic sensor
float getUltrasonicDistance() {
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(US_DELAY_SHORT);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(US_DELAY_LONG);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    long duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
    return duration * 0.034 / 2; // Calculate distance in cm
}

// Turn on the shredding indicator light
void turnOnShreddingLight() {
    digitalWrite(BLUE_LED, HIGH);
    isShredding = true;
}

// Turn off the shredding indicator light
void turnOffShreddingLight() {
    digitalWrite(BLUE_LED, LOW);
    isShredding = false;
}


void turnOnGreenLight() {
    digitalWrite(GREEN_LED, HIGH);
}

void turnOffGreenLight() {
    digitalWrite(GREEN_LED, LOW);
}

// Check if paper is detected
bool isPaperDetected() {
    return digitalRead(IR_SENSOR_PIN) == LOW;
}

// Alert when the basket is full
void alertBasketFull() {
    digitalWrite(RED_LED, HIGH);
    isBasketFull = true;
    turnOffGreenLight();
}

void alertBasketEmpty() {
    digitalWrite(RED_LED, LOW);
    isBasketFull = false;
}

// Check if the paper basket is full
void checkBasketFullness() {
    float distance = getUltrasonicDistance();
    if (distance < BASKET_FULL_THRESHOLD_CM) {
        alertBasketFull();
    } else {
        alertBasketEmpty();
    }
}

// Turn on the shredder motors
void turnOnShredding() {
    // Motor 1 spins in one direction
    turnOffGreenLight();
    isShredding = true;
    digitalWrite(MOTOR_TERMINAL_1, HIGH);
    digitalWrite(MOTOR_TERMINAL_2, LOW);
    analogWrite(MOTOR_ENABLE_PIN_1, 255);

    digitalWrite(MOTOR_TERMINAL_3, LOW);
    digitalWrite(MOTOR_TERMINAL_4, HIGH);
    analogWrite(MOTOR_ENABLE_PIN_2, 255);

    turnOnShreddingLight();
}

// Stop the shredder motors
void stopShredding() {
    // Stop Motor 1
    digitalWrite(MOTOR_TERMINAL_1, LOW);
    digitalWrite(MOTOR_TERMINAL_2, LOW);

    // Stop Motor 2
    digitalWrite(MOTOR_TERMINAL_3, LOW);
    digitalWrite(MOTOR_TERMINAL_4, LOW);

    // Turn off shredding indicator
    turnOffShreddingLight();
    checkBasketFullness();
}

// Arduino setup function
void setup() {
    // Initialize LED pins
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    // Initialize motor enable pin
    pinMode(MOTOR_ENABLE_PIN_1, OUTPUT);
    pinMode(MOTOR_ENABLE_PIN_2, OUTPUT);

    // Initialize motor pins for Motor 1
    pinMode(MOTOR_TERMINAL_1, OUTPUT);
    pinMode(MOTOR_TERMINAL_2, OUTPUT);

    // Initialize motor pins for Motor 2
    pinMode(MOTOR_TERMINAL_3, OUTPUT);
    pinMode(MOTOR_TERMINAL_4, OUTPUT);

    // Initialize IR sensor pin
    pinMode(IR_SENSOR_PIN, INPUT);

    // Initialize ultrasonic sensor pins
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);

    checkBasketFullness();
}

/**
 * @brief Main control loop for paper shredding and basket monitoring system.
 *
 * This function handles the primary logic for a paper shredder operation, including:
 * - Checking if the basket is full and taking appropriate action to monitor its fullness.
 * - Detecting the presence of paper using an infrared sensor and starting the shredding process if paper is detected.
 * - Stopping the shredding operation when no paper is detected.
 * - Activating a green indicator light when the shredder is idle and the basket is not full.
 *
 * The loop prioritizes ensuring the basket's fullness status is continuously managed, and the system
 * transitions smoothly between shredding, idle, and full states.
 *
 * Pre-conditions:
 * - Sensor and motor pins are initialized.
 * - The system global variables `isShredding` and `isBasketFull` manage state tracking.
 *
 * Post-conditions:
 * - The appropriate indicator lights and motors are activated based on the system's state.
 *
 * This function should be called repeatedly to maintain the operation of the shredder.
 */
void loop() {
    if (isBasketFull) {
        checkBasketFullness();
        return;
    }

    if (isPaperDetected()) {
        if (!isShredding) {
            turnOnShredding();
        }
    } else {
        if (isShredding) {
            stopShredding();
        } else {
            turnOnGreenLight();
        }
    }
}
