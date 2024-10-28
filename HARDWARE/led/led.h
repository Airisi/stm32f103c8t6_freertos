

#ifndef __LED_H
#define __LED_H


#include "system.h"
#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"
#include "task.h"
#endif

#define __LED0	10
#define __LED1	0
#define __LED2	0
#define __LED3	0


#if __LED0
#define	LED0                       PCout(13)
#define LED0_GPIO_PIN              GPIO_Pin_All
#define LED0_GPIO_PORT             GPIOC
#define LED0_GPIO_CLK              RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC
#endif


#if __LED1
#define	LED1                       PCout(13)
#define LED1_GPIO_PIN              GPIO_Pin_13
#define LED1_GPIO_PORT             GPIOC
#define LED1_GPIO_CLK              RCC_APB2Periph_GPIOC
#endif


#if __LED2
#define	LED2                       PCout(13)
#define LED2_GPIO_PIN              GPIO_Pin_13
#define LED2_GPIO_PORT             GPIOC
#define LED2_GPIO_CLK              RCC_APB2Periph_GPIOC
#endif


#if __LED3
#define	LED3                       PCout(13)
#define LED3_GPIO_PIN              GPIO_Pin_13
#define LED3_GPIO_PORT             GPIOC
#define LED3_GPIO_CLK              RCC_APB2Periph_GPIOC
#endif


//#define    ON        1
//#define    OFF       0

//// \  C语言里面叫续行符，后面不能有任何的东西

//#define   LED_G(a)   if(a) \
//	                       GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN); \
//                     else  GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);

void LED_GPIO_Config(void);
void led0_task(void *pvParameters);//任务函数
void led1_task(void *pvParameters);//任务函数


#endif /* __LED_H */

