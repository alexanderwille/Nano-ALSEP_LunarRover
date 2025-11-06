// ArduinoTestCode_v2.0.cpp
// Attempts remote control of rover

#include <Arduino.h>

// Global Variable and Constant Definitions
    // Pin Definitions
        // Motors
        const int leftMotor_pin_enable = 9; // PWM enable pins for left and right motors
        const int rightMotor_pin_enable = 10;

        const int leftMotor_pin_input1 = 2; // Input control pins for left and right motors
        const int leftMotor_pin_input2 = 3;
        const int rightMotor_pin_input1 = 4;
        const int rightMotor_pin_input2 = 5;

        // RC
        const int rc_pin_throttle = 6;
        const int rc_pin_turn = 7;
    //

    // Speed and input settings and restrictions
    const int rc_pulse_min = 1000;
    const int rc_pulse_avg = 1500; 
    const int rc_pulse_max = 2000;
    const int motor_speed_max = 30;

    const int rc_deadband = 50;
//

// Reads the RC's channel values
int rcChannel_in(int rc_pin) {
    return pulseIn(rc_pin, HIGH, 25000);
}

// Function to set motor speeds and directions based on input values
void set_motor_speed(int pin_enable, int pin_input1, int pin_input2, int speed) {
    int absSpeed = abs(speed);
    int pwmValue = map(absSpeed, 0, motor_speed_max, 0, 255); // Map speed to the input, the set max and min, and PWM range max (255)

    if (speed > 0) { // Forward
        digitalWrite(pin_input1, HIGH);
        digitalWrite(pin_input2, LOW);
    } else if (speed < 0) { // Backward
        digitalWrite(pin_input1, LOW);
        digitalWrite(pin_input2, HIGH);
    } else { // Stop
        digitalWrite(pin_input1, LOW);
        digitalWrite(pin_input2, LOW);
    }

    analogWrite(pin_enable, pwmValue); // Set the motor speed using PWM
}

void rc2motor_converter(int throttle_input, int turn_input) {
    // Checks if either input channel has lost connection (no inputs will return 1500, a lost connection returns 0)
    if ( throttle_input == 0 || turn_input == 0 ) {
        set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, 0);
        set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, 0);
        Serial.println("Connection to controller lost on one or both channels. Shutting down motors and system.");
        return; 
    }

    // Applies deadband constant (prevents drifting or humming when no turn is set)
    if ( abs(throttle_input - rc_pulse_avg) < rc_deadband ) {
        throttle_input = rc_pulse_avg;
    }
    if ( abs(turn_input - rc_pulse_avg) < rc_deadband ) {
        turn_input = rc_pulse_avg;
    }

    // Normalize RC inputs to motor speed range
    int throttle = map(throttle_input, rc_pulse_min, rc_pulse_max, -motor_speed_max, motor_speed_max);
    int turn = map(turn_input, rc_pulse_min, rc_pulse_max, -motor_speed_max, motor_speed_max);

    // Calculate individual motor speeds
    int leftMotor_speed = throttle - turn;
    int rightMotor_speed = throttle + turn;

    // Constrain motor speeds to valid range
    leftMotor_speed = constrain(leftMotor_speed, -motor_speed_max, motor_speed_max);
    rightMotor_speed = constrain(rightMotor_speed, -motor_speed_max, motor_speed_max);

    // Set motor speeds
    set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, leftMotor_speed);
    set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, rightMotor_speed);

    // Test output for throttle and turn outputs
    Serial.print("Throttle Input: ");
    Serial.print(throttle_input);
    Serial.print(", Turn Input: ");
    Serial.println(turn_input);
    Serial.print("Left Motor Speed: ");
    Serial.print(leftMotor_speed);
    Serial.print(", Right Motor Speed: ");
    Serial.println(rightMotor_speed);
}

// Sets up pins for motors, sets first speed as zero
void setup() {
    Serial.begin(9600); // Initialize serial communication

    // Intialize rc pins as inputs, motor pins as outputs
    pinMode(rc_pin_throttle, INPUT);
    pinMode(rc_pin_turn, INPUT);

    pinMode(leftMotor_pin_enable, OUTPUT);
    pinMode(rightMotor_pin_enable, OUTPUT);
    pinMode(leftMotor_pin_input1, OUTPUT);
    pinMode(leftMotor_pin_input2, OUTPUT);
    pinMode(rightMotor_pin_input1, OUTPUT);
    pinMode(rightMotor_pin_input2, OUTPUT);

    
    // Set initial speeds to 0
    set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, 0);
    set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, 0);

}

// 
void loop() {
    int throttle = rcChannel_in(rc_pin_throttle);
    int turn = rcChannel_in(rc_pin_turn);

    rc2motor_converter(throttle, turn);
    delay(100);
}