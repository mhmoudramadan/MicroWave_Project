# MicroWave_Project

[![Status](https://img.shields.io/badge/status-active-success.svg)](https://github.com/mhmoudramadan/MicroWave_Project)[![GitHub Issues](https://img.shields.io/github/issues/mhmoudramadan/MicroWave_Project.svg)](https://github.com/mhmoudramadan/MicroWave_Project/issues)[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/mhmoudramadan/MicroWave_Project.svg)](https://github.com/mhmoudramadan/MicroWave_Project/pulls)[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/mhmoudramadan/MicroWave_Project/blob/master/LICENSE.md)

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project implements a microwave system based on the ATmega32 microcontroller. It features a keypad for entering heating time, an LCD for displaying the time, and various buttons for start, cancel, door sensor, and weight sensor functionalities.

## Features

- **Keypad Input**: Allows users to enter heating time.
- **LCD Display**: Shows the time setting.
- **Control Buttons**: Includes start and cancel buttons.
- **Sensors**: Integrates door and weight sensors represented as push buttons.

## Repository Structure

- **HAL/**: Hardware Abstraction Layer.
- **MCAL/**: Microcontroller Abstraction Layer.
- **MICROWAVE/**: Application-specific files.
- **simulation/**: Simulation files for testing the system.
- **main.c**: Main application code.

## Getting Started

### Prerequisites

- ATmega32 microcontroller.
- Keypad, LCD, and push buttons for sensors.
- Development environment with AVR-GCC and AVRDude.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/mhmoudramadan/MicroWave_Project.git
   ```


## Configuration

Modify the configuration parameters in the source code files to customize the system settings as needed.

## Contributing

Contributions are welcome! Please submit pull requests or open issues to help improve this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.
