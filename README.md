# 💧 AquaGuardian: Smart Water Drinking Reminder System

## 📌 Overview

AquaGuardian is an **ARM7/LPC21xx-based embedded system** designed to remind users to drink water at regular intervals and track their daily water intake.

The system uses the **LPC21xx internal RTC** to maintain time, a **16×2 LCD** for displaying information, a **4×4 matrix keypad** for user configuration, and a **drink-detection switch** to record water intake.

The system keeps track of:

* 💧 Water drinking target
* 🥤 Water consumed
* 📊 Remaining quantity
* ⚠️ Missed reminders
* 📈 Completion percentage

---

## 🎯 Objective

The main objective of AquaGuardian is to develop a simple embedded water reminder system that combines:

* RTC-based time management
* Periodic drinking reminders
* User-configurable settings
* Water intake detection
* LCD-based status monitoring
* Keypad-based user interaction
* Visual LED indications
* Audible buzzer notifications

---

## ⚙️ Key Features

| Feature              | Description                                                       |
| -------------------- | ----------------------------------------------------------------- |
| 🕐 RTC Clock         | Displays the current time and date using the LPC21xx internal RTC |
| 💧 Water Reminder    | Generates a reminder when the configured reminder time is reached |
| 🥤 Water Detection   | Detects water intake using a switch                               |
| 🎯 Target Setting    | Allows the user to configure the required water target            |
| 📊 Intake Tracking   | Maintains the amount of water consumed                            |
| 🔢 Remaining Count   | Displays the remaining quantity required to reach the target      |
| ⚠️ Missed Count      | Records reminders that were not answered                          |
| 📈 Completion %      | Displays the percentage of the target completed                   |
| ⌨️ Keypad Menu       | Provides user interaction and configuration                       |
| ⚡ External Interrupt | Opens the configuration/menu interface                            |
| 🖥️ LCD Display      | Displays time, date, reminders and water statistics               |
| 🔊 Buzzer            | Provides an audible reminder                                      |
| 💡 LEDs              | Indicates water intake and reminder status                        |

---

# 🧩 System Architecture

The main controller of the system is the **ARM7/LPC21xx microcontroller**.

### Inputs

* LPC21xx Internal RTC
* 4×4 Matrix Keypad
* External Interrupt Button
* Drink Detection Button

### Outputs

* 16×2 LCD
* Buzzer
* Yellow LED
* Green LED
* Red LED

### Overall Working Flow

**RTC → Reminder Check → User Notification → Drink Detection → Update Statistics → LCD Display**

---

# 🖼️ Block Diagram

The following block diagram represents the overall hardware architecture of AquaGuardian.

<img width="1536" height="1024" alt="ChatGPT Image Sep 21, 2026, 12_17_11 PM" src="https://github.com/user-attachments/assets/cef6505d-5e2c-4b0a-87b3-5ed4dff53f1c" />

---

# 🔌 Hardware Connections

## 🖥️ LCD Interface

The 16×2 LCD uses an **8-bit data interface**.

| LCD Signal | LPC21xx Connection |
| ---------- | ------------------ |
| D0         | P0.8               |
| D1         | P0.9               |
| D2         | P0.10              |
| D3         | P0.11              |
| D4         | P0.12              |
| D5         | P0.13              |
| D6         | P0.14              |
| D7         | P0.15              |
| RS         | P0.16              |
| EN         | P0.17              |

---

## ⌨️ 4×4 Matrix Keypad

The keypad uses four row lines and four column lines.

| Keypad Signal | LPC21xx Connection |
| ------------- | ------------------ |
| Row 1         | P1.16              |
| Row 2         | P1.17              |
| Row 3         | P1.18              |
| Row 4         | P1.19              |
| Column 1      | P1.20              |
| Column 2      | P1.21              |
| Column 3      | P1.22              |
| Column 4      | P1.23              |

---

## 💡 Control and Indicator Connections

| Device                    | LPC21xx Pin | Function                           |
| ------------------------- | ----------- | ---------------------------------- |
| External Interrupt Button | P0.1        | Opens configuration/menu interface |
| Drink Detection Button    | P0.20       | Detects water intake               |
| Buzzer                    | P0.21       | Audible reminder                   |
| Yellow LED                | P0.4        | Reminder/status indication         |
| Green LED                 | P0.22       | Successful water intake indication |
| Red LED                   | P0.23       | Missed reminder indication         |

The external interrupt button and drink detection button are **active-low inputs**.

---

# 🖥️ Display Information

The LCD is used to present both real-time information and water-drinking statistics.

