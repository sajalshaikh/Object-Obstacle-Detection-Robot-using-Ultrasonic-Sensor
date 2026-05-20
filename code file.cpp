/**
 * @file Obstacle_Avoidance.cpp
 * @brief 4WD Autonomous Navigation & Obstacle Avoidance Firmware
 * @author Sajal Saeed
 * @version 2.0.0
 */

#include <AFMotor.h>

// I/O Peripheral Hardware Mappings
#define TRIG_PIN A1
#define ECHO_PIN A4

// System Performance Parameters
#define MOTOR_SPEED 160     // Operational PWM duty cycle (0-255)
#define OBSTACLE_LIMIT 15   // Critical proximity boundary in centimeters

// Instantiate H-Bridge DC Motor Actuators
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
  // Initialize hardware UART serial telemetry link
  Serial.begin(9600);
  Serial.println(F("[SYSTEM LOG] Booting Navigation Controller Core v2.0.0..."));
  
  // Set explicit pin directions for ultrasonic transceiver
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Configure internal PWM timer frequencies for motor channels
  motor1.setSpeed(MOTOR_SPEED);
  motor2.setSpeed(MOTOR_SPEED);
  motor3.setSpeed(MOTOR_SPEED);
  motor4.setSpeed(MOTOR_SPEED);
  
  Serial.println(F("[SYSTEM LOG] Subsystems status: OK. Running scan loop."));
}

void loop() {
  int distance = getDistance();
  
  // Stream telemetry parameters to serial monitor
  Serial.print(F("Ranging Data: "));
  Serial.print(distance);
  Serial.println(F(" cm"));

  // Evaluate collision boundary thresholds
  if (distance > 0 && distance <= OBSTACLE_LIMIT) {
    Serial.println(F("[ALERT] Critical Proximity Breached. Executing Hazard Escape Loop."));
    
    // Step 1: Structural Emergency Brake
    moveStop();
    delay(500);
    
    // Step 2: Clear Turning Radius
    Serial.println(F("[ACTION] Disengaging forward path... Reversing vector."));
    moveBackward();
    delay(600);
    moveStop();
    delay(300);
    
    // Step 3: Pivot Orientation Axial Right
    Serial.println(F("[ACTION] Rotating spatial frame clockwise..."));
    turnRight();
    delay(600);
    moveStop();
    delay(300);
  } 
  else {
    // Nominal operational forward routing
    moveForward();
  }
  
  delay(50); // Transient signal settling gap
}

/**
 * @brief Computes ambient distance by analyzing acoustic wave propagation.
 * @return Integrated integer distance measurement in centimeters.
 */
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Capture high logic timing pulse with a fixed 30ms guard timeout
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
  
  if (duration == 0) {
    return 999; // Yield out-of-bounds ceiling value if signal drops
  }
  
  return (int)(duration / 29 / 2); 
}

// --- Lower-Level H-Bridge Commutation Subroutines ---

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}