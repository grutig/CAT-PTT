# CAT-Based PTT Control for Non-Interfaceable Radios

## Overview

The most common method for controlling the PTT (Push-To-Talk) of legacy radios in digital modes via computer is by using the control lines of serial interfaces. However, this approach often suffers from a critical issue: during the computer's boot process, these lines may change state unexpectedly, triggering transmission even when not intended.
To overcome this limitation, I adopted a different approach by programming an **Arduino Nano** to emulate a subset of **Kenwood TS-850 CAT commands**. This allows the transmission to be triggered only through explicit software commands, ensuring safer and more predictable behavior.
The emulated commands are the minimal set required to avoid errors with **Hamlib** (tested with version 4.3 on both Linux and Windows).

## How It Works

The sketch is extremely simple:

- `T 1` raises the level of **pin 8** and turns on the LED (activates transmission).
- `T 0` resets the pin and LED to idle state (stops transmission).

Additionally, a **watchdog timer** is implemented to automatically stop transmission after **30 seconds**—useful for **packet radio** applications. This timeout can be easily customized by modifying the `txTimeout` constant in the code.

## Requirements

- Arduino Nano (or compatible)
- Serial connection to PC
- Software capable of sending Kenwood CAT commands (e.g., Hamlib-compatible apps)

## Tested With

- Hamlib 4.3  
- Linux (Debian)  
- Windows 10
