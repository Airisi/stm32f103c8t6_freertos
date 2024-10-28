

#include "led.h"


/*******************************************************************
 * @name       :void LED_GPIO_Config(void)
 * @date       :2022-08-01
 * @function   :LED引脚初始化函数
 * @parameters :无
 * @retvalue   :无
********************************************************************/
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	
	#if __LED0
	RCC_APB2PeriphClockCmd(LED0_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED0_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOA,LED0_GPIO_PIN);
	GPIO_ResetBits(GPIOB,LED0_GPIO_PIN);
	GPIO_ResetBits(GPIOC,LED0_GPIO_PIN);
	#endif	/*__LED0*/
	
	
	#if __LED1
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
	#endif	/*__LED1*/
	
	
	#if __LED2
	RCC_APB2PeriphClockCmd(LED2_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_ResetBits(LED2_GPIO_PORT,LED2_GPIO_PIN);
	#endif	/*__LED2*/
	
	
	#if __LED3
	RCC_APB2PeriphClockCmd(LED3_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED3_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_ResetBits(LED3_GPIO_PORT,LED3_GPIO_PIN);
	#endif	/*__LED3*/
}


/*******************************************************************
 * @name       :void led0_task(void *pvParameters)
 * @date       :2022-08-01
 * @function   :LED0任务函数
 * @parameters :*pvParameters:任务参数
 * @retvalue   :无
********************************************************************/
void led0_task(void *pvParameters)
{
	while(1)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_8);	
		vTaskDelay(500);
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);	
		vTaskDelay(500);
	}
}


/*******************************************************************
 * @name       :void led1_task(void *pvParameters)
 * @date       :2022-08-01
 * @function   :LED1任务函数
 * @parameters :*pvParameters:任务参数
 * @retvalue   :无
********************************************************************/
void led1_task(void *pvParameters)
{
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);	
		vTaskDelay(500);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);	
		vTaskDelay(500);
	}
}

