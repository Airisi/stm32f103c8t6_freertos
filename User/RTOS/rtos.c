

#include	"rtos.h"


TaskHandle_t StartTask_Handler;		//������
TaskHandle_t LED0Task_Handler;		//������
TaskHandle_t LED1Task_Handler;		//������
TaskHandle_t TIMER1CH1Task_Handler;		//������

/*******************************************************************
 * @name       :void start_task(void *pvParameters)
 * @date       :2022-08-01
 * @function   :��ʼ������
 * @parameters :*pvParameters:�������
 * @retvalue   :��
********************************************************************/
void start_task(void *pvParameters)//������
{
	taskENTER_CRITICAL();           //�����ٽ���
	//����LED0����
	xTaskCreate(led0_task,"led0_task",LED0_STK_SIZE, NULL,LED0_TASK_PRIO,&LED0Task_Handler);
	
	xTaskCreate(led1_task,"led1_task",LED1_STK_SIZE, NULL,LED1_TASK_PRIO,&LED1Task_Handler);

	xTaskCreate(timer1_ch1_task,"timer1_ch1_task",TIMER1CH1_STK_SIZE, NULL,TIMER1CH1_Task_PRIO,&TIMER1CH1Task_Handler);

	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
	taskEXIT_CRITICAL();            //�˳��ٽ���
}



