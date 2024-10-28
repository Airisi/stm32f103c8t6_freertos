

#include	"stm32f10x.h"
#include	"system.h"
#include	"sys.h"
#include	"delay.h"
#include	"usart.h"
#include	"timer.h"
#include	"led.h"
#if SYSTEM_SUPPORT_OS
#include	"FreeRTOS.h"
#include	"task.h"
#endif
#include	"rtos.h"


/*******************************************************************
 * @name       :int main(void)
 * @date       :2022-08-01
 * @function   :主函数
 * @parameters :无
 * @retvalue   :无
********************************************************************/
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init();
	JTAG_Set(JTAG_SWD_DISABLE);     //关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //打开SWD接口 可以利用主板的SWD接口调试
	LED_GPIO_Config();
	
	//创建开始任务
	//任务函数 任务名称 任务堆栈大小 任务参数 任务优先级 任务句柄
	xTaskCreate(start_task,"start_task",START_STK_SIZE,NULL,START_TASK_PRIO,&StartTask_Handler);
	vTaskStartScheduler();          //开启任务调度
}

