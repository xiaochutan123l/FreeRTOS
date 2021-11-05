/*
************************************************************************
* 								main 
************************************************************************
*/

#include "list.h"

/*
************************************************************************
* 								ȫ�ֱ��� 
************************************************************************
*/

//���� ������ڵ�
struct xLIST		List_Test;


//����ڵ�
struct xLIST_ITEM	List_Item1;
struct xLIST_ITEM	List_Item2;
struct xLIST_ITEM	List_Item3;

/*
************************************************************************
* 								main ����
************************************************************************
*/

int main (void)
{
	
	//������ڵ��ʼ��
	vListInitialise( &List_Test );
	
	//�ڵ�1��ʼ��
	vListInitialiseItem( &List_Item1 );
	List_Item1.xItemValue = 1;
	
	//�ڵ�2��ʼ��
	vListInitialiseItem( &List_Item2 );
	List_Item2.xItemValue = 2;
	
	//�ڵ�3��ʼ��
	vListInitialiseItem( &List_Item3 );
	List_Item3.xItemValue = 3;
	
	//���ڵ������������������������
	vListInsert( &List_Test, &List_Item1 );
	vListInsert( &List_Test, &List_Item2 );
	vListInsert( &List_Test, &List_Item3 );
	
	for (;;)
	{
		/* do nothing */
	}
}
