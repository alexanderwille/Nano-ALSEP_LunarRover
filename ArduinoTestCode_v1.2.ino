#include <Arduino.h>

// Global Variable and Constant Definitions
    // Motor pin definitions
    const int left_motor_pin_enable = 9; // PWM enable pins for left and right motors
    const int right_motor_pin_enable = 10;

    const int left_motor_inputPin1 = 2; // Input control pins for left and right motors
    const int left_motor_inputPin2 = 3;
    const int right_motor_inputPin1 = 4;
    const int right_motor_inputPin2 = 5;

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

// Function to simulate and display the motor inputs for a turn
void simulate_turn(const char* turn_type, int left_motor_speed, int right_motor_speed, int runTime) {
    delay(defaultStopTime);

    // Provide a brief explanation of the physical movement and motor speeds
    Serial.println("------------------------------------------");
    Serial.print("Turn type: ");
    Serial.println(turn_type);
    Serial.print("Left motor input: ");
    Serial.println(left_motor_speed);
    Serial.print("Right motor input: ");
    Serial.println(right_motor_speed);

    // Set motor speeds
    set_motor_speed(left_motor_pin_enable, left_motor_inputPin1, left_motor_inputPin2, left_motor_speed);
    set_motor_speed(right_motor_pin_enable, right_motor_inputPin1, right_motor_inputPin2, right_motor_speed);

    // Runs for the set time
    delay(runTime);

    // Briefly stops before the next action
    delay(defaultStopTime);
}

// Function to set motor speeds and directions based on input values
void set_motor_speed(int enablePin, int inputPin1, int inputPin2, int speed) {
    int absSpeed = abs(speed);

    int pwmValue = map(absSpeed, 0, 30, 0, 255); // Map speed to the input, the set max and min, and PWM range max (255)

    if (speed > 0) { // Forward
        digitalWrite(inputPin1, HIGH);
        digitalWrite(inputPin2, LOW);
    } else if (speed < 0) { // Backward
        digitalWrite(inputPin1, LOW);
        digitalWrite(inputPin2, HIGH);
    } else { // Stop
        digitalWrite(inputPin1, LOW);
        digitalWrite(inputPin2, LOW);
    }

    analogWrite(enablePin, pwmValue); // Set the motor speed using PWM
}

// Stops both motors for a specified time
void dead_stop(int timeStop) {
    set_motor_speed(left_motor_pin_enable, left_motor_inputPin1, left_motor_inputPin2, stopSpeed);
    set_motor_speed(right_motor_pin_enable, right_motor_inputPin1, right_motor_inputPin2, stopSpeed);
    delay(timeStop);
}

// Currently all logic is in setup() because it is just being tested right now. In the future, most will be moved to loop().
// Currently all movements are set to only last for 2 seconds. This will be adjustable in the future.
void setup() {
    Serial.begin(9600); // Initialize serial communication

    // Intialize motor pins as outputs
    pinMode(left_motor_pin_enable, OUTPUT);
    pinMode(right_motor_pin_enable, OUTPUT);
    pinMode(left_motor_inputPin1, OUTPUT);
    pinMode(left_motor_inputPin2, OUTPUT);
    pinMode(right_motor_inputPin1, OUTPUT);
    pinMode(right_motor_inputPin2, OUTPUT);

    // Starts at a stop
    dead_stop(defaultStopTime);
    Serial.println("Two-Wheeled Rover Turning Simulation");
    Serial.println("Motor input range is assumed to be -30 (full reverse) to 30 (full forward)");

    // Straight Movement (Both motors move in the same direction at the same rate) //
    // Straight Forward
    simulate_turn("Forward Straight", normalSpeed, normalSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    
    // Straight Backward
    simulate_turn("Backward Straight", -normalSpeed, -normalSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    dead_stop(endStopTime);
    


    // Slow Turns/Arcs (One motor is slower than the other) //
    // Arcs forward right
    simulate_turn("Slow Right Turn (Forward Arc)", normalSpeed, slowSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    // Arcs forward left
    simulate_turn("Slow Left Turn (Forward Arc)", slowSpeed, normalSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    // Arcs backward right
    simulate_turn("Slow Right Turn (Backward Arc)", -normalSpeed, -slowSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    // Arcs backward left
    simulate_turn("Slow Left Turn (Backward Arc)", -slowSpeed, -normalSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    
    // Dead Stop (Both motors are stationary) // (Safety to end test)
    dead_stop(endStopTime);



    // Quick Turns/Arcs (One motor turns quickly, the other doesn't move) //
    // Left motor turns forward quickly, right motor is stationary
    simulate_turn("Sharp Right Turn (Forward Arc)", fastSpeed, stopSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    // Right motor turns forward quickly, left motor is stationary
    simulate_turn("Sharp Left Turn (Forward Arc)", stopSpeed, fastSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    // Left motor turns backward quickly, right motor is stationary
    simulate_turn("Sharp Right Turn (Reverse Arc)", -fastSpeed, stopSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    // Right motor turns backward quickly, left motor is stationary
    simulate_turn("Sharp Left Turn (Reverse Arc)", stopSpeed, -fastSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    dead_stop(endStopTime);



    // Spinning in Place (Motors move in opposite directions at the same rates) //
    // Spin clockwise (left forward, right backward)
    simulate_turn("Spin Left in Place (Clockwise)", normalSpeed, -normalSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);
    // Spin counter-clockwise (left backward, right forward)
    simulate_turn("Spin Right in Place (Counter-Clockwise)", -normalSpeed, normalSpeed, motor_runTime_2s);
    dead_stop(defaultStopTime);

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    dead_stop(endOfSimulationTime);
}

// loop() is empty because all logic is currently in setup()
void loop() {
    
}