#include "stm32f030x8.h"
#include  <stdio.h>

#define  USART_PIN            (1U<<2)
#define  USART_GPIO_EN        (1U<<17)
#define  USART_EN_CLK         (1U<<17)
#define  USART_GPIO_NAME       GPIOA
#define  USART_EN             (1U<<0)
#define  USART_TE_EN          (1U<<3)
#define  USART_NAME           USART2
#define DESIRED_BAUD_RATE     115200
#define MCU_CLK               8000000
#define  USART_TX_STATUS      (1U<<7)


void usart_gpio_init(void);
void usart_init(void);
void usart_gpio_init(void);
int brr_calc(void);
void uart2_write(int ch);
int __io_putchar(int ch);



int main()
{
	usart_gpio_init();
	usart_init();
	while(1)
	{
		printf("your message here\n");
	}
}

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_write(int ch)
{

		while(!(USART2->ISR & USART_TX_STATUS)){}

		USART2->TDR	=  (ch & 0xFF);
}

//doesnt work properly

int brr_calc(void)
{
	int brr_val = ((MCU_CLK + (DESIRED_BAUD_RATE/2))/DESIRED_BAUD_RATE);
	return brr_val;
}

void usart_gpio_init(void)
{

	RCC->APB1ENR |= USART_EN_CLK;
	RCC->AHBENR  |= USART_GPIO_EN;

	USART_GPIO_NAME->MODER &=~ (1U<<4);
    USART_GPIO_NAME->MODER  |= (1U<<5);

    USART_GPIO_NAME->AFR[0]  |=  (1U<<8);
    USART_GPIO_NAME->AFR[0]  &=~ (1U<<9);
    USART_GPIO_NAME->AFR[0]  &=~ (1U<<10);
    USART_GPIO_NAME->AFR[0]  &=~ (1U<<11);

}

void usart_init(void)
{
	int baud_rate = 69;

	USART_NAME->BRR = baud_rate;

	USART_NAME->CR1 = 0;

	USART_NAME->CR1 = USART_TE_EN;

	USART_NAME->CR1 |= USART_EN;
}




