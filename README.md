# T-Beam LoRa “Hello” Link (Sender + Receiver) — RadioLib (SX1262, 868 MHz)

A minimal two-device project using **two LILYGO T-Beam V1.2 (ESP32 + SX1262)** boards to communicate over **LoRa** in the **EU 868 MHz** band.

One T-Beam acts as a **Sender** and periodically transmits a short text message (`"hello"`).  
The other T-Beam acts as a **Receiver** and continuously listens, printing received messages plus signal quality information (RSSI/SNR) to the serial monitor.


---

## What is LoRa (in plain words)?

**LoRa** is a long-range, low-power radio technology.  
Think of it like “walkie-talkies for tiny data”:

- ✅ Works over long distances (often hundreds of meters to kilometers depending on environment)
- ✅ Uses very little power
- ✅ Sends small messages (not suitable for high-speed data like Wi‑Fi)

In this project, LoRa is used to send a simple text message from one board to another.

---

## Software Overview

This repository contains two independent firmware programs:

- **`main_send.cpp`** — runs on the **Sender** T-Beam  
  Sends `"hello"` every 2 seconds.

- **`main_receive.cpp`** — runs on the **Receiver** T-Beam  
  Listens for incoming messages and prints them to Serial.

Both programs use the **RadioLib** library to control the **SX1262 LoRa radio** on the T-Beam.

---

## Program Logic (How it works)

### 1) Sender (`main_send.cpp`)
1. Starts the serial port (so you can see logs on your PC).
2. Initializes the SX1262 radio at **868.0 MHz**.
3. Every 2 seconds:
   - Transmits the text message `"hello"`.
   - Prints whether the transmission succeeded.

**Key idea:** the sender does not “connect” like Bluetooth/Wi‑Fi. It simply broadcasts a LoRa packet.

### 2) Receiver (`main_receive.cpp`)
1. Starts the serial port.
2. Initializes the SX1262 radio at **868.0 MHz** (must match the sender).
3. Continuously calls `radio.receive(...)`:
   - If a message arrives, it prints:
     - the received text
     - **RSSI** (signal strength)
     - **SNR** (signal quality)

**Key idea:** the receiver is always listening. When a packet arrives, it reads it and reports signal metrics.

---

## Features

- ✅ Simple “Hello World” LoRa link (Sender → Receiver)
- ✅ Uses **EU 868 MHz** frequency
- ✅ Serial logging for easy debugging
- ✅ Receiver prints **RSSI** and **SNR**
- ✅ Built with **PlatformIO** + Arduino framework
- ✅ Uses **RadioLib** (SX1262 support)

---

## Hardware / Components Used

### Boards
- **2× LILYGO T-Beam V1.2**
  - MCU: **ESP32**
  - LoRa radio: **SX1262**
  - GPS: **NEO-M8N**
  - PMU: **AXP2101**
  - USB-UART: **CH9102**
  - Flash: 4MB, PSRAM: 8MB
  - Marking: *LILYGO 868/915 MHz Model: LORA32 SX1262*

### Region / Frequency
- **Europe (EU): 868 MHz** is used in the code:
  - `static const float LORA_FREQ = 868.0;`

> ⚠️ Always follow your local radio regulations (frequency, transmit power, duty cycle).


![Diagram](images/circuit_image.png)

