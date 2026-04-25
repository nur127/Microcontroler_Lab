#include<stdint.h>
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))

#define GPIOC_BASE 0x40011000
#define GPIOC_CRH (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR (*(volatile unsigned int *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR (*(volatile unsigned int *)(GPIOC_BASE + 0x14))

void delay(){
    for (volatile int  i = 0; i < 50000; i++);
    
}
int main(){
    RCC_APB2ENR |=(1<<4);
    GPIOC_CRH &= ~(0xF<<20);
    GPIOC_CRH |= (0x2<<20);

    int a,b;
    uint32_t apsr;

    while (1)
    {
        __asm volatile(
            "MOV R0 #0    \n"
            "MSR APRS R0  \n"
            :
            :
            :"cc"

        );
        a=5,b=-6;
        __asm volatile (
            "MOV R0 %1      \n"
            "MOV R1 %2      \n"
            "ADDS R2,RO,R1  \n"
            "MRS %0 , APSR     \n"  
            :"=r"(apsr)
            :"r"(a) ,"r"(b)
            :"cc"
        );
        if(apsr & (1<<31)){
            GPIOC_BRR = (1<<13);
        }
        else{
            GPIOC_BSRR = (1<<13);
        }
        delay();

    }
}