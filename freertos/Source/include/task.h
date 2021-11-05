//任务是一个独立的、无限循环且不能返回的函数.

#ifndef INC_TASK_H
#define INC_TASK_H

#include "list.h"

#define taskYIELD()				portYIELD()

typedef void * TaskHandle_t;

#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
												const char * const pcName,
												const uint32_t ulStackDepth,
												void * const pvParameters,
												StackType_t * const puxStackBuffer,
												TCB_t * const pxTaskBuffer
														);

#endif /* configSUPPORT_STATIC_ALLOCATION */
												
void prvInitialiseTaskLists(void);
void vTaskStartScheduler(void);
void vTaskSwitchContex(void);
												
#endif /* INC_TASK_H */