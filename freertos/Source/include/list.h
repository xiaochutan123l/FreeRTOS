#ifndef LIST_H
#define LIST_H
/*
************************************************************************
*                                ͷ�ļ�
************************************************************************
*/
#include "FreeRTOS.h"



/*
************************************************************************
*                                �ṹ�嶨��
************************************************************************
*/

// ���������ݽṹ
struct xLIST_ITEM
{
	TickType_t xItemValue;          /*����ֵ�����ڰ����ڵ���˳������*/
	struct xLIST_ITEM * pxNext;		/*ָ�������һ���ڵ�*/
	struct xLIST_ITEM * pxPrevious; /*ָ������ǰһ���ڵ�*/
	void * pvOwner;					/*ָ��ӵ�иýڵ��ӵ���ߣ����ýڵ���Ƕ���Ǹ��ĸ����ݽṹ�У������ĸ����ݽṹ��һԱ*/
	void * pvContainer;				/*ָ��ýڵ����ڵ�����,ͨ��ָ������ĸ��ڵ�*/
};
typedef struct xLIST_ITEM ListItem_t;/*�ڵ����������ض���*/

// ������ڵ����ݽṹ����
struct xMINI_LIST_ITEM
{
	TickType_t xItemValue;						
	struct xLIST_ITEM * pxNext;
	struct xLIST_ITEM * pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;

// ������ڵ����ݽṹ����
typedef struct xLIST
{
	UBaseType_t uxNumberOfItems;	/*����ڵ���������þ߱�ʾ���������ж��ٽڵ㣬���ڵ����*/
	ListItem_t * pxIndex;			/*����ڵ�����ָ�룬���ڱ����ڵ�*/
	MiniListItem_t xListEnd;		/*�������һ���ڵ㣬��ʵ���ǵ�һ���ڵ㣨����ڵ㣩*/
} List_t;