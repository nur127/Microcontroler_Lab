#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define GPIOC_BASE 0x40011000
#define GPIOC_CRH (*(volatile unsigned int * )(GPIOC_BASE + 0x04))
#define GPIOC_BSRR (*(volatile unsigned int * )(GPIOC_BASE + 0x10))
#define GPIOC_BRR (*(volatile unsigned int * )(GPIOC_BASE + 0x14))

void delay(){
	for(volatile int i = 0 ; i<500000;i++);
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
	GPIOC_CRH |= (0x2<<20);
	int a,b;
	volatile unsigned int apsr;
    while(1){


//        __asm volatile (
//            "MOV R0 ,#0     \n"
//            "MSR APSR_nzcvq ,R0   \n"
//            :
//            :
//            :"cc"
//        );
//
//    	a=6 , b=-8;
//
//    	__asm volatile(
//    			"MOV R0,%1     \n"
//    			"MOV R1,%2     \n"
//    			"ADDS R2, R0,R1     \n"
//    			"MRS %0 , APSR    \n"
//    			:"=r"(apsr)
//    			:"r"(a),"r"(b)
//				:"cc"
//
//    	);
//
//    	if(apsr & (1<<31)){
//    		GPIOC_BRR = (1<<13);
//    	}
//    	else{
//    		GPIOC_BSRR = (1<<13);
//    	}

        __asm volatile (
            "MOV R0 ,#0     \n"
            "MSR APSR_nzcvq ,R0   \n"
            :
            :
            :"cc"
        );

        a=6 , b=6;

            	__asm volatile(
            			"MOV R0,%1     \n"
            			"MOV R1,%2     \n"
            			"SUBS R2, R0,R1     \n"
            			"MRS %0 , APSR    \n"
            			:"=r"(apsr)
            			:"r"(a),"r"(b)
        				:"cc"

            	);

            	if(apsr & (1<<31)) blink(1);   // N
            	if(apsr & (1<<30)) blink(2);   // Z
            	if(apsr & (1<<29)) blink(3);   // C
            	if(apsr & (1<<28)) blink(4);   // V
            	if(apsr & (1<<27)) blink(5);   // Q





    }

}
