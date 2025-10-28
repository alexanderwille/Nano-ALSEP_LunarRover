#include <iostream>
#include <string>
#include <thread>

// Global Variable and Constant Definitions
    // Motor speed settings
    int stopSpeed = 0;
    int slowSpeed = 5;
    int normalSpeed = 15;
    int fastSpeed = 30;

    // Pausing time settings (in milliseconds)
    int defaultStopTime = 1000;
    int endStopTime = 5000;
    int endOfSimulationTime = 0;
//

// Function to simulate and display the motor inputs for a turn
void simulate_turn(const std::string turn_type, int left_motor_speed, int right_motor_speed) {
    std::this_thread::sleep_for(std::chrono::seconds(defaultStopTime));

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Turn type: " << turn_type << std::endl;
    std::cout << "Left motor input: " << left_motor_speed << std::endl;
    std::cout << "Right motor input: " << right_motor_speed << std::endl;
    
    // Provide a brief explanation of the physical movement
    if (left_motor_speed > stopSpeed && right_motor_speed > stopSpeed) {
        std::cout << "Result: The rover moves **forward**, with a greater speed difference causing a sharper turn." << std::endl;
    } else if (left_motor_speed < stopSpeed && right_motor_speed < stopSpeed) {
        std::cout << "Result: The rover moves **backward**, with a greater speed difference causing a sharper turn." << std::endl;
    } else if ((left_motor_speed > stopSpeed && right_motor_speed < stopSpeed) || (left_motor_speed < 0 && right_motor_speed > 0)) {
        std::cout << "Result: The rover spins" << std::endl;
    } else if (left_motor_speed == stopSpeed && right_motor_speed == stopSpeed) {
        std::cout << "Result: The rover turns around the left wheel" << std::endl;
    } else {
        std::cout << "Result: The rover moves straight or is stopped" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(defaultStopTime));
}

// Stops both motors for a specified time
void simulate_dead_stop(int timeStop) {
    int left_motor_speed = stopSpeed;
    int right_motor_speed = stopSpeed;
    std::this_thread::sleep_for(std::chrono::seconds(timeStop));
}

// Runs the simulation
void main() {
    std::cout << "Two-Wheeled Rover Turning Simulation" << std::endl;
    std::cout << "Motor input range is assumed to be -30 (full reverse) to 30 (full forward)" << std::endl;

    // Straight Movement (Both motors move in the same direction at the same rate) //
    // Straight Forward
    simulate_turn("Forward Straight", normalSpeed, normalSpeed);
    simulate_dead_stop(defaultStopTime);
    
    // Straight Backward
    simulate_turn("Backward Straight", -normalSpeed, -normalSpeed);
    simulate_dead_stop(defaultStopTime);

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    simulate_dead_stop(endStopTime);
    


    // Slow Turns/Arcs (One motor is slower than the other) //
    // Arcs forward right
    simulate_turn("Slow Right Turn (Forward Arc)", normalSpeed, slowSpeed);
    simulate_dead_stop(defaultStopTime);
    // Arcs forward left
    simulate_turn("Slow Left Turn (Forward Arc)", slowSpeed, normalSpeed);
    simulate_dead_stop(defaultStopTime);
    // Arcs backward right
    simulate_turn("Slow Right Turn (Backward Arc)", -normalSpeed, -slowSpeed);
    simulate_dead_stop(defaultStopTime);
    // Arcs backward left
    simulate_turn("Slow Left Turn (Backward Arc)", -slowSpeed, -normalSpeed);
    simulate_dead_stop(defaultStopTime);
    
    // Dead Stop (Both motors are stationary) // (Safety to end test)
    simulate_dead_stop(endStopTime);



    // Quick Turns/Arcs (One motor turns quickly, the other doesn't move) //
    // Left motor turns forward quickly, right motor is stationary
    simulate_turn("Sharp Right Turn (Forward Arc)", fastSpeed, stopSpeed);
    simulate_dead_stop(defaultStopTime);
    // Right motor turns forward quickly, left motor is stationary
    simulate_turn("Sharp Left Turn (Forward Arc)", stopSpeed, fastSpeed);
    simulate_dead_stop(defaultStopTime);
    // Left motor turns backward quickly, right motor is stationary
    simulate_turn("Sharp Right Turn (Reverse Arc)", -fastSpeed, stopSpeed);
    simulate_dead_stop(defaultStopTime);
    // Right motor turns backward quickly, left motor is stationary
    simulate_turn("Sharp Left Turn (Reverse Arc)", stopSpeed, -fastSpeed);
    simulate_dead_stop(defaultStopTime);

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    simulate_dead_stop(endStopTime);



    // Spinning in Place (Motors move in opposite directions at the same rates) //
    // Spin clockwise (left forward, right backward)
    simulate_turn("Spin Left in Place (Clockwise)", normalSpeed, -normalSpeed);
    simulate_dead_stop(defaultStopTime);
    // Spin counter-clockwise (left backward, right forward)
    simulate_turn("Spin Right in Place (Counter-Clockwise)", -normalSpeed, normalSpeed);
    simulate_dead_stop(defaultStopTime);

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    simulate_dead_stop(endOfSimulationTime);
}