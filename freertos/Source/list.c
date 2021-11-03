#include "FreeRTOS.h"
#include <stdlib.h>
#include "list.h"


//根节点初始化
void vListInitialise( List_t * const pxList )
{
	/* 将链表索引指针指向最后一个节点,即第一个节点，或者说第零个节点，这个节点不会算入节点计数器的值 */
	pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );
	
	/* 将链表最后一个节点的辅助排序的值设置为最大，确保该节点就是链表的最后节点 */
	pxList->xListEnd.xItemValue = portMAX_DELAY;
	
	/* 将最后一个节点的 pxNext 和 pxPrevious 指针均指向节点自身，表示链表为空 */
	pxList->xListEnd.pxNext = ( ListItem_t * ) & ( pxList->xListEnd );
	
	pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );
	
	/* 初始化链表节点计数器的值为 0，表示链表为空 */
	pxList->uxNumberOfItems = ( UBaseType_t ) 0U;
}

//链表节点初始化
void vListInitialiseItem ( ListItem_t * const pxItem )
{
	/* 初始化该节点所在的链表为空，表示节点还没有插入任何链表 */
	pxItem->pvContainer = NULL;
}

//将节点插入到链表尾部（插入到索引节点的前一个）
//链表式为了多任务进行顺序设置的
//index节点是遍历中目前所在的节点位置。
/*
。。。所以, 为什么 vListInsertEnd() 是将新的节点插入到 pxIndex 前面也就解释的通了, 
这是为了更公平的让各个任务共享时间片. 比如说当前有如下的任务链表, 每个任务的优先级相同:

1    2    3    4    5    end
|
V
1	 2    3    6    4    5    end
其中 1, 2, 3 任务刚刚依次获得完时间片, pxIndex 现在指向 4, 那么现在又来了一个新的任务 6, 
当调用 vListInsertEnd() 的时候, 任务 6 就会被插入到 4 前面, 之后调度就会变成 4, 5, 1, 2, 3, 6, … 
而如果 6 被插入 end 前面, 那之后的调度就会变成 4, 5, 6, 1, 2, 3, … 显然这对 1, 2, 3 是不公平的.
*/
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	//链表索引节点，链表初始化后指向根节点
	ListItem_t * const pxIndex = pxList->pxIndex;
	
	//索引节点作为新节点的下一个节点
	pxNewListItem->pxNext = pxIndex;
	//索引节点的前一个节点作为新节点的前一个节点
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;
	//新节点作为索引节点原先的前一个节点的下一个节点
	pxIndex->pxPrevious->pxNext = pxNewListItem;
	//新节点作为索引节点的前一个节点
	pxIndex->pxPrevious = pxNewListItem;

	//记住该节点所在的链表
	pxNewListItem->pvContainer = ( void * ) pxList;
	
	//链表节点计数器++
	( pxList->uxNumberOfItems )++;
}

//将节点按照升序排列插入到链表
//升序是按照xItemValue大小来排列的
//链表本身就是升序排列，新节点只需要按大小找到应该插入的位置插入即可
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t *pxIterator;
	
	//获取节点的排序辅助值
	const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
	
	if ( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
		/*箭头（->）：左边必须为指针；
		  点号（.）：左边必须为实体。*/
	}
	else
	{
		for ( pxIterator = ( ListItem_t * ) & ( pxList->xListEnd );
				pxIterator->pxNext->xItemValue <= xValueOfInsertion;
				pxIterator = pxIterator->pxNext )
		{
			//没有事情可做，不断迭代只为了找到节点要插入的位置
		}
	}
	//根据升序排列，将节点插入
	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;
	
	//记住该节点所在的链表
	pxNewListItem->pvContainer = ( void * ) pxList;
	
	//节点计数器++
	( pxList->uxNumberOfItems )++;
}

//将节点从链表删除
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove)
{
	//获取节点所在的链表
	List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;
	//将指定的节点从链表删除
	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;
	
	//调整链表的节点索引指针,如果索引正好是要删除的，那么调整成前一个节点,否则不需要变化
	if ( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}
	
	//初始化该节点所在的链表为空，表示该节点还没有插入任何链表
	pxItemToRemove->pvContainer = NULL;
	
	//链表节点计数器--
	( pxList->uxNumberOfItems )--;
	
	//返回链表剩余节点的个数
	return pxList->uxNumberOfItems;
	
}
