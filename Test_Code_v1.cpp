#include <iostream>
#include <string>
#include <thread>

// Function to simulate and display the motor inputs for a turn
void simulate_turn(const std::string turn_type, int left_motor_speed, int right_motor_speed) {
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Turn type: " << turn_type << std::endl;
    std::cout << "Left motor input: " << left_motor_speed << std::endl;
    std::cout << "Right motor input: " << right_motor_speed << std::endl;
    
    // Provide a brief explanation of the physical movement
    if (left_motor_speed > 0 && right_motor_speed > 0) {
        std::cout << "Result: The rover moves **forward**, with a greater speed difference causing a sharper turn." << std::endl;
    } else if (left_motor_speed < 0 && right_motor_speed < 0) {
        std::cout << "Result: The rover moves **backward**, with a greater speed difference causing a sharper turn." << std::endl;
    } else if ((left_motor_speed > 0 && right_motor_speed < 0) || (left_motor_speed < 0 && right_motor_speed > 0)) {
        std::cout << "Result: The rover spins" << std::endl;
    } else if (left_motor_speed == 0 && right_motor_speed == 0) {
        std::cout << "Result: The rover turns around the left wheel" << std::endl;
    } else {
        std::cout << "Result: The rover moves straight or is stopped" << std::endl;
    }
}

int main() {
    std::cout << "Two-Wheeled Rover Turning Simulation" << std::endl;
    std::cout << "Motor input range is assumed to be -30 (full reverse) to 30 (full forward)" << std::endl;

    // Straight Movement (Both motors move in the same direction at the same rate) //
    // Straight Forward
    simulate_turn("Forward Straight", 15, 15);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    // Straight Backward
    simulate_turn("Backward Straight", -15, -15);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(5000));
    


    // Slow Turns/Arcs (One motor is slower than the other) //
    // Arcs forward right
    simulate_turn("Slow Right Turn (Forward Arc)", 15, 5);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    // Arcs forward left
    simulate_turn("Slow Left Turn (Forward Arc)", 5, 15);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    // Arcs backward right
    simulate_turn("Slow Right Turn (Backward Arc)", -15, -5);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    // Arcs backward left
    simulate_turn("Slow Left Turn (Backward Arc)", -5, -15);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    
    // Dead Stop (Both motors are stationary) // (Safety to end test)
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(5000));



    // Quick Turns/Arcs (One motor turns quickly, the other doesn't move) //
    // Left motor turns forward quickly, right motor is stationary
    simulate_turn("Sharp Right Turn (Forward Arc)", 30, 0);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    // Right motor turns forward quickly, left motor is stationary
    simulate_turn("Sharp Left Turn (Forward Arc)", 0, 30);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    // Left motor turns backward quickly, right motor is stationary
    simulate_turn("Sharp Right Turn (Reverse Arc)", -30, 0);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    // Right motor turns backward quickly, left motor is stationary
    simulate_turn("Sharp Left Turn (Reverse Arc)", 0, -30);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(5000));



    // Spinning in Place (Motors move in opposite directions at the same rates) //
    // Spin clockwise (left forward, right backward)
    simulate_turn("Spin Left in Place (Clockwise)", 15, -15);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));
    // Spin counter-clockwise (left backward, right forward)
    simulate_turn("Spin Right in Place (Counter-Clockwise)", -15, 15);
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(1000));

    // Dead Stop (Both motors are stationary) // (Safety to end test)
    simulate_turn("Dead Stop", 0, 0);
    std::this_thread::sleep_for(std::chrono::seconds(5000));


    
    return 0;
}