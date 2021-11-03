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


/*
************************************************************************
*                           节点带参宏小函数
************************************************************************
*/

//初始化节点的拥有者
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )\
		( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )
			
//获取节点拥有者
#define listGET_LIST_ITEM_OWNER( pxListItem )\
		( ( pxListItem )->pvOwner )
		
//初始化节点排序辅助值
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )\
		( ( pxListItem )->xItemValue = ( xValue ) )
		
//获取节点排序辅助值
#define listGET_LIST_ITEM_VALUE( pxListItem )\
		( ( pxListItem )->xItemValue )
		
//获取链表第一个的节点计数器的值
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )\
		( ( ( pxList )->xListEnd ).pxNext->xItemValue )
		
//获取链表的入口节点
#define listGET_HEAD_ENTRY( pxList )\
		( ( ( pxList )->xListEnd ).pxNext )
		
//获取节点的下一个节点
#define listGET_NEXT( pxListItem )\
		( ( pxListItem )->pxNext )
		
//获取链表最后一个节点
#define listGET_END_MARKER( pxList )\
		( ( ListItem_t cons * ) ( &( ( pxList )->xListEnd ) ) )
		
//判断链表是否为空
#define listLIST_IS_EMPTY( pxList )\
		( ( BaseType_t ) ( ( pxList )->uxNumberOfItems == ( UBaseType_t ) 0 ) )

//获取链表的节点数
#define listCURRENT_LIST_LENGTH( pxList )\
		( ( pxList )->uxNumberOfItems )

//获取链表的下一个节点的owner，即TCB
#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )\
{													\
	List_t * const pxConstList = ( pxList );		\
	/*节点索引指向链表第一个节点*/					\
	( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;	\
	/*如果下一个节点是根节点（第一个节点），那么跳过去*/			\
	if( ( void * ) ( pxConstList )->pxIndex == ( void * ) & ( ( pxConstList )->xListEnd ) )		\
	{																							\
		( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;							\
	}																							\
	( pxTCB ) = ( pxCOnstList )->pxIndex->pvOwner;												\
}

//获取链表入口节点的owner
#define listGET_OWNER_OF_HEAD_ENTRY( pxList )\
		( (&( pxList )->xListEnd ))->pxNext->pvOwner )


/*
************************************************************************
*                                函数声明
************************************************************************
*/
void vListInitialise( List_t * const pxList );
void vListInitialiseItem ( ListItem_t * const pxItem );
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem );
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem );
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove);

#endif /* LIST_H */
