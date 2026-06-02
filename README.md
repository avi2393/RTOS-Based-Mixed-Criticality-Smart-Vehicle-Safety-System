# RTOS-Based Mixed-Criticality Smart Vehicle Safety System

A real-time embedded vehicle safety project built on **STM32F446RE** using **FreeRTOS**.  
The system demonstrates mixed-criticality task handling, where safety-related functions are prioritized and managed in real time for reliable vehicle operation.

---

## Overview

This project focuses on implementing a **smart vehicle safety system** using an RTOS-based architecture.  
It is designed to support multiple vehicle safety functions while keeping critical tasks responsive and stable.

The project is built as an STM32 embedded application with FreeRTOS integration and standard STM32Cube project structure. It includes the CubeMX configuration file, STM32 project files, linker scripts, and FreeRTOS source components. :contentReference[oaicite:1]{index=1}

---

## Key Features

- Mixed-criticality task design
- Real-time task scheduling using FreeRTOS
- Safety-focused embedded control logic
- STM32-based hardware implementation
- Modular code structure for future expansion
- Vehicle safety system foundation for automotive applications

---

## System Highlights

The project is intended to simulate or implement a smart vehicle safety platform where tasks with different priorities are handled efficiently.

Typical functions in such a system may include:

- Safety monitoring
- Real-time alerts
- Event-based control handling
- Critical task priority management
- Embedded vehicle status response

---

## Hardware / Platform

- **Microcontroller:** STM32F446RE
- **RTOS:** FreeRTOS
- **Development Environment:** STM32CubeIDE / STM32CubeMX
- **Language:** C

The repository structure shows STM32 project configuration, FreeRTOS sources, and STM32F446RE linker scripts. :contentReference[oaicite:2]{index=2}

---

## Project Structure

```text
RTOS-Based-Mixed-Criticality-Smart-Vehicle-Safety-System/
└── MixedCritical_system/
    ├── Core/
    ├── Drivers/
    ├── Middlewares/Third_Party/FreeRTOS/Source/
    ├── Debug/
    ├── .ioc
    ├── .cproject
    ├── .project
    ├── STM32F446RETX_FLASH.ld
    └── STM32F446RETX_RAM.ld
