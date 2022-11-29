#include "stm32f10x.h"                  // Device header
#include "SysClock.h"
#include "timer_driver.h"
#include "gpio_driver.h"
#include "i2c_driver.h"
#include "hcsr04.h"
#include "lcd_i2c.h"

void EXTI0_Config(void);
void EXTI0_IRQHandler(void);

static HCSR04_TypeDef hcsr04;
static LCD_TypeDef lcd;

void EXTI0_Config(void)
{
	//PA0 - EXTI0
	__disable_irq();
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[0] &= (uint16_t)~AFIO_EXTICR1_EXTI0;		//Clear EXTI0 bits
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;						//Set EXTI0 - PA0
	EXTI->IMR |= 1;																			//Disable the Mask on EXTI0
	EXTI->RTSR |= 1;																		//Enable Rising Edge Trigger for PA0
	EXTI->FTSR |= 1;																		//Enable Falling Edge Trigger for PA0
	NVIC_SetPriority(EXTI0_IRQn, 1);										//Set Priority
	NVIC_EnableIRQ(EXTI0_IRQn);													//Enable Interrupt
	__enable_irq();
}

void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & (1 << 0))
	{
		EXTI_HCSR04_Callback(&hcsr04);
	}
	EXTI->PR |= (1 << 0);
}

void HCSR04_Complete_Callback(HCSR04_TypeDef *hcsr04_x)
{
	if(&hcsr04 == hcsr04_x)
	{
		lcd_set_cursor(&lcd, 1, 4);
		lcd_printf(&lcd, "%.3f ", hcsr04.distan);
	}
}

int main()
{
	SysClockConfig();
	
	HCSR04_Init(&hcsr04, TIM2, GPIOA, PIN_1, PIN_0);
	TIM_Config(TIM2, 72, MAX_ARR_VALUE);
	GPIO_Config(GPIOA, PIN_0, INPUT, IN_PP);
	GPIO_Config(GPIOA, PIN_1, OUT50, O_GP_PP);
	EXTI0_Config();
	
	GPIO_Config(GPIOB, PIN_6, OUT50, O_AF_OD);
	GPIO_Config(GPIOB, PIN_7, OUT50, O_AF_OD);
	I2C_Config(I2C1);
	lcd_init(&lcd, I2C1, LCD_ADDR_DEFAULT);
	
	lcd_clear_display(&lcd);
	Delay_ms(1);
	lcd_printf(&lcd, "Distance to obj.");
	
	uint32_t time_now = Get_Tick();
	
	while(1)
	{
		if(Get_Tick() - time_now > 100)
		{
			HCSR04_Start(&hcsr04);
			time_now = Get_Tick();
		}
		HCSR04_Handler(&hcsr04);
	}
}

