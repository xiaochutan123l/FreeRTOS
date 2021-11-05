
#include "task.h"

/*
*************************************************************************
*                               函数声明
*************************************************************************
*/

static void prvInitialiseNewTask( TaskFunction_t pxTaskCode,
												const char * const pcName,	//任务名字
												const uint32_t ulStackDepth,//任务栈大小
												void * const pvParameters,	//任务形参
												TaskHandle_t * const pxCreatedTask,//任务栈起始地址
												TCB_t * pxNew_TCB		//任务控制块指针
														);
					

/*
*************************************************************************
*                               静态任务创建函数
*************************************************************************
*/
												
//静态分配任务
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,					//任务入口
												const char * const pcName,	//任务名字
												const uint32_t ulStackDepth,//任务栈大小
												void * const pvParameters,	//任务形参
												StackType_t * const puxStackBuffer,//任务栈起始地址
												TCB_t * const pxTaskBuffer		//任务控制块指针
														)
{
	TCB_t *pxNewTCB;
	//定义一个任务句柄xTurn，用于指向任务TCB
	TaskHandle_t xReturn;
	
	if ( ( pxTaskBuffer != NULL ) && ( puxStackBuffer != NULL ) )
	{
		pxNewTCB = ( TCB_t * ) pxTaskBuffer;
		pxNewTCB->pxStack = (StackType_t *) puxStackBuffer;
		
		prvInitialiseNewTask( pxTaskCode,
							  pcName,
							  ulStackDepth,
							  pvParameters,
							  &xReturn,
							  pxNewTCB);
	}
	else
	{
		xReturn = NULL;
	}
	return xReturn;
}												
												
#endif /* configSUPPORT_STATIC_ALLOCATION */