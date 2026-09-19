# Autonomous Reconnaissance Rover with Gas and Metal Detection

[![GitHub Repository](https://img.shields.io/badge/GitHub-Repository-00f0ff?style=for-the-badge&logo=github&logoColor=white)](https://github.com/ALWINTR/spybot-metal-and-gas-detection)
[![Developer](https://img.shields.io/badge/Developer-Alwin_T_R-0284c7?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/alwintr)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

An advanced tele-operated multi-terrain reconnaissance rover designed for hazardous search-and-rescue operations, toxic combustible gas leak detection, and buried metal proximity identification in environments hazardous to human personnel.

---

## System Architecture

SpyBot operates using a distributed dual-controller architecture:
1. **Master Wireless Controller (ESP32)**: Manages long-range wireless telemetry reception, streaming video payload, and operator control command decoding.
2. **Real-Time Sensor and Actuation Unit (Arduino Uno)**: Executes high-speed analog ADC sampling of the MQ-2 gas sensor, digital polling of the inductive proximity sensor, and dual H-bridge L298N differential motor drive actuation.
3. **2-DOF Pan-Tilt Camera Gimbal**: Driven by twin SG90 micro-servos enabling full 180 degree horizontal and 90 degree vertical optical field-of-view scanning.

```
                  +------------------------------+
                  |    Operator Wireless Link    |
                  +--------------+---------------+
                                 | Wi-Fi / Serial
                                 v
                  +------------------------------+
                  |   ESP32 Master Controller    |
                  |   - Video Stream & Telemetry |
                  +--------------+---------------+
                                 | UART Telemetry
                                 v
                  +------------------------------+
                  |   Arduino Sub-Controller     |
                  |   - Real-Time ADC & PWM      |
                  +--+-----------+------------+--+
                     |           |            |
       +-------------v--+ +------v------+ +---v------------+
       | MQ-2 Gas Sensor| |Inductive Sen| |Dual L298N Drive|
       | (Combustible)  | |(Metal Proxim| |(Differential)  |
       +----------------+ +-------------+ +----------------+
```

---

## Hardware Bill of Materials (BOM)

| Component | Technical Specification | Functional Role |
| :--- | :--- | :--- |
| **Master Controller** | ESP32-WROOM-32 (240MHz Dual Core) | Wireless video streaming and telemetry communication |
| **Sub-Controller** | Arduino Uno (ATmega328P, 16MHz) | Real-time ADC sensor acquisition and motor PWM |
| **Motor Driver** | L298N Dual H-Bridge Driver Module | Bi-directional DC motor speed and direction |
| **Drive Motors** | Dual 12V High-Torque DC Geared Motors | Differential steering propulsion |
| **Combustible Gas Sensor** | MQ-2 Semiconductor Sensor | Combustible gas (LPG, Methane, Smoke, CO) detection |
| **Metal Detection Probe** | LJ12A3-4-Z/BX Inductive Proximity Sensor | Ferrous and non-ferrous metal detection |
| **Camera Pan-Tilt Gimbal** | Dual TowerPro SG90 9g Micro Servos | 2-DOF optical orientation mechanism |
| **Power Regulation** | 3S 11.1V 2200mAh LiPo with LM2596 Buck | Dual-rail clean power supply (12V and 5V) |

---

## Circuit Pinout Table

| Sensor / Module Pin | Microcontroller Pin | Signal Type | Description |
| :--- | :--- | :--- | :--- |
| **MQ-2 Gas (A0)** | Arduino Analog A0 | Analog Input (0-5V) | Gas concentration voltage output |
| **MQ-2 Gas (D0)** | Arduino Digital D2 | Digital Input | Hardware threshold interrupt trigger |
| **Inductive Metal Sensor** | Arduino Digital D3 | Digital Input | Metal proximity trigger (Active LOW) |
| **L298N ENA / ENB** | Arduino Digital D5 / D6 | PWM Output (8-Bit) | Left and right motor speed control |
| **L298N IN1 / IN2** | Arduino Digital D7 / D8 | Digital Output | Left motor direction gates |
| **L298N IN3 / IN4** | Arduino Digital D9 / D10 | Digital Output | Right motor direction gates |
| **Pan Servo (X-Axis)** | Arduino Digital D11 | PWM Output (50Hz) | 0 to 180 degree horizontal pan |
| **Tilt Servo (Y-Axis)** | Arduino Digital D12 | PWM Output (50Hz) | 0 to 90 degree vertical tilt |
| **Inter-MCU UART** | RX0 / TX1 (Crossed to ESP32) | Serial (115200 Baud) | Inter-controller bidirectional data packet bus |

---

## Firmware Architecture and State Machine

1. **System Self-Check & Baseline Calibration**: On boot, verifies supply voltages, centers the camera gimbal, and performs a 20-second ambient air calibration of the MQ-2 sensor.
2. **Tele-Operation Processing Loop**: Parses operator packets to update motor drive PWM registers.
3. **Hazard Response Engine**:
   - When gas concentration exceeds the safe threshold, triggers an acoustic alarm and transmits a critical alert flag to the dashboard.
   - When metal proximity is detected, latches the coordinates and commands an emergency stop to prevent vehicle damage.

---

## Installation and Setup

1. Clone repository:
   ```bash
   git clone https://github.com/ALWINTR/spybot-metal-and-gas-detection.git
   ```
2. Open the source files in Arduino IDE or VS Code PlatformIO.
3. Install dependencies:
   - `Servo.h`
   - `Wire.h`
4. Select board **Arduino Uno** and **ESP32 Dev Module** for respective files.
5. Compile, flash, and open Serial Monitor at **115200 baud**.

---

## Author

**Alwin T R** - Robotics and Automation Engineer  
- LinkedIn: [linkedin.com/in/alwintr](https://www.linkedin.com/in/alwintr)  
- Portfolio: [alwintr.github.io](https://alwintr.github.io)  
- GitHub: [github.com/ALWINTR](https://github.com/ALWINTR)

---

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.
