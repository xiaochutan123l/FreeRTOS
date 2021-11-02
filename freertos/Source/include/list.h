#ifndef LIST_H
#define LIST_H
/*
************************************************************************
*                                头文件
************************************************************************
*/
#include "FreeRTOS.h"



/*
************************************************************************
*                                结构体定义
************************************************************************
*/

// 链表项数据结构
struct xLIST_ITEM
{
	TickType_t xItemValue;          /*辅助值，用于帮助节点做顺序排列*/
	struct xLIST_ITEM * pxNext;		/*指向链表后一个节点*/
	struct xLIST_ITEM * pxPrevious; /*指向链表前一个节点*/
	void * pvOwner;					/*指向拥有该节点的拥有者，即该节点内嵌在那个哪个数据结构中，属于哪个数据结构的一员*/
	void * pvContainer;				/*指向该节点所在的链表,通常指向链表的根节点*/
};
typedef struct xLIST_ITEM ListItem_t;/*节点数据类型重定义*/

// 链表精简节点数据结构定义
struct xMINI_LIST_ITEM
{
	TickType_t xItemValue;						
	struct xLIST_ITEM * pxNext;
	struct xLIST_ITEM * pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;

// 链表根节点数据结构定义
typedef struct xLIST
{
	UBaseType_t uxNumberOfItems;	/*链表节点计数器，用具表示该链表下有多少节点，根节点除外*/
	ListItem_t * pxIndex;			/*链表节点索引指针，用于遍历节点*/
	MiniListItem_t xListEnd;		/*链表最后一个节点，其实就是第一个节点（精简节点）*/
} List_t;