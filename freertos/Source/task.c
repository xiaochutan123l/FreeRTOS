
#include "task.h"

/*
*************************************************************************
*                               ��������
*************************************************************************
*/

static void prvInitialiseNewTask( TaskFunction_t pxTaskCode,
												const char * const pcName,	//��������
												const uint32_t ulStackDepth,//����ջ��С
												void * const pvParameters,	//�����β�
												TaskHandle_t * const pxCreatedTask,//����ջ��ʼ��ַ
												TCB_t * pxNew_TCB		//������ƿ�ָ��
														);
					

/*
*************************************************************************
*                               ��̬���񴴽�����
*************************************************************************
*/
												
//��̬��������
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,					//�������
												const char * const pcName,	//��������
												const uint32_t ulStackDepth,//����ջ��С
												void * const pvParameters,	//�����β�
												StackType_t * const puxStackBuffer,//����ջ��ʼ��ַ
												TCB_t * const pxTaskBuffer		//������ƿ�ָ��
														)
{
	TCB_t *pxNewTCB;
	//����һ��������xTurn������ָ������TCB
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