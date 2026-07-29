# Task 4 - Robot Control Panel & Speech Recognition

## Overview

This project involves building a web-based control interface for a robot, combining manual button controls with an Arabic Speech-to-Text feature. The system is connected to a MySQL database to log commands in real-time and is hosted live using InfinityFree.

## Part 1: System Features & Logic

**Control Pad (`index.html`):** Acts as the main user interface. It features directional buttons (Forward, Backward, Left, Right, Stop) and a microphone button. Clicking a direction (e.g., Right arrow) updates the robot's state in the database to execute the corresponding movement.
**Arabic Speech-to-Text:** Integrated Web Speech API configured to listen and respond exclusively to Arabic voice inputs, converting spoken words into actionable text commands.
**Monitor Page (`monitor.html`):** A dedicated response interface that fetches and displays the current state of the robot from the database (e.g., showing "r" and "right"). It also displays a "Last updated" timestamp to track exactly when the command was issued.
**Seamless Navigation:** Users can easily switch between the two interfaces using the "MONITOR ->" link on the control pad and the "<- Back to control pad" link on the monitor page.

## Part 2: Backend & Database Structure

The project utilizes a PHP backend architecture to handle the data flow between the user interface and the database:

**Database Setup:** The `setup.sql` file initializes the required database tables to store the robot's commands.
**Backend Scripts:** 
- `db.php`: Establishes the secure database connection.
- `update_command.php`: Processes incoming HTTP requests from the control pad (button clicks or voice) to update the database.
- `get_state.php`: Retrieves the latest command and timestamp to update the monitor page dynamically.

## Part 3: Interface Previews

**Control Pad Interface:**
![Control Pad](images/control_pad.png)

**Monitor Page Interface:**
![Monitor Page](images/monitor.png)

## Part 4: Source Code & Live Link

- **Live Website:** [Click here to view and test the live project](https://task4.kesug.com/index.html)
- **Source Code Files:**
  - `index.html`
  - `monitor.html`
  - `db.php`
  - `update_command.php`
  - `get_state.php`
  - `setup.sql`
