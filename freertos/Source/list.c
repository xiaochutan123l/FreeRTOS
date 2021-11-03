#include "FreeRTOS.h"
#include <stdlib.h>
#include "list.h"


//���ڵ��ʼ��
void vListInitialise( List_t * const pxList )
{
	/* ����������ָ��ָ�����һ���ڵ�,����һ���ڵ㣬����˵������ڵ㣬����ڵ㲻������ڵ��������ֵ */
	pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );
	
	/* ���������һ���ڵ�ĸ��������ֵ����Ϊ���ȷ���ýڵ������������ڵ� */
	pxList->xListEnd.xItemValue = portMAX_DELAY;
	
	/* �����һ���ڵ�� pxNext �� pxPrevious ָ���ָ��ڵ�������ʾ����Ϊ�� */
	pxList->xListEnd.pxNext = ( ListItem_t * ) & ( pxList->xListEnd );
	
	pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );
	
	/* ��ʼ������ڵ��������ֵΪ 0����ʾ����Ϊ�� */
	pxList->uxNumberOfItems = ( UBaseType_t ) 0U;
}

//����ڵ��ʼ��
void vListInitialiseItem ( ListItem_t * const pxItem )
{
	/* ��ʼ���ýڵ����ڵ�����Ϊ�գ���ʾ�ڵ㻹û�в����κ����� */
	pxItem->pvContainer = NULL;
}

//���ڵ���뵽����β�������뵽�����ڵ��ǰһ����
//����ʽΪ�˶��������˳�����õ�
//index�ڵ��Ǳ�����Ŀǰ���ڵĽڵ�λ�á�
/*
����������, Ϊʲô vListInsertEnd() �ǽ��µĽڵ���뵽 pxIndex ǰ��Ҳ�ͽ��͵�ͨ��, 
����Ϊ�˸���ƽ���ø���������ʱ��Ƭ. ����˵��ǰ�����µ���������, ÿ����������ȼ���ͬ:

1    2    3    4    5    end
|
V
1	 2    3    6    4    5    end
���� 1, 2, 3 ����ո����λ����ʱ��Ƭ, pxIndex ����ָ�� 4, ��ô����������һ���µ����� 6, 
������ vListInsertEnd() ��ʱ��, ���� 6 �ͻᱻ���뵽 4 ǰ��, ֮����Ⱦͻ��� 4, 5, 1, 2, 3, 6, �� 
����� 6 ������ end ǰ��, ��֮��ĵ��Ⱦͻ��� 4, 5, 6, 1, 2, 3, �� ��Ȼ��� 1, 2, 3 �ǲ���ƽ��.
*/
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	//���������ڵ㣬�����ʼ����ָ����ڵ�
	ListItem_t * const pxIndex = pxList->pxIndex;
	
	//�����ڵ���Ϊ�½ڵ����һ���ڵ�
	pxNewListItem->pxNext = pxIndex;
	//�����ڵ��ǰһ���ڵ���Ϊ�½ڵ��ǰһ���ڵ�
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;
	//�½ڵ���Ϊ�����ڵ�ԭ�ȵ�ǰһ���ڵ����һ���ڵ�
	pxIndex->pxPrevious->pxNext = pxNewListItem;
	//�½ڵ���Ϊ�����ڵ��ǰһ���ڵ�
	pxIndex->pxPrevious = pxNewListItem;

	//��ס�ýڵ����ڵ�����
	pxNewListItem->pvContainer = ( void * ) pxList;
	
	//����ڵ������++
	( pxList->uxNumberOfItems )++;
}

//���ڵ㰴���������в��뵽����
//�����ǰ���xItemValue��С�����е�
//����������������У��½ڵ�ֻ��Ҫ����С�ҵ�Ӧ�ò����λ�ò��뼴��
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
	ListItem_t *pxIterator;
	
	//��ȡ�ڵ��������ֵ
	const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;
	
	if ( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
		/*��ͷ��->������߱���Ϊָ�룻
		  ��ţ�.������߱���Ϊʵ�塣*/
	}
	else
	{
		for ( pxIterator = ( ListItem_t * ) & ( pxList->xListEnd );
				pxIterator->pxNext->xItemValue <= xValueOfInsertion;
				pxIterator = pxIterator->pxNext )
		{
			//û��������������ϵ���ֻΪ���ҵ��ڵ�Ҫ�����λ��
		}
	}
	//�����������У����ڵ����
	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;
	
	//��ס�ýڵ����ڵ�����
	pxNewListItem->pvContainer = ( void * ) pxList;
	
	//�ڵ������++
	( pxList->uxNumberOfItems )++;
}

//���ڵ������ɾ��
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove)
{
	//��ȡ�ڵ����ڵ�����
	List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;
	//��ָ���Ľڵ������ɾ��
	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;
	
	//��������Ľڵ�����ָ��,�������������Ҫɾ���ģ���ô������ǰһ���ڵ�,������Ҫ�仯
	if ( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}
	
	//��ʼ���ýڵ����ڵ�����Ϊ�գ���ʾ�ýڵ㻹û�в����κ�����
	pxItemToRemove->pvContainer = NULL;
	
	//����ڵ������--
	( pxList->uxNumberOfItems )--;
	
	//��������ʣ��ڵ�ĸ���
	return pxList->uxNumberOfItems;
	
}
