#include<stdint.h>
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile unsigned int*)(RCC_BASE + 0x18))

#define GPIOC_BASE 0x40011000
#define GPIOC_CRH (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_BSRR (*(volatile unsigned int*)(GPIOC_BASE + 0x10))
#define GPIOC_BRR (*(volatile unsigned int*)(GPIOC_BASE + 0x14))

void delay(){
    for(volatile int i=0 ; i<500000;i++);
}

void LED_ON(){
     GPIOC_BRR = (1<<13);
}
void LED_OFF(){
     GPIOC_BSRR = (1<<13);
}

void blink(int times)
{
    for(int i = 0; i < times; i++)
    {
        LED_ON();
        delay();
        LED_OFF();
        delay();
    }
}



int main(){
    RCC_APB2ENR |=(1<<4);
    GPIOC_CRH &= ~(0x00F00000);
    GPIOC_CRH |= (0x2 << 20);

    int a,b;
    uint32_t apsr;
    while(1){

        __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );
        a = 6,b=-8;
        //Addition Negative N fLAF
        __asm volatile(
            "MOV R0, %1     \n"
            "MOV R1 , %2    \n"
            "ADDS R2,R0,R1  \n"
            "MRS %0 , APSR    \n"
            :"=r"(apsr)
            :"r"(a),"r"(b)
            :"cc"
        );

        if ( apsr & (1<<31)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();
    
        __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

    // SUBSTRACTION
    a = 8 , b =10;
        __asm volatile(
            "MOV R0, %1     \n"
            "MOV R1 , %2    \n"
            "SUBS R2,R0,R1  \n"
            "MRS %0 , APSR    \n"
            :"=r"(apsr)
            :"r"(a),"r"(b)
            :"cc"
        );

        if ( apsr & (1<<31)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();
    
        __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

        // ADDITION
        a= 6,b=-6;
        __asm volatile(
            "MOV R0, %1     \n"
            "MOV R1 , %2    \n"
            "SUBS R2,R0,R1  \n"
            "MRS %0 , APSR    \n"
            :"=r"(apsr)
            :"r"(a),"r"(b)
            :"cc"
        );

        if ( apsr & (1<<30)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();

                __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

        // Q SSAT 
        __asm volatile(
            "MOV R0, #300   \n"
            "SSAT R1 , #8 ,R0    \n"
            "MRS %0 , APSR   \n"
            :"=r"(apsr)
            :
            :"cc"
        );
        
        if ( apsr & (1<<27)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();

                __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

          // Q USAT 
        __asm volatile(
            "MOV R0, #300   \n"
            "USAT R1 , #8 ,R0    \n"
            "MRS %0 , APSR   \n"
            :"=r"(apsr)
            :
            :"cc"
        );
        
        if ( apsr & (1<<27)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();
                __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );
        // Overflow
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
            LED_ON();
        else
            LED_OFF();

        delay();

                __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

        // ADDITION CARRY FLAG 
        a= 0xFFFFFFFF,b=1;
        __asm volatile(
            "MOV R0, %1     \n"
            "MOV R1 , %2    \n"
            "ADDS R2,R0,R1  \n"
            "MRS %0 , APSR    \n"
            :"=r"(apsr)
            :"r"(a),"r"(b)
            :"cc"
        );

        if ( apsr & (1<<30)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();

        // Logical AND with Z flag
                        __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

        a= 1,b=1;
        __asm volatile(
            "MOV R0, %1     \n"
            "MOV R1 , %2    \n"
            "ANDS R2,R0,R1  \n"
            "MRS %0 , APSR    \n"
            :"=r"(apsr)
            :"r"(a),"r"(b)
            :"cc"
        );

        if ( apsr & (1<<30)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();
        // Logical OR with Z flag
                        __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

        a= 1,b=1;
        __asm volatile(
            "MOV R0, %1     \n"
            "MOV R1 , %2    \n"
            "ORS R2,R0,R1  \n"
            "MRS %0 , APSR    \n"
            :"=r"(apsr)
            :"r"(a),"r"(b)
            :"cc"
        );

        if ( apsr & (1<<30)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();
        // Logical XOR with Z flag
                        __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

        a= 1,b=1;
        __asm volatile(
            "MOV R0, %1     \n"
            "MOV R1 , %2    \n"
            "EORS R2,R0,R1  \n"
            "MRS %0 , APSR    \n"
            :"=r"(apsr)
            :"r"(a),"r"(b)
            :"cc"
        );

        if ( apsr & (1<<30)){
            LED_ON();
        }
        else{
            LED_OFF();
        }
        delay();


    }

    // Multiplication 
    __asm volatile(
    "MOV R0, %1     \n"
    "MOV R1, %2     \n"
    "MUL R2, R0, R1 \n"
    "CMP R2, #0     \n"   // force flag update
    "MRS %0, APSR   \n"
    : "=r"(apsr)
    : "r"(a), "r"(b)
    : "cc"
);

if (apsr & (1<<30))   // Z flag
    LED_ON();
else
    LED_OFF();


    // Devision 

    __asm volatile(
    "MOV R0, %1     \n"
    "MOV R1, %2     \n"
    "MUL R2, R0, R1 \n"
    "CMP R2, #0     \n"   // force flag update
    "MRS %0, APSR   \n"
    : "=r"(apsr)
    : "r"(a), "r"(b)
    : "cc"
);

if (apsr & (1<<30))   // Z flag
    LED_ON();
else
    LED_OFF();


}
