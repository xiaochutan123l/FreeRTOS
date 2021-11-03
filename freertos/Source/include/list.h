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


/*
************************************************************************
*                           �ڵ���κ�С����
************************************************************************
*/

//��ʼ���ڵ��ӵ����
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )\
		( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )
			
//��ȡ�ڵ�ӵ����
#define listGET_LIST_ITEM_OWNER( pxListItem )\
		( ( pxListItem )->pvOwner )
		
//��ʼ���ڵ�������ֵ
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )\
		( ( pxListItem )->xItemValue = ( xValue ) )
		
//��ȡ�ڵ�������ֵ
#define listGET_LIST_ITEM_VALUE( pxListItem )\
		( ( pxListItem )->xItemValue )
		
//��ȡ�����һ���Ľڵ��������ֵ
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )\
		( ( ( pxList )->xListEnd ).pxNext->xItemValue )
		
//��ȡ�������ڽڵ�
#define listGET_HEAD_ENTRY( pxList )\
		( ( ( pxList )->xListEnd ).pxNext )
		
//��ȡ�ڵ����һ���ڵ�
#define listGET_NEXT( pxListItem )\
		( ( pxListItem )->pxNext )
		
//��ȡ�������һ���ڵ�
#define listGET_END_MARKER( pxList )\
		( ( ListItem_t cons * ) ( &( ( pxList )->xListEnd ) ) )
		
//�ж������Ƿ�Ϊ��
#define listLIST_IS_EMPTY( pxList )\
		( ( BaseType_t ) ( ( pxList )->uxNumberOfItems == ( UBaseType_t ) 0 ) )

//��ȡ����Ľڵ���
#define listCURRENT_LIST_LENGTH( pxList )\
		( ( pxList )->uxNumberOfItems )

//��ȡ�������һ���ڵ��owner����TCB
#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )\
{													\
	List_t * const pxConstList = ( pxList );		\
	/*�ڵ�����ָ�������һ���ڵ�*/					\
	( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;	\
	/*�����һ���ڵ��Ǹ��ڵ㣨��һ���ڵ㣩����ô����ȥ*/			\
	if( ( void * ) ( pxConstList )->pxIndex == ( void * ) & ( ( pxConstList )->xListEnd ) )		\
	{																							\
		( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;							\
	}																							\
	( pxTCB ) = ( pxCOnstList )->pxIndex->pvOwner;												\
}

//��ȡ������ڽڵ��owner
#define listGET_OWNER_OF_HEAD_ENTRY( pxList )\
		( (&( pxList )->xListEnd ))->pxNext->pvOwner )


/*
************************************************************************
*                                ��������
************************************************************************
*/
void vListInitialise( List_t * const pxList );
void vListInitialiseItem ( ListItem_t * const pxItem );
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem );
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem );
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove);

#endif /* LIST_H */
