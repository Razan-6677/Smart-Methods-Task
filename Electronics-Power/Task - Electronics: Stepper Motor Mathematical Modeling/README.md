# Task - Electronics: Stepper Motor Mathematical Modeling

## Overview

This task is about understanding how a stepper motor (NEMA 17) works internally and using math to control its exact speed and timing through an Arduino and an A4988 driver.

## Part 1: Research

A NEMA 17 stepper motor has a step angle of 1.8°, which means one full rotation (360°) needs:

360 / 1.8 = 200 steps

**Full-Step vs Half-Step:** In Full-Step mode, one pulse moves the motor a full 1.8°. In Half-Step mode, the driver switches between energizing one coil and both coils together, so each step becomes half the angle (0.9°). This gives smoother motion and better precision, but it needs double the pulses to cover the same angle.

**Microstepping:** Drivers like the A4988 don't just switch coils on/off, they control the current gradually, which splits every full step into smaller microsteps. Setting Microstep to 1/8 divides each 1.8° step into 8 parts (0.225° per microstep), so a full revolution now needs 1600 steps instead of 200. The motion becomes much smoother but requires a higher pulse rate to keep the same speed.

## Part 2: Calculations

For the required motion (1080° in 2.5 seconds):

**Total steps needed:**
1080 / 1.8 = 600 steps

**Motor speed:**
1080° = 3 full revolutions, so RPM = (3 × 60) / 2.5 = 72 RPM

**Delay between steps:**
2.5 seconds / 600 steps = 0.004166 seconds = 4166.7 microseconds per step

The same logic was applied to the return motion (1080° in 4 seconds), giving 600 steps with a delay of 6666.7 microseconds.

## Part 3: Simulation

Since `delayMicroseconds()` in Arduino doesn't accept decimal values, the timing had to be converted from seconds to microseconds (multiplying by 1,000,000) before dividing it over the number of steps. This way the code doesn't use fixed numbers, it calculates the steps and delay directly from the angle and duration, so it stays connected to the math in Part 2.

The circuit was built and simulated on Wokwi (Arduino Uno → A4988 → NEMA 17). Since Wokwi doesn't have an official separate power source part for VMOT, it was connected to 5V, which is enough to prove the logic (step count and timing) works correctly.

🔗 [Wokwi Simulation](https://wokwi.com/projects/470441622798031873)

## Simulation Preview

![Simulation](./screenshots/preview.png)

## Files

- [code/sketch.ino](code/sketch.ino) — Arduino code for the stepper motor motion

## References

- [NEMA 17 Stepper Motor Datasheet](https://components101.com/motors/nema17-stepper-motor)
