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

+--------------------------------------------------------------+
| 🔵 2. Arithmetic & Logical Operations                        |
+--------------------------------------------------------------+

🔴 Arithmetic Operation
- Instruction: ADDS
- ✔ Performs addition
- ✔ Updates CPU flags (N, Z, C, V)
- Example: 5 + (-6) = -1

--------------------------------------------------------------

🔵 Logical Operations
- Instructions:
  • ANDS → Bitwise AND
  • ORRS → Bitwise OR
  • EORS → Bitwise XOR

✔ Affects only N and Z flags
✔ Does NOT affect C or V

--------------------------------------------------------------

🟡 Saturation Operation
- Instruction: SSAT
- ✔ Limits value within range
- ✔ Used in DSP applications
- ✔ Sets Q flag on overflow


+--------------------------------------------------------------+
| 🔌 Hardware Used                                             |
+--------------------------------------------------------------+

- STM32F103C8T6 (Blue Pill)
- Onboard LED (PC13)
- ST-Link Programmer


+--------------------------------------------------------------+
| ⚙️ Development Tools                                         |
+--------------------------------------------------------------+

- STM32CubeIDE
- ST-Link Driver
- ARM GCC Toolchain


+--------------------------------------------------------------+
| 🚀 How It Works                                             |
+--------------------------------------------------------------+

1. Enable GPIOC clock (RCC register)
2. Configure PC13 as output (GPIOC_CRH)
3. Execute assembly instructions (ADDS, ANDS, etc.)
4. Read APSR register:
     MRS apsr, APSR
5. Check CPU flags using bitwise operations
6. Control LED based on flag result
