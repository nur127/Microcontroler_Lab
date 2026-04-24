#include <stdint.h>

/* RCC and GPIO Registers */
#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int *)(RCC_BASE + 0x18))

#define GPIOC_BASE    0x40011000
#define GPIOC_CRH     (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR    (*(volatile unsigned int *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR     (*(volatile unsigned int *)(GPIOC_BASE + 0x14))

void delay(void)
{
    for(volatile int i = 0; i < 400000; i++);
}

int main(void)
{
    /* Enable GPIOC clock */
    RCC_APB2ENR |= (1 << 4);

    /* Configure PC13 as output */
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    uint32_t apsr;
    int a, b;

    while(1)
    {
        /* =====================================================
           🧠 1. CLEAR ALL FLAGS (MSR)
        ===================================================== */
        __asm volatile(
            "MOV R0, #0            \n"
            "MSR APSR_nzcvq, R0    \n"
            :
            :
            : "cc"
        );

        /* =====================================================
           🔴 2. NEGATIVE FLAG (ADDS)
        ===================================================== */
        a = 5; b = -6;

        __asm volatile(
            "MOV R0, %1      \n"
            "MOV R1, %2      \n"
            "ADDS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            : "r"(a), "r"(b)
            : "cc"
        );

        if (apsr & (1 << 31))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =====================================================
           🔴 3. SUBTRACTION (SUBS)
        ===================================================== */
        a = 5; b = 10;

        __asm volatile(
            "MOV R0, %1      \n"
            "MOV R1, %2      \n"
            "SUBS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            : "r"(a), "r"(b)
            : "cc"
        );

        delay();

        /* =====================================================
           🟢 4. ZERO FLAG
        ===================================================== */
        a = 5; b = -5;

        __asm volatile(
            "MOV R0, %1      \n"
            "MOV R1, %2      \n"
            "ADDS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            : "r"(a), "r"(b)
            : "cc"
        );

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =====================================================
           🔵 5. OVERFLOW FLAG
        ===================================================== */
        __asm volatile(
            "LDR R0, =2147483647 \n"
            "MOV R1, #1          \n"
            "ADDS R2, R0, R1     \n"
            "MRS %0, APSR        \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        delay();

        /* =====================================================
           🟡 6. Q FLAG (SSAT)
        ===================================================== */
        __asm volatile(
            "MOV R0, #300     \n"
            "SSAT R1, #8, R0  \n"
            "MRS %0, APSR     \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        delay();

        /* =====================================================
           🟡 7. Q STICKY DEMO
        ===================================================== */
        __asm volatile(
            "MRS %0, APSR     \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        delay();

        /* =====================================================
           🔷 8. ANDS (Z = 1)
        ===================================================== */
        a = 0x0F; b = 0xF0;

        __asm volatile(
            "MOV R0, %1      \n"
            "MOV R1, %2      \n"
            "ANDS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            : "r"(a), "r"(b)
            : "cc"
        );

        delay();

        /* =====================================================
           🔷 9. ORRS (Z = 0)
        ===================================================== */
        __asm volatile(
            "MOV R0, %1      \n"
            "MOV R1, %2      \n"
            "ORRS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            : "r"(a), "r"(b)
            : "cc"
        );

        delay();

        /* =====================================================
           🔷 10. EORS (Z = 1)
        ===================================================== */
        a = 0xFF; b = 0xFF;

        __asm volatile(
            "MOV R0, %1      \n"
            "MOV R1, %2      \n"
            "EORS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            : "r"(a), "r"(b)
            : "cc"
        );

        delay();
    }
}