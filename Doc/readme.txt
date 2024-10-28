FreeRTOS使用方法：（以下方法以创建led0_task任务为例）

Step1：完成函数的引脚功能初始化

Step2：创建任务函数，如led.c文件的【void led0_task(void *pvParameters)】

任务函数必须包含while(1)或者其他类型的死循环；任务当中必须调用【vTaskDelay(500);】延时函数，延时之间自定义，让任务处于一定时间的阻塞状态，系统跳转至别的任务执行。

Step3：rtos.c文件中创建任务句柄【TaskHandle_t LED0Task_Handler;		//任务句柄】

Step4：rtos.h文件中声明任务优先级、任务堆栈大小、定义全局任务句柄变量

注： FreeRTOS 中任务的最高优先级是通过 FreeRTOSConfig.h 文件中的 configMAX_PRIORITIES 进行
配置的，优先级顺序为【0≤优先级≤(configMAX_PRIORITIES -1)】

Step5：rtos.c文件中创建任务【xTaskCreate(led0_task,"led0_task",LED0_STK_SIZE, NULL,LED0_TASK_PRIO,&LED0Task_Handler);】

led0_task：任务函数，需要执行的程序

"led0_task"：任务名，用法等同于程序注释

LED0_STK_SIZE：任务栈大小，根据程序运行所需的空间自定义

NULL：任务参数，即Step2当中创建任务函数的入口参数(void *pvParameters)

LED0_TASK_PRIO：任务优先级，0~(configMAX_PRIORITIES -1)

&LED0Task_Handler：任务句柄



FreeRTOS执行过程：

Step1：完成系统的初始化配置

Step2：创建开始任务，并开启调度

Step3：程序执行开始任务函数，而后在开始任务函数内部再定义led0任务函数与led1任务函数

Step4：开始任务函数的作用已经完成，调用【vTaskDelete(StartTask_Handler);】将开始任务删除

Step5：系统仅剩下led0任务与led1任务在执行

另：也可以直接将led0任务与led1任务写在main函数里面直接执行，不需要通过开始任务函数，这样会造成main函数臃肿，不建议。



最终解释权归作者所有。

作者：戴创昆

2022/08/01