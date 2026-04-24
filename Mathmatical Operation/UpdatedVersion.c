#include <stdint.h>

/* RCC and GPIO Registers */
#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int *)(RCC_BASE + 0x18))

#define GPIOC_BASE    0x40011000
#define GPIOC_CRH     (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR    (*(volatile unsigned int *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR     (*(volatile unsigned int *)(GPIOC_BASE + 0x14))

/* Simple delay */
void delay(void)
{
    for(volatile int i = 0; i < 500000; i++);
}

int main(void)
{
    /* Enable GPIOC clock */
    RCC_APB2ENR |= (1 << 4);

    /* Configure PC13 as output */
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    uint32_t apsr;

    while(1)
    {
        /* =========================
           CLEAR ALL FLAGS (MSR)
        ========================= */
        __asm volatile(
            "MOV R0, #0            \n"
            "MSR APSR_nzcvq, R0    \n"
            :
            :
            : "cc"
        );

        /* =========================
           🔴 NEGATIVE FLAG (ADDS)
        ========================= */
        __asm volatile(
            "MOV R0, #5      \n"
            "MOV R1, #-6     \n"
            "ADDS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 31))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =========================
           🔴 SUBTRACTION (SUBS)
        ========================= */
        __asm volatile(
            "MOV R0, #5      \n"
            "MOV R1, #10     \n"
            "SUBS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 31))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =========================
           🟢 ZERO FLAG
        ========================= */
        __asm volatile(
            "MOV R0, #5      \n"
            "MOV R1, #-5     \n"
            "ADDS R2, R0, R1 \n"
            "MRS %0, APSR    \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =========================
           🔵 OVERFLOW FLAG
        ========================= */
        __asm volatile(
            "LDR R0, =2147483647 \n"
            "MOV R1, #1          \n"
            "ADDS R2, R0, R1     \n"
            "MRS %0, APSR        \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 28))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =========================
           🟡 Q FLAG (SSAT)
        ========================= */
        __asm volatile(
            "MOV R0, #300     \n"
            "SSAT R1, #8, R0  \n"
            "MRS %0, APSR     \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 27))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =========================
           🟡 Q STICKY DEMO
        ========================= */
        __asm volatile(
            "MRS %0, APSR     \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 27))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =========================
           🔷 ANDS (Z = 1)
        ========================= */
        __asm volatile(
            "MOV R0, #0x0F    \n"
            "MOV R1, #0xF0    \n"
            "ANDS R2, R0, R1  \n"
            "MRS %0, APSR     \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =========================
           🔷 ORRS (Z = 0)
        ========================= */
        __asm volatile(
            "MOV R0, #0x0F    \n"
            "MOV R1, #0xF0    \n"
            "ORRS R2, R0, R1  \n"
            "MRS %0, APSR     \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();

        /* =========================
           🔷 EORS (Z = 1)
        ========================= */
        __asm volatile(
            "MOV R0, #0xFF    \n"
            "MOV R1, #0xFF    \n"
            "EORS R2, R0, R1  \n"
            "MRS %0, APSR     \n"
            : "=r"(apsr)
            :
            : "cc"
        );

        if (apsr & (1 << 30))
            GPIOC_BRR = (1 << 13);
        else
            GPIOC_BSRR = (1 << 13);

        delay();
    }
}