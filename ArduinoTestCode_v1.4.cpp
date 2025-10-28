#include <Arduino.h>

// Global Variable and Constant Definitions
    // Motor pin definitions
    const int leftMotor_pin_enable = 9; // PWM enable pins for left and right motors
    const int rightMotor_pin_enable = 10;

    const int leftMotor_pin_input1 = 2; // Input control pins for left and right motors
    const int leftMotor_pin_input2 = 3;
    const int rightMotor_pin_input1 = 4;
    const int rightMotor_pin_input2 = 5;

    // Motor speed settings
    int stopSpeed = 0;
    int slowSpeed = 5;
    int normalSpeed = 15;
    int fastSpeed = 30;

    // Time settings (in milliseconds)
    int defaultStopTime = 1000; // Pause time
    int endStopTime = 5000;
    int endOfSimulationTime = 0;

    int motor_runTime_1s = 1000; // How long each motor runs
    int motor_runTime_2s = 2000;
    int motor_runTime_3s = 3000;
//

// Function to set motor speeds and directions based on input values
void set_motor_speed(int pin_enable, int pin_input1, int pin_input2, int speed) {
    int absSpeed = abs(speed);

    int pwmValue = map(absSpeed, 0, 30, 0, 255); // Map speed to the input, the set max and min, and PWM range max (255)

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

// Function to simulate and display the motor inputs for a turn
void turn(const char* turnType, int leftMotor_speed, int rightMotor_speed, int runTime) {
    // Provide a brief explanation of the physical movement and motor speeds
    Serial.println("------------------------------------------");
    Serial.print("Turn type: ");
    Serial.println(turnType);
    Serial.print("Left motor input: ");
    Serial.println(leftMotor_speed);
    Serial.print("Right motor input: ");
    Serial.println(rightMotor_speed);

    // Set motor speeds
    set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, leftMotor_speed);
    set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, rightMotor_speed);

    // Runs for the set time
    delay(runTime);

    // Briefly stops before the next action
    stop(2*defaultStopTime);
}

// Stops both motors for a specified time
void stop(int timeStop) {
    set_motor_speed(leftMotor_pin_enable, leftMotor_pin_input1, leftMotor_pin_input2, stopSpeed);
    set_motor_speed(rightMotor_pin_enable, rightMotor_pin_input1, rightMotor_pin_input2, stopSpeed);
    delay(timeStop);
}

// Currently all logic is in setup() because it is just being tested right now. In the future, most will be moved to loop().
// Currently all movements are set to only last for 2 seconds. This will be adjustable in the future.
void setup() {
    Serial.begin(9600); // Initialize serial communication

    // Intialize motor pins as outputs
    pinMode(leftMotor_pin_enable, OUTPUT);
    pinMode(rightMotor_pin_enable, OUTPUT);
    pinMode(leftMotor_pin_input1, OUTPUT);
    pinMode(leftMotor_pin_input2, OUTPUT);
    pinMode(rightMotor_pin_input1, OUTPUT);
    pinMode(rightMotor_pin_input2, OUTPUT);

    // Starts at a stop
    stop(defaultStopTime);
    Serial.println("Two-Wheeled Rover Turning Simulation");
    Serial.println("Motor input range is assumed to be -30 (full reverse) to 30 (full forward)");

    // Straight Movement (Both motors move in the same direction at the same rate)
        // Straight Forward
        turn("Forward Straight", normalSpeed, normalSpeed, motor_runTime_2s);
        // Straight Backward
        turn("Backward Straight", -normalSpeed, -normalSpeed, motor_runTime_2s);

        // Dead Stop (Both motors are stationary) // (Safety to end test)
        stop(endStopTime);
    //
    


    // Slow Turns/Arcs (One motor is slower than the other)
        // Arcs forward right
        turn("Slow Right Turn (Forward Arc)", normalSpeed, slowSpeed, motor_runTime_2s);
        // Arcs forward left
        turn("Slow Left Turn (Forward Arc)", slowSpeed, normalSpeed, motor_runTime_2s);
        // Arcs backward right
        turn("Slow Right Turn (Backward Arc)", -normalSpeed, -slowSpeed, motor_runTime_2s);
        // Arcs backward left
        turn("Slow Left Turn (Backward Arc)", -slowSpeed, -normalSpeed, motor_runTime_2s);
    
        // Dead Stop (Both motors are stationary) // (Safety to end test)
        stop(endStopTime);
    //



    // Quick Turns/Arcs (One motor turns quickly, the other doesn't move)
        // Left motor turns forward quickly, right motor is stationary
        turn("Sharp Right Turn (Forward Arc)", fastSpeed, stopSpeed, motor_runTime_2s);
        // Right motor turns forward quickly, left motor is stationary
        turn("Sharp Left Turn (Forward Arc)", stopSpeed, fastSpeed, motor_runTime_2s);
        // Left motor turns backward quickly, right motor is stationary
        turn("Sharp Right Turn (Reverse Arc)", -fastSpeed, stopSpeed, motor_runTime_2s);
        // Right motor turns backward quickly, left motor is stationary
        turn("Sharp Left Turn (Reverse Arc)", stopSpeed, -fastSpeed, motor_runTime_2s);

        // Dead Stop (Both motors are stationary) // (Safety to end test)
        stop(endStopTime);
    //



    // Spinning in Place (Motors move in opposite directions at the same rates)
        // Spin clockwise (left forward, right backward)
        turn("Spin Left in Place (Clockwise)", normalSpeed, -normalSpeed, motor_runTime_2s);
        // Spin counter-clockwise (left backward, right forward)
        turn("Spin Right in Place (Counter-Clockwise)", -normalSpeed, normalSpeed, motor_runTime_2s);

        // Dead Stop (Both motors are stationary) // (Safety to end test)
        stop(endOfSimulationTime);
    //
}

// loop() is empty because all logic is currently in setup()
void loop() {
    
}