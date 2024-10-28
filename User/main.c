

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
 * @function   :������
 * @parameters :��
 * @retvalue   :��
********************************************************************/
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init();
	JTAG_Set(JTAG_SWD_DISABLE);     //�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //��SWD�ӿ� �������������SWD�ӿڵ���
	LED_GPIO_Config();
	
	//������ʼ����
	//������ �������� �����ջ��С ������� �������ȼ� ������
	xTaskCreate(start_task,"start_task",START_STK_SIZE,NULL,START_TASK_PRIO,&StartTask_Handler);
	vTaskStartScheduler();          //�����������
}

