## 🧠 System Architecture & Control 
polished_readme = """# 🤖 Autonomous 4WD Obstacle Avoidance Robot

An elegant, production-ready implementation of an autonomous 4-wheel-drive robotic platform engineered with an **Arduino Uno**, an **Adafruit Motor Shield (L293D)**, and a precision **HC-SR04 Ultrasonic Distance Sensor**. The system dynamically measures localized environment clearances, processes path spatial hazards in real time, and executes reactive escape subroutines completely independent of human telemetry.

Developed as an academic research prototype at **Air University**.

---

## 📌 Technical Overview
Obstacle detection and dynamic route reconfiguration serve as foundational building blocks for mobile robotics, unmanned aerial systems (UAVs), and full-scale autonomous vehicles. This project establishes an automated navigation loop utilizing high-frequency acoustic waves to gauge object proximity. 

When a front-facing collision boundary is breached ($\le 15\text{ cm}$), the microcontroller interrupts the standard forward-drive trajectory, initiates an explicit multi-step hazard recovery loop (`Halt` $\rightarrow$ `Reverse Vector` $\rightarrow$ `Halt` $\rightarrow$ `Axial Turn`), and resumes environment scanning to establish a clear heading.

---

## 🧠 System Architecture & Control Loop

The robot's underlying processing logic follows a traditional **Sense-Think-Act** architecture loop:
