# 🤖 SpyBot — Long-Range Multi-Sensor Reconnaissance & Hazardous Detection Rover

[![GitHub Repository](https://img.shields.io/badge/GitHub-Repository-00f0ff?style=for-the-badge&logo=github&logoColor=white)](https://github.com/ALWINTR/spybot-metal-and-gas-detection)
[![Developer](https://img.shields.io/badge/Developer-Alwin_T_R-0284c7?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/alwintr)
[![Platform](https://img.shields.io/badge/Platform-ESP32_%26_Arduino-38bdf8?style=for-the-badge&logo=arduino&logoColor=white)](https://github.com/ALWINTR)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

An advanced tele-operated multi-terrain reconnaissance rover designed for hazardous search-and-rescue operations, toxic gas leak detection, and buried metal proximity identification in environments hazardous to human personnel.

---

## 📌 System Architecture

SpyBot operates using a distributed dual-controller architecture:
1. **Master Wireless Controller (ESP32)**: Manages long-range wireless telemetry reception, streaming video payload, and operator control command decoding.
2. **Real-Time Sensor & Actuation Unit (Arduino Uno / Mega)**: Executes high-speed analog ADC sampling of the **MQ-2 gas sensor**, digital polling of the **inductive proximity sensor**, and dual H-bridge **L298N differential motor drive** actuation.
3. **2-DOF Pan-Tilt Camera Gimbal**: Driven by twin SG90 micro-servos enabling full 180° horizontal and 90° vertical optical field-of-view scanning.

```
                  ┌──────────────────────────────┐
                  │    Operator Wireless Link    │
                  └──────────────┬───────────────┘
                                 │ Wi-Fi / Serial
                                 ▼
                  ┌──────────────────────────────┐
                  │   ESP32 Master Controller    │
                  │   • Video Stream & Telemetry │
                  └──────────────┬───────────────┘
                                 │ UART Telemetry
                                 ▼
                  ┌──────────────────────────────┐
                  │   Arduino Sub-Controller     │
                  │   • Real-Time ADC & PWM      │
                  └──┬───────────┬────────────┬──┘
                     │           │            │
       ┌─────────────▼──┐ ┌──────▼──────┐ ┌───▼────────────┐
       │ MQ-2 Gas Sensor│ │Inductive Sen│ │Dual L298N Drive│
       │ (Combustible)  │ │(Metal Proxim│ │(Differential)  │
       └────────────────┘ └─────────────┘ └────────────────┘
```

---

## ⚙️ Hardware Bill of Materials (BOM)

| Component | Specification | Function |
| :--- | :--- | :--- |
| **Microcontroller 1** | ESP32-WROOM-32 (240MHz Dual-Core) | Wireless video & operator tele-operation |
| **Microcontroller 2** | Arduino Uno / Mega (ATmega328P / ATmega2560) | Sensor acquisition & motor PWM |
| **Motor Driver** | L298N Dual H-Bridge Driver Module | Bi-directional DC motor speed & direction |
| **Drive Motors** | 2x / 4x 12V High-Torque DC Geared Motors | Differential steering & propulsion |
| **Gas Sensor** | MQ-2 Semiconductor Sensor | Combustible gas (LPG, Methane, Smoke, CO) |
| **Metal Sensor** | LJ12A3-4-Z/BX Inductive Proximity Sensor | Ferrous and non-ferrous metal detection |
| **Camera Gimbal** | 2x TowerPro SG90 9g Micro Servos | 2-DOF Pan/Tilt camera orientation |
| **Power System** | 3S 11.1V 2200mAh LiPo + LM2596 5V Buck | Clean dual-rail power distribution |

---

## 🔌 Pinout & Interconnect Table

| Sensor / Module Pin | Arduino / ESP32 Pin | Signal Type | Description |
| :--- | :--- | :--- | :--- |
| **MQ-2 Gas (A0)** | Arduino A0 | Analog In (0-5V) | Gas concentration ADC voltage |
| **MQ-2 Gas (D0)** | Arduino D2 | Digital In | Hardware threshold interrupt |
| **Inductive Metal Sensor** | Arduino D3 | Digital In (via Divider) | Metal proximity trigger (Active LOW) |
| **L298N ENA / ENB** | Arduino D5 / D6 | PWM Out (8-Bit) | Motor speed control |
| **L298N IN1 / IN2** | Arduino D7 / D8 | Digital Out | Left motor direction |
| **L298N IN3 / IN4** | Arduino D9 / D10 | Digital Out | Right motor direction |
| **Pan Servo (X-Axis)** | Arduino D11 | PWM Out (50Hz) | 0° - 180° Horizontal Pan |
| **Tilt Servo (Y-Axis)** | Arduino D12 | PWM Out (50Hz) | 0° - 90° Vertical Tilt |
| **UART RX / TX** | Pins 0 / 1 (Crossed to ESP32) | Serial (115200 Baud) | Inter-MCU bidirectional link |

---

## 🧠 Firmware Logic & Safety State Machine

1. **Self-Test & Calibration**: On startup, verifies MCU voltage rails, zeros servo gimbal positions, and samples ambient gas baseline for 20 seconds.
2. **Tele-Operation Loop**: Continuously decodes differential velocity packets (`V_left`, `V_right`) from the wireless stream.
3. **Hazard Response Engine**:
   - **Gas Alert**: When MQ-2 ADC reading exceeds calibrated threshold, emits acoustic alert and flags operator dashboard.
   - **Metal Detection**: When inductive sensor triggers, rover automatically latches coordinates and engages emergency brake to prevent detonating or colliding with metallic hazards.

---

## 🚀 Getting Started & Flashing

1. Clone this repository:
   ```bash
   git clone https://github.com/ALWINTR/spybot-metal-and-gas-detection.git
   ```
2. Open `spybot motor control.ino` and `spybot sensor control.ino` in Arduino IDE or VS Code PlatformIO.
3. Install required libraries:
   - `Servo.h`
   - `Wire.h`
4. Select board **Arduino Uno** / **ESP32 Dev Module** and corresponding COM ports.
5. Flash binaries and open Serial Monitor at **115200 baud**.

---

## 👨‍💻 Author

**Alwin T R** — Robotics & Automation Engineer  
- 💼 LinkedIn: [linkedin.com/in/alwintr](https://www.linkedin.com/in/alwintr)  
- 🌌 Portfolio: [alwintr.github.io](https://alwintr.github.io)  
- 💻 GitHub: [github.com/ALWINTR](https://github.com/ALWINTR)

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.
