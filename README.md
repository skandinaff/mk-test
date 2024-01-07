# README

## Description

This project is designed for the STM32 NUCLEO-L011K4 board. It includes a UART interface for processing specific text commands and controlling LEDs connected to GPIO pins.

## How to build

### Using VS Code Tasks
- Open the project in Visual Studio Code.
- Access the tasks by pressing Ctrl+Shift+P and typing Tasks: Run Task.
- Choose a task to run, such as:
    - Re-build project
    - Clean project
    - Flash project
    - Run CMake configuration


## Build Options

`UART_BAUD_RATE` : Sets the baud rate for UART communication (default: 115200).

`PIN1`, `PIN2`,`PIN3`, `PIN4`: Define the GPIO pins used for LED control.

## Tools Used
- Visual Studio Code: For development with tasks integration.
- CMake: For building the project.
- GNU Arm Embedded Toolchain: Compiler and tools for ARM Cortex-M processors.