

#ifndef __RTOS_H
#define __RTOS_H


#include	"system.h"
#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"
#include "task.h"
#endif
#include	"led.h"


#define START_TASK_PRIO		0//�������ȼ�
#define START_STK_SIZE 		128  //�����ջ��С
extern TaskHandle_t StartTask_Handler;//������


#define LED0_TASK_PRIO		1//�������ȼ�
#define LED0_STK_SIZE 		50  //�����ջ��С
extern TaskHandle_t LED0Task_Handler;//������


#define LED1_TASK_PRIO		2//�������ȼ�
#define LED1_STK_SIZE 		50  //�����ջ��С
extern TaskHandle_t LED1Task_Handler;//������


void start_task(void *pvParameters);//������


#endif /* __RTOS_H */

