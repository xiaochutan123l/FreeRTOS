#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_16_BIT_TICKS					0
#define configMAX_TASK_NAME_LEN					(16)
#define configSUPPORT_STATIC_ALLOCATION			1
#define configMAX_PRIORITIES					(5)

#define configKERNEL_INTERRUPT_PRIORITY			255
#define config_MAX_SYSCAL_INTERRUPT_PRIORITY	191

#define xPortPendSVHander	PendSV_Handler
#define xPortSysTickHander	SysTick_Handler
#define vPortSVHander		SVC_Handler

#endif /* FREERTOS_CONFIG_H */
