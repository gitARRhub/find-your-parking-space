# 🚗 Find Your Parking Space System 🅿️

> 📡 A Smart Embedded System for Detecting and Displaying Available Parking Slots Using Sensors and Arduino.

---

# 📖 Overview

The **Find Your Parking Space System** is an Arduino-based smart parking management project designed to help users easily identify available parking slots in parking areas.

The system continuously monitors parking spaces using sensors and displays whether slots are occupied or available. This helps reduce traffic congestion, saves time, and improves parking management efficiency.

✨ The project uses:
- ⚡ Arduino UNO
- 📡 IR Sensors / Ultrasonic Sensors
- 💡 LEDs
- 📟 LCD Display
- 🔔 Buzzer (optional)

🎯 The main objective of this project is to provide a low-cost and efficient smart parking solution.

---

# 🎯 Objectives

✅ Detect available parking spaces  
✅ Reduce parking search time  
✅ Display parking slot status  
✅ Improve parking management  
✅ Provide a low-cost smart parking solution  

---

# ✨ Features

🚗 Real-time parking slot detection  
💡 LED indication for slot availability  
📟 LCD display output  
🔔 Alert indication system  
⚡ Low power consumption  
💰 Low-cost implementation  
🛠️ Easy installation and maintenance  

---

# 🧰 Components Used

| 🔩 Component | 🔢 Quantity |
|---|---|
| ⚡ Arduino UNO | 1 |
| 📡 IR Sensors / Ultrasonic Sensors | Multiple |
| 📟 LCD Display | 1 |
| 💡 LEDs | Multiple |
| 🔔 Buzzer | 1 |
| 🔌 Breadboard | 1 |
| 🔗 Jumper Wires | Multiple |
| 🔋 Power Supply | 1 |

---

# ⚙️ Working Principle

📡 Sensors are placed at each parking slot to detect whether a vehicle is present.

🚗 When a vehicle occupies a parking slot:
- 🔴 Red LED turns ON
- Slot is marked as occupied

✅ When the slot is empty:
- 🟢 Green LED turns ON
- Slot is marked as available

📟 The LCD display shows:
- Total parking slots
- Available slots
- Occupied slots

🔔 Optional buzzer alerts can also be implemented for vehicle entry and exit notifications.

---

# 🧱 Block Diagram

## 📥 Input Section
- 📡 IR Sensors / Ultrasonic Sensors

## 🧠 Processing Section
- ⚡ Arduino UNO

## 📤 Output Section
- 📟 LCD Display
- 💡 LEDs
- 🔔 Buzzer

---

# 🛠️ Hardware Used

## ⚡ Arduino UNO
Main controller used to process sensor data and control outputs.

---

## 📡 IR / Ultrasonic Sensors
Used for vehicle detection in parking slots.

---

## 📟 LCD Display
Displays parking slot information and availability status.

---

## 💡 LEDs
Used for visual indication of slot status.

🟢 Green LED → Slot Available  
🔴 Red LED → Slot Occupied  

---

## 🔔 Buzzer
Used for alert indications (optional).

---

# 💻 Software Used

## 🖥️ Arduino IDE

The project is programmed using **Arduino IDE**.

### ✨ Features:
- 📝 Writing and uploading code
- 🔌 Compatible with Arduino boards
- 🌐 Offline development support
- 📡 Serial monitoring support

## 🔗 Download Arduino IDE
https://www.arduino.cc/en/software

---

# 📂 Source Code

The source code for the project is included in the `src/` folder.

### 🔧 Main Functionalities
- 📡 Parking slot sensing
- 🚗 Vehicle detection
- 📟 LCD interfacing
- 💡 LED indication system
- 🔔 Alert system

---

# 📸 Results

✅ Detects vehicle presence  
✅ Displays available parking spaces  
✅ Indicates slot status using LEDs  
✅ Reduces parking search time  
✅ Provides efficient parking management  

---

# 🌍 Applications

🏢 Shopping malls  
🏫 Colleges and universities  
🏥 Hospitals  
🏬 Commercial buildings  
🛬 Airports  
🏙️ Smart city parking systems  

---

# 🚀 Future Improvements

📶 Wi-Fi module integration  
📱 Mobile application support  
☁️ IoT-based monitoring  
📷 Camera integration  
🛰️ Cloud data storage  
🤖 AI-based vehicle analytics  

---

# 💰 Cost Analysis

| 🧩 Component | 💵 Cost |
|---|---|
| ⚡ Arduino UNO | ₹800 |
| 📡 Sensors | ₹300 |
| 📟 LCD Display | ₹100 |
| 💡 LEDs | ₹50 |
| 🔔 Buzzer | ₹10 |
| 🔌 Breadboard | ₹50 |
| 🔧 Other Components | ₹100 |

# 💸 Total Cost: ₹1400 Approx.

---

# 📁 Folder Structure

```text
find-your-parking-space/
│
├── README.md
├── src/
│   └── code.ino
│
├── images/
│   ├── complete_setup.jpg
│   ├── parking_detection.jpg
│   ├── lcd_display.jpg
│   └── slot_indication.jpg
│
├── circuit_diagram/
│   └── circuit.png
│
├── docs/
│   └── project_report.pdf
│
└── components/
    └── components_list.txt