| Information      | Purpose                                     |
| ---------------- | ------------------------------------------- |
| Time             | Current RTC time                            |
| Date             | Current RTC date                            |
| Day              | Current day of the week                     |
| Completion %     | Percentage of target completed              |
| Taken            | Quantity of water consumed                  |
| Target           | Configured water target                     |
| Remaining        | Quantity still required                     |
| Missed           | Number of missed reminders                  |
| Reminder Message | Notification when it is time to drink water |

---

# 🔄 Working Principle

1. The LPC21xx initializes the RTC, LCD, keypad, GPIO and external interrupt.
2. The RTC continuously maintains the current time and date.
3. The main program monitors the configured reminder condition.
4. When a reminder is due, the system activates the reminder indication.
5. The LCD displays a water-drinking reminder.
6. The user operates the drink detection button after taking water.
7. If water intake is detected, the consumed quantity is updated.
8. If the reminder is not answered, the missed count is incremented.
9. The LCD continuously updates the water-drinking statistics.
10. The keypad and external interrupt provide access to the configuration/menu interface.

---

# 🔄 Working Workflow

The workflow below represents the software execution and decision flow of AquaGuardian.

<img width="1205" height="1305" alt="ChatGPT Image Sep 21, 2026, 12_19_07 PM" src="https://github.com/user-attachments/assets/64f42997-13d4-4cea-acc8-ed8c0a6a27bc" />

---

# 🧱 Software Modules

| Module                            | Responsibility                                     |
| --------------------------------- | -------------------------------------------------- |
| `project_main.c`                  | System initialization and main program loop        |
| `display_mode.c`                  | Main LCD display and reminder monitoring           |
| `remainder.c`                     | Reminder handling and water-intake/missed tracking |
| `Init_RTC.c`                      | LPC21xx RTC initialization                         |
| `Init_block.c`                    | GPIO direction initialization                      |
| `Init_int.c`                      | External interrupt configuration                   |
| `Init_mode_isr.c`                 | Menu and configuration handling                    |
| `KPM.c`                           | Keypad scanning and numeric input                  |
| `lcd.h` / LCD files               | LCD interface and display operations               |
| `project.h` / `project_defines.h` | Project declarations and hardware definitions      |

---

# 🛠️ Technologies Used

| Category             | Technology                 |
| -------------------- | -------------------------- |
| Microcontroller      | ARM7 / LPC21xx             |
| Programming Language | Embedded C                 |
| Development          | Embedded C Toolchain       |
| Simulation           | Proteus                    |
| Display              | 16×2 LCD                   |
| Input                | 4×4 Matrix Keypad          |
| Time Management      | LPC21xx Internal RTC       |
| Interrupt            | External Interrupt (EINT0) |
| Indicators           | Buzzer + LEDs              |
| Water Detection      | Push Button / Switch       |

---

# 📷 Circuit Diagram

The following circuit diagram shows the hardware connections between the **LPC21xx microcontroller and the connected peripherals**.

<img width="745" height="594" alt="AQUAGUARDIAN_CIRCUIT" src="https://github.com/user-attachments/assets/1ad13edc-4b09-48ce-aff5-029e7940cfe1" />

---

# 📊 Project Demonstration

The project demonstration includes:

* RTC time and date display
* Water reminder generation
* Water intake detection
* Target configuration
* Taken/remaining water tracking
* Missed reminder tracking
* Completion percentage
* Keypad-based interaction
* External interrupt-based menu access
* Buzzer and LED indications

---

# 🚀 Future Improvements

The current project can be extended with:

* Fully configurable reminder duration
* Optional pre-reminder notification
* More robust reminder scheduling
* Daily statistics and reset functionality
* Additional user-configurable parameters
* Non-blocking program architecture
* Power-saving features

---

# 🎓 Learning Outcomes

This project provided practical experience with:

* ARM7/LPC21xx microcontroller programming
* Embedded C
* GPIO configuration
* RTC programming
* LCD interfacing
* Matrix keypad interfacing
* External interrupt handling
* Buzzer and LED control
* User-input processing
* Modular embedded software development
* Hardware/software integration
* Proteus-based embedded-system simulation

---

# 👨‍💻 Project Purpose

AquaGuardian was developed as an **embedded-systems project** to demonstrate the integration of multiple microcontroller peripherals into a practical real-world application.

The project combines **time management, user interaction, input detection, notification mechanisms and data tracking** into a single ARM7-based embedded system.

---

## ⭐ Project Summary

**AquaGuardian** demonstrates how an **ARM7/LPC21xx microcontroller** can integrate RTC, GPIO, LCD, keypad, external interrupts, LEDs and a buzzer to create a practical embedded application.

The project focuses on **modular firmware development, peripheral interfacing, real-time event handling and hardware/software integration**.
