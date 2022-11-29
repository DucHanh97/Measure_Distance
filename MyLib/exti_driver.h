#ifndef EXTI_DRIVER_H
#define EXTI_DRIVER_H

#include "stm32f10x.h"

#define EXTI0		0
#define EXTI1		1
#define EXTI2		2
#define EXTI3		3
#define EXTI4		4
#define EXTI5		5
#define EXTI6		6
#define EXTI7		7
#define EXTI8		8
#define EXTI9		9
#define EXTI10	10
#define EXTI11	11
#define EXTI12	12
#define EXTI13	13
#define EXTI14	14
#define EXTI15	15

#define RISE		0
#define FALL		1
#define RI_FA		2

#define PA			0
#define PB			1
#define PC			2

void EXTI_Config(uint8_t EXTIx, uint8_t IOPort, uint8_t Ri_Fa, int8_t priority);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

__WEAK void EXTI_IRQHander_Callback(uint8_t EXTIx);
#endif
