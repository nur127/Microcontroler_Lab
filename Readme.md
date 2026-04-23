# 💡 STM32 PC13 LED Blink (Register Level - No HAL)

This project demonstrates a simple LED blinking program using **register-level programming** on an STM32 microcontroller (STM32F1 series).

No HAL or standard libraries are used—only direct register access.

---

## 🧠 Concepts Used

- GPIO register programming
- RCC clock enable
- Bitwise operations
- Delay using simple loop
- PC13 LED control (active low)

---

## 🔧 Hardware Requirements

- STM32F103C8 (Blue Pill) or similar STM32 board
- Onboard LED (PC13) OR external LED
- ST-Link programmer

---

## ⚙️ Working Principle

The program:

1. Enables clock for GPIOC using RCC register  
2. Configures PC13 as output push-pull  
3. Toggles LED using:
   - BRR → LED ON (because active LOW)
   - BSRR → LED OFF  
4. Uses simple delay loop for visible blinking

---

## 📌 Register Mapping

| Peripheral | Register |
|------------|----------|
| RCC | 0x40021000 |
| GPIOC | 0x40011000 |

---

## 💻 Code

```c
#include <stdint.h>

#define RCC_BASE        0x40021000
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))

#define GPIOC_BASE      0x40011000
#define GPIOC_CRH       (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR      (*(volatile uint32_t *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR       (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

void delay(void)
{
    for(volatile int i = 0; i < 500000; i++);
}

int main(void)
{
    // Enable GPIOC clock
    RCC_APB2ENR |= (1 << 4);

    // Configure PC13 as output push-pull
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    while(1)
    {
        GPIOC_BRR = (1 << 13);  // LED ON
        delay();

        GPIOC_BSRR = (1 << 13); // LED OFF
        delay();
    }
}