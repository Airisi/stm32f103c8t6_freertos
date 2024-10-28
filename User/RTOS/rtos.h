

#ifndef __RTOS_H
#define __RTOS_H


#include	"system.h"
#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"
#include "task.h"
#endif
#include	"led.h"


#define START_TASK_PRIO		0//任务优先级
#define START_STK_SIZE 		128  //任务堆栈大小
extern TaskHandle_t StartTask_Handler;//任务句柄


#define LED0_TASK_PRIO		1//任务优先级
#define LED0_STK_SIZE 		50  //任务堆栈大小
extern TaskHandle_t LED0Task_Handler;//任务句柄


#define LED1_TASK_PRIO		2//任务优先级
#define LED1_STK_SIZE 		50  //任务堆栈大小
extern TaskHandle_t LED1Task_Handler;//任务句柄


void start_task(void *pvParameters);//任务函数


#endif /* __RTOS_H */

