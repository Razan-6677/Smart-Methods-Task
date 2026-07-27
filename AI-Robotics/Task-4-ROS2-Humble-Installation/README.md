# Task 4 - ROS 2 Humble Installation

## Overview

This task documents the step-by-step process of installing ROS 2 Humble Hawksbill on Windows using the Windows Subsystem for Linux (WSL) with Ubuntu 22.04.

## Part 1: WSL & Ubuntu Setup

**Open PowerShell:** Run Windows PowerShell as Administrator.

**Install WSL:** `wsl --install`

**Install Ubuntu 22.04:** `wsl --install -d Ubuntu-22.04`

**Restart:** Restart the computer after the installation is complete.

## Part 2: Install ROS 2 Humble

Once Ubuntu 22.04 is set up and running, the following commands were executed in the Ubuntu terminal:

**Update and upgrade the system:** `sudo apt update && sudo apt upgrade -y`

**Install dependencies:** `sudo apt install software-properties-common curl -y`

**Add the ROS 2 GPG key:** `sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg`

**Add the ROS 2 repository:** `echo "deb [arch=amd64 signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu jammy main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null`

**Update repositories again:** `sudo apt update`

**Install the ROS 2 Humble desktop package:** `sudo apt install ros-humble-desktop -y`

## Part 3: Environment Setup & Verification

To ensure ROS 2 commands work in every new terminal, the setup script must be sourced.

**Source setup script:** `echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc` followed by `source ~/.bashrc`

**Verify installation:** `ros2 --version`

**Check active distribution:** `echo $ROS_DISTRO` (This outputs `humble`)

## Part 4: Troubleshooting

**Error Encountered:** Faced two main issues. First, running `wsl --install` returned an `ERROR_ALREADY_EXISTS` because WSL was already installed. Second, running Linux commands like `sudo apt install ros-humble-desktop` directly in Windows PowerShell resulted in a `CommandNotFoundException`.

**Solution:** The issue was resolved by directing the commands to the correct Ubuntu environment instead of Windows.

**Access Ubuntu:** Switched to the Linux environment via PowerShell by running `wsl -d Ubuntu-22.04`.

**Verify ROS Installation:** Inside Ubuntu, executed `sudo apt install ros-humble-desktop`, which confirmed that the ROS Humble package was already installed and updated to the latest version.

**Environment Setup (Sourcing):** To ensure the system permanently recognizes ROS commands, the path was linked to the terminal configuration by running `echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc` followed by `source ~/.bashrc`.

**Final Result:** The `ros2` command was successfully recognized by the system, confirming that the ROS 2 Humble environment is ready for use.
