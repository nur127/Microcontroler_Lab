#include<stdint.h>
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile  uint32_t *) (RCC_BASE + 0x18))
// #define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOC_BASE 0x40011000
#define GPIOC_CRH (*(volatile  uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR (*(volatile  uint32_t *)(GPIOC_BASE + 0x10))
#define GPIOC_BRR (*(volatile  uint32_t *)(GPIOC_BASE + 0x14))

void delay(){
    for ( volatile int  i = 0; i < 50000; i++);
    
}

int main(){

    RCC_APB2ENR |= (1 << 4);
    GPIOC_CRH &= ~(0x00F00000) ;
    GPIOC_CRH |= (1<<21);
    while (1)
    {
        GPIOC_BRR = (1<<13);
        delay();
        GPIOC_BSRR= (1<<13);
        delay();
    }


}