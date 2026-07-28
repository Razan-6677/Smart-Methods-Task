# Task 4 - Electro'nics: ESP32 Web Server Servo Control

## Overview

This task demonstrates how to control a Servo motor and LED indicators via a web interface hosted on an ESP32 configured as a WiFi Access Point (AP).

## Part 1: Implementation Approach

**Hardware over Simulation:** The initial requirement was to simulate the project on Wokwi. However, because simulating ESP32 WiFi gateway features requires a premium subscription on the platform, the project was directly built and tested on real physical hardware instead.

## Part 2: Hardware Setup

**Components Used:** ESP32, Servo Motor, Red LED, Green LED, Resistors, and a Breadboard.

**System States:**
**Open State:** The Servo rotates to 90 degrees, the Green LED turns ON, and the Red LED turns OFF.
**Closed State:** The Servo returns to 0 degrees, the Red LED turns ON, and the Green LED turns OFF.

## Part 3: Web Server Configuration

**Access Point:** The ESP32 is programmed to broadcast a local WiFi network named "Razan".

**Web Interface:** Connecting to this network and navigating to the assigned IP address loads an HTML web page with "Open" and "Close" buttons. Pressing these buttons sends HTTP GET requests (`/open` or `/close`) to trigger the hardware states in real-time.

## Part 4: Project Media & Code

**Physical Setup:**
![Hardware Setup](images/hardware.png)

**Web Interface Preview:**
![Web Interface](images/website.png)

**Source Code:** [Code/server.ino](Code/server.ino)
