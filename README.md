# AquaGuardian

AquaGuardian is a smart hydration reminder and water intake tracking system built using the **LPC2148 microcontroller** and **Embedded C**.

The system reminds the user to drink water at configurable time intervals, tracks the number of glasses consumed, and provides visual and audible alerts.

## Features

- Configurable daily water intake target
- Configurable hydration reminder interval
- RTC-based reminder scheduling
- 16x2 LCD display for time and hydration status
- 4x4 keypad interface for user input
- External interrupt-based menu access
- Yellow LED and buzzer for hydration alerts
- Drink button to record water intake
- Red and green LEDs to indicate hydration status
- Tracks missed water reminders
- Custom LCD character for water glass indication

## Hardware Used

- LPC2148 Microcontroller
- 16x2 LCD
- 4x4 Matrix Keypad
- LEDs
- Buzzer
- Push Button

## Project Workflow

1. The system starts and displays the AquaGuardian startup message.
2. The user sets a daily water intake target.
3. The user configures the reminder frequency.
4. The RTC monitors the configured reminder interval.
5. When the reminder time is reached, the yellow LED and buzzer alert the user.
6. The user presses the drink button after consuming a glass of water.
7. The system updates the consumed and remaining glass counts.
8. If the user does not respond during the alert period, the missed reminder count is incremented.
9. Once the daily target is achieved, the green LED indicates successful completion.

## Display Information

The LCD displays:

- Current time
- Glasses consumed (`C`)
- Daily target (`T`)
- Reminder frequency (`F`)
- Remaining glasses (`R`)
- Missed reminders (`M`)

## Menu Controls

| Key | Function |
|-----|----------|
| `A` | Time settings |
| `B` | Set daily target |
| `C` | Set reminder frequency |
| `D` | Confirm / Exit |

### Time Settings

| Key | Function |
|-----|----------|
| `A` | Set hour |
| `B` | Set minutes |
| `C` | Set day of week |
| `D` | Return to main menu |

## Project Structure

```text
AquaGuardian/
│
├── main_aquaguardian.c   # Main application logic
├── MENU_FUN.c            # Menu handling functions
├── keypad.c              # Keypad driver
├── keypad_defines.h      # Keypad pin definitions
├── lcd.c                 # LCD driver
├── lcd_defines.h         # LCD command definitions
├── rtc.c                 # RTC driver
├── rtc.h                 # RTC function declarations
├── types.h               # Custom data types
└── Startup.s             # LPC2148 startup code
