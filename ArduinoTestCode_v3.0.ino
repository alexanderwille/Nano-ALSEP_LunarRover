// ArduinoTestCode_v3.0
// Scaled down rover operated by IR remote instead of RC

#include <Arduino.h>
#include <IRremote.hpp>

// Global Variable and Constant Definitions
    // Pin Definitions
        // Motors
        const int leftMotor_pin_enable = 6; // PWM enable pins for left and right motors
        const int rightMotor_pin_enable = 5;

        const int leftMotor_pin_input1 = 8; // Input control pins for left and right motors
        const int leftMotor_pin_input2 = 7;
        const int rightMotor_pin_input1 = 4;
        const int rightMotor_pin_input2 = 2;

        // IR Remote
        const int ir_pin_input = 11;
    //

    // Speed and input settings and restrictions
    const int driveSpeed = 200;
//

// Function to set motor speeds and directions based on input values
void set_motor_speed(int pin_enable, int pin_input1, int pin_input2, int speed) {
    int absSpeed = abs(speed);
    
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

    analogWrite(pin_enable, absSpeed); // Set the motor speed
}

void setup() {
    Serial.begin(9600); // Initialize serial communication

    // Intialize IR receiver pin as an input and the motor pins as outputs
    IrReceiver.begin(ir_pin_input, ENABLE_LED_FEEDBACK);
    pinMode(leftMotor_pin_enable, OUTPUT);
    pinMode(rightMotor_pin_enable, OUTPUT);
    pinMode(leftMotor_pin_input1, OUTPUT);
    pinMode(leftMotor_pin_input2, OUTPUT);
    pinMode(rightMotor_pin_input1, OUTPUT);
    pinMode(rightMotor_pin_input2, OUTPUT);
}

// 
void loop() {
    if(IrReceiver.decode()) {
        unsigned long command = IrReceiver.decodedIRData.command; // Gets the command based on the button pressed, then prints it
        Serial.print("IR Command Received: ");
        Serial.println(command, HEX);

        switch(command) { // Adjusts motors based on input
            case 0x46: // Forward
                set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, -driveSpeed);
                set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, driveSpeed);
                Serial.println("Moving forward...");
                break;
            case 0x15: // Backward
                set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, driveSpeed);
                set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, -driveSpeed);
                Serial.println("Moving backwards...");
                break;
            case 0x44: // Rotate left
                set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, driveSpeed);
                set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, driveSpeed);
                Serial.println("Turning left...");
                break;
            case 0x43: // Rotate right
                set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, -driveSpeed);
                set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, -driveSpeed);
                Serial.println("Turning right...");
                break;
            case 0x40: // OK/Stop
                set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, 0);
                set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, 0);
                Serial.println("Stopping...");
                break;
        }
        IrReceiver.resume(); // Gets the next input
    }
}