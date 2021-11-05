#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

#include "FreeRTOSConfig.h"
#include "portable.h"
#include "list.h"
#include "projdefs.h"

typedef struct tskTaskControlBlock
{
	// 栈顶
	volatile StackType_t	*pxTopOfStack;
	//任务节点
	ListItem_t				xStateListItem;
	//任务栈起始地址
	StackType_t				*pxStack;
	//任务名称，字符串形式
	char					pcTaskName[ configMAX_TASK_NAME_LEN ];
	
} tskTCB;

typedef tskTCB TCB_t;

#endif /* INC_FREERTOS_H */
