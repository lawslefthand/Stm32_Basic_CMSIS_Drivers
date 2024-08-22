#include "stm32f030x8.h"

#define LED_ON         (1U<<5)  //Use the pins for turning led on in your board.  BSRR pin 5 here.
#define LED_OFF        (1U<<21) //Use the pins for turning led off in your board. BSRR pin 21 here.
#define ENABLE_PORT    (1U<<17) //Give clock access to your port. Port A in this case.
#define GPIO           GPIOA     


int main(void)
{
   RCC->AHBENR  |=  ENABLE_PORT; //Enables clock access using AHBENR registers
   GPIO->MODER |=  (1U<<10);     // Set GPIO mode registers
   GPIO->MODER &=~ (1U<<11);

   while(1)
   {
	   GPIO->BSRR |= LED_ON;
	   for (int i =0;i<100000;i++) //delay
	   	 {}
	   GPIO->BSRR = LED_OFF;       //delay
	   for (int i =0;i<100000;i++)
	   	   	 {}


   }

}
