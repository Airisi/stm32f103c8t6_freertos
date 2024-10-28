
#ifndef __TIMER_H
#define __TIMER_H

#include	"stm32f10x.h"

#include "system.h"
#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"
#include "task.h"
#endif

#define	TIM1_Int	1
#define	TIM2_Int	0
#define	TIM3_Int	10
#define	TIM4_Int	0
#if 0	//HD以上容量才有
#define	TIM5_Int	0
#define	TIM6_Int	0
#define	TIM7_Int	0
#define	TIM8_Int	0
#endif


#define TIM1_BDTRInitStructure	0	//死区刹车

#define TIM1_OCInitStructure	1
#define TIM2_OCInitStructure	0
#define TIM3_OCInitStructure	10
#define TIM4_OCInitStructure	0
#if 0	//HD以上容量才有
#define TIM5_OCInitStructure	0
#define TIM8_OCInitStructure	0
#endif


#define TIM1_CH1	1	//PA8
#define TIM1_CH1N	0	//PB13互不输出
#define TIM1_CH2	0	//PA9
#define TIM1_CH2N	0	//PB14互不输出
#define TIM1_CH3	0	//PA10
#define TIM1_CH3N	0	//PB15互不输出
#define TIM1_CH4	0	//PA11
#define TIM2_CH1	0	//PA0
#define TIM2_CH2	0	//PA1
#define TIM2_CH3	0	//PA2
#define TIM2_CH4	0	//PA3
#define TIM3_CH1	10	//PA6
#define TIM3_CH2	0	//PA7
#define TIM3_CH3	0	//PB0
#define TIM3_CH4	0	//PB1
#define TIM4_CH1	0	//PB6
#define TIM4_CH2	0	//PB7
#define TIM4_CH3	0	//PB8
#define TIM4_CH4	0	//PB9
#if 0	//HD以上容量才有
#define TIM5_CH1	0	//PA0
#define TIM5_CH2	0	//PA1
#define TIM5_CH3	0	//PA2
#define TIM5_CH4	0	//PA3
#define TIM8_CH1	0	//PC6
#define TIM8_CH2	0	//PC7
#define TIM8_CH3	0	//PC8
#define TIM8_CH4	0	//PC9
#endif



#define TIM1_NVIC 1
#define TIM2_NVIC 0
#define TIM3_NVIC 0
#define TIM4_NVIC 0
#if 0	//HD以上容量才有
#define TIM5_NVIC 0
#define TIM6_NVIC 0
#define TIM7_NVIC 0
#define TIM8_NVIC 0
#endif

extern void TIM1_Int_Init(u16 arr,u16 psc);
extern void TIM2_Int_Init(u16 arr,u16 psc);
extern void TIM3_Int_Init(u16 arr,u16 psc);
extern void TIM4_Int_Init(u16 arr,u16 psc);
#if 0	//HD以上容量才有
extern void TIM5_Int_Init(u16 arr,u16 psc);
extern void TIM6_Int_Init(u16 arr,u16 psc);
extern void TIM7_Int_Init(u16 arr,u16 psc);
extern void TIM8_Int_Init(u16 arr,u16 psc);
#endif

void timer1_ch1_task(void *pvParameters);//任务函数

#endif






