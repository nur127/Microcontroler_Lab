# 🔷 STM32F103C8 - CPU Flags (APSR) + Logical & Arithmetic Operations Demo

---

## 📌 Project Title
**Understanding ARM Cortex-M3 CPU Flags using STM32F103C8 (Blue Pill)**

---

## 🎯 Project Goal

This project is designed to help beginners understand:

- How the ARM Cortex-M3 processor executes instructions
- How arithmetic operations affect CPU flags
- How logical operations behave in ARM assembly
- How to read CPU status register (APSR)
- How to control hardware (LED) using register-level programming

👉 Output is shown using **onboard LED (PC13)**.

---

# 🧠 What You Will Learn

## 🔴 1. CPU Flags (APSR Register)

The ARM Cortex-M3 has a special register called:

> **APSR (Application Program Status Register)**

It stores flags that describe the result of operations.

| Flag | Bit | Meaning |
|------|-----|--------|
| N | 31 | Negative result |
| Z | 30 | Zero result |
| C | 29 | Carry from addition |
| V | 28 | Overflow |
| Q | 27 | Saturation |

---

## 🔵 2. Arithmetic Operations

We use:

```assembly
ADDS

### 🔵 Operations Used
- Arithmetic:
  - `ADDS` → Add and update flags
- Logical:
  - `ANDS` → Bitwise AND
  - `ORRS` → Bitwise OR
  - `EORS` → Bitwise XOR
- Saturation:
  - `SSAT` → Signed saturation

---

## 🔌 Hardware Used

- STM32F103C8 (Blue Pill)
- Onboard LED (PC13)
- ST-Link Programmer

---

## ⚙️ Development Tools

- STM32CubeIDE
- ST-Link Driver
- ARM GCC Toolchain

---

## 🚀 How It Works

1. GPIOC clock is enabled using RCC register
2. PC13 is configured as output pin
3. Inline assembly instructions execute:
   - Arithmetic operations
   - Logical operations
4. APSR register is read using:
   ```c
   MRS apsr, APSR