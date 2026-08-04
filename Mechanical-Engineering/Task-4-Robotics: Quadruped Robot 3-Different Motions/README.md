# Task 4 - Robotics: Quadruped Robot 3-Different Motions

## Overview

This task focuses on programming a 3D-printed quadruped robot dog using an Arduino, a breadboard, and four servo motors. The objective is to execute three distinct mechanical movements, fulfilling the requirements of the robotics training module.

## Part 1: Task Requirements & Motion Logic

The Arduino is programmed with three specific custom functions to demonstrate the robot's mobility and joint coordination:

1. **Forward and Back (`forwardAndBack`):** The legs move in a coordinated sequence to simulate a rocking or stepping motion forward and backward.
2. **Side Tilt (`sideTilt`):** The robot shifts its weight from side to side by adjusting the angles of the opposing legs synchronously.
3. **Happy Dance (`happyDance`):** A rapid, synchronized movement of all four legs to create a bouncing or dancing effect.

## Part 2: Hardware & Wiring Configuration

**Components Used:** Arduino UNO, Breadboard, jumper wires, four servo motors, and the 3D-printed quadruped structure.

**Pin Connections:**
- **Leg 1 Servo:** Connected to Pin **3**
- **Leg 2 Servo:** Connected to Pin **4**
- **Leg 3 Servo:** Connected to Pin **6**
- **Leg 4 Servo:** Connected to Pin **7**

## Part 3: Project Media & Demonstration

**Hardware Wiring Setup:**
![Wiring Setup](Mechanical-Engineering/Task-4-Robotics%3A%20Quadruped%20Robot%203-Different%20Motions/images/robot1.PNG)

**Robot Assembly:**
![Quadruped Robot](Mechanical-Engineering/Task-4-Robotics%3A%20Quadruped%20Robot%203-Different%20Motions/images/robot2.PNG)

**Demo Video:**
- **Watch Robot Motions:** [Click here to view the demonstration video on Google Drive](https://drive.google.com/file/d/1ICXY7mnW7B15XBbFcnFb1aOAXl7vm7C9/view?usp=drivesdk)

## Part 4: Source Code

The complete Arduino source code for the robot's motions is provided in a separate file within this repository.

- **Source Code File:** [Code/robot_motions.ino](Mechanical-Engineering/Task-4-Robotics%3A%20Quadruped%20Robot%203-Different%20Motions/Code/robot_motions.ino)
