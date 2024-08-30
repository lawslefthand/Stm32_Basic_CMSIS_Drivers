#include "stm32f030x8.h"
#include <stdio.h>

#define BUTTON_GPIO_CLK      (1<<19)  //button gpio port bitmask here
#define LED_GPIO_CLK         (1<<17) //led gpio port bitmask here
#define LED_PORT_NAME        GPIOA   //led port name here
#define BUTTON_PORT_NAME     GPIOC    //button port name here
#define BUTTON_PIN_NUMBER    (1<<13)  //button pin here
#define LED_PIN_ON           (1<<5)  //led pin bsrr set bitmask here
#define LED_PIN_OFF           (1<<21) //led pin bsrr reset bitmask here

void gpio_config(void)
{

	RCC->AHBENR |= BUTTON_GPIO_CLK;
	RCC->AHBENR |= LED_GPIO_CLK;

	LED_PORT_NAME->MODER     |= (1<<10);
	LED_PORT_NAME->MODER    &=~ (1<<11);

    BUTTON_PORT_NAME->MODER &=~  (1<<26);
    BUTTON_PORT_NAME->MODER &=~  (1<<27);

    BUTTON_PORT_NAME->PUPDR  &=~ (1<<26);
    BUTTON_PORT_NAME->PUPDR  |=  (1<<27);


}

void blinky_function_start()
{
	if ((BUTTON_PORT_NAME->IDR & BUTTON_PIN_NUMBER) != BUTTON_PIN_NUMBER)
	{
		LED_PORT_NAME->BSRR |= LED_PIN_ON;
	}
	else
	{
		LED_PORT_NAME->BSRR |= LED_PIN_OFF;
	}

}



int main()
{
	gpio_config();

	while(1)
	{
		blinky_function_start();

	}
}
