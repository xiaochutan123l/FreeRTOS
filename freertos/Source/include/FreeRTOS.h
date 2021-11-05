#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

#include "FreeRTOSConfig.h"
#include "portable.h"
#include "list.h"
#include "projdefs.h"

typedef struct tskTaskControlBlock
{
	// ջ��
	volatile StackType_t	*pxTopOfStack;
	//����ڵ�
	ListItem_t				xStateListItem;
	//����ջ��ʼ��ַ
	StackType_t				*pxStack;
	//�������ƣ��ַ�����ʽ
	char					pcTaskName[ configMAX_TASK_NAME_LEN ];
	
} tskTCB;

typedef tskTCB TCB_t;

#endif /* INC_FREERTOS_H */
