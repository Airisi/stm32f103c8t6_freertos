

#include	"rtos.h"


TaskHandle_t StartTask_Handler;		//任务句柄
TaskHandle_t LED0Task_Handler;		//任务句柄
TaskHandle_t LED1Task_Handler;		//任务句柄
TaskHandle_t TIMER1CH1Task_Handler;		//任务句柄

/*******************************************************************
 * @name       :void start_task(void *pvParameters)
 * @date       :2022-08-01
 * @function   :开始任务函数
 * @parameters :*pvParameters:任务参数
 * @retvalue   :无
********************************************************************/
void start_task(void *pvParameters)//任务函数
{
	taskENTER_CRITICAL();           //进入临界区
	//创建LED0任务
	xTaskCreate(led0_task,"led0_task",LED0_STK_SIZE, NULL,LED0_TASK_PRIO,&LED0Task_Handler);
	
	xTaskCreate(led1_task,"led1_task",LED1_STK_SIZE, NULL,LED1_TASK_PRIO,&LED1Task_Handler);

	xTaskCreate(timer1_ch1_task,"timer1_ch1_task",TIMER1CH1_STK_SIZE, NULL,TIMER1CH1_Task_PRIO,&TIMER1CH1Task_Handler);

	vTaskDelete(StartTask_Handler); //删除开始任务
	taskEXIT_CRITICAL();            //退出临界区
}



