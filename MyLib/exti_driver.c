#include "exti_driver.h"

void EXTI_Config(uint8_t EXTIx, uint8_t IOPort, uint8_t Ri_Fa, int8_t priority)
{
	__disable_irq();
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	if(EXTIx < 4)
	{
		AFIO->EXTICR[0] |= (uint16_t)(0xF << (EXTIx * 4));								//Clear EXTIx bits
		AFIO->EXTICR[0] |= (uint16_t)(IOPort << (EXTIx * 4));							//SET EXTIx - IOPort (PA, PB, PC)
	}
	else if((EXTIx > 3) && (EXTIx < 8))
	{
		AFIO->EXTICR[1] |= (uint16_t)(0xF << ((EXTIx-4) * 4));
		AFIO->EXTICR[1] |= (uint16_t)(IOPort << ((EXTIx-4) * 4));
	}
	else if((EXTIx > 7) && (EXTIx < 12))
	{
		AFIO->EXTICR[2] |= (uint16_t)(0xF << ((EXTIx-8) * 4));
		AFIO->EXTICR[2] |= (uint16_t)(IOPort << ((EXTIx-8) * 4));
	}
	else if((EXTIx > 11) && (EXTIx < 16))
	{
		AFIO->EXTICR[3] |= (uint16_t)(0xF << ((EXTIx-12) * 4));
		AFIO->EXTICR[3] |= (uint16_t)(IOPort << ((EXTIx-12) * 4));
	}
	
	EXTI->IMR |= 1 << EXTIx;																						//Disable the Mask on EXTIx line
	
	if(Ri_Fa == 0)
	{
		EXTI->RTSR |= 1 << EXTIx;																					//Enable Rising Edge Trigger for EXTIx line
	}
	else if(Ri_Fa == 1)
	{
		EXTI->FTSR |= 1 << EXTIx;																					//Enable Falling Edge Trigger for EXTIx line
	}
	else if(Ri_Fa == 2)
	{
		EXTI->RTSR |= 1 << EXTIx;
		EXTI->FTSR |= 1 << EXTIx;
	}
	if(EXTIx == 0)
	{
		NVIC_SetPriority(EXTI0_IRQn, priority);														//Set Priority
		NVIC_EnableIRQ(EXTI0_IRQn);																				//Enable Interrupt
	}
	else if(EXTIx == 1)
	{
		NVIC_SetPriority(EXTI1_IRQn, priority);
		NVIC_EnableIRQ(EXTI1_IRQn);
	}
	else if(EXTIx == 2)
	{
		NVIC_SetPriority(EXTI2_IRQn, priority);
		NVIC_EnableIRQ(EXTI2_IRQn);
	}
	else if(EXTIx == 3)
	{
		NVIC_SetPriority(EXTI3_IRQn, priority);
		NVIC_EnableIRQ(EXTI3_IRQn);
	}
	else if(EXTIx == 4)
	{
		NVIC_SetPriority(EXTI4_IRQn, priority);
		NVIC_EnableIRQ(EXTI4_IRQn);
	}
	else if(EXTIx >= 5 && EXTIx <= 9)
	{
		NVIC_SetPriority(EXTI9_5_IRQn, priority);
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	else if(EXTIx >= 10 && EXTIx <= 15)
	{
		NVIC_SetPriority(EXTI15_10_IRQn, priority);
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
	__enable_irq();
}

void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & (1 << 0))
	{
		EXTI_IRQHander_Callback(EXTI0);
	}
	EXTI->PR |= (1 << 0);
}
void EXTI1_IRQHandler(void)
{
	if(EXTI->PR & (1 << 1))
	{
		EXTI_IRQHander_Callback(EXTI1);
	}
	EXTI->PR |= (1 << 1);
}
void EXTI2_IRQHandler(void)
{
	if(EXTI->PR & (1 << 2))
	{
		EXTI_IRQHander_Callback(EXTI2);
	}
	EXTI->PR |= (1 << 2);
}
void EXTI3_IRQHandler(void)
{
	if(EXTI->PR & (1 << 3))
	{
		EXTI_IRQHander_Callback(EXTI3);
	}
	EXTI->PR |= (1 << 3);
}
void EXTI4_IRQHandler(void)
{
	if(EXTI->PR & (1 << 4))
	{
		EXTI_IRQHander_Callback(EXTI4);
	}
	EXTI->PR |= (1 << 4);
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & (1 << 5))
	{
		EXTI_IRQHander_Callback(EXTI5);
		EXTI->PR |= (1 << 5);
	}
	if(EXTI->PR & (1 << 6))
	{
		EXTI_IRQHander_Callback(EXTI6);
		EXTI->PR |= (1 << 6);
	}
	if(EXTI->PR & (1 << 7))
	{
		EXTI_IRQHander_Callback(EXTI7);
		EXTI->PR |= (1 << 7);
	}
	if(EXTI->PR & (1 << 8))
	{
		EXTI_IRQHander_Callback(EXTI8);
		EXTI->PR |= (1 << 8);
	}
	if(EXTI->PR & (1 << 9))
	{
		EXTI_IRQHander_Callback(EXTI9);
		EXTI->PR |= (1 << 9);
	}
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & (1 << 10))
	{
		EXTI_IRQHander_Callback(EXTI10);
		EXTI->PR |= (1 << 10);
	}
	if(EXTI->PR & (1 << 11))
	{
		EXTI_IRQHander_Callback(EXTI11);
		EXTI->PR |= (1 << 11);
	}
	if(EXTI->PR & (1 << 12))
	{
		EXTI_IRQHander_Callback(EXTI12);
		EXTI->PR |= (1 << 12);
	}
	if(EXTI->PR & (1 << 13))
	{
		EXTI_IRQHander_Callback(EXTI13);
		EXTI->PR |= (1 << 13);
	}
	if(EXTI->PR & (1 << 14))
	{
		EXTI_IRQHander_Callback(EXTI14);
		EXTI->PR |= (1 << 14);
	}
	if(EXTI->PR & (1 << 15))
	{
		EXTI_IRQHander_Callback(EXTI15);
		EXTI->PR |= (1 << 15);
	}
}
