#include "./Slist.h"
#include "../DataType/DataType.h"
#include <stdio.h>
#include <stdlib.h>
void printSlist(struct ds_Slist *list)
{
	if (list == NULL)
	{
		printf("List is NULL\n");
		return;
	}
	struct ds_SlistNode *tempnode = list->headNode->next;
	while (tempnode)
	{
		printf("%d->", tempnode->data->ds_int);
		tempnode = tempnode->next;
	}
}

int main(void)
{
	ds_Slist *list = ds_InitSlist();
	for (int i = 0; i < 9; i++)
	{
		ds_DataType *node_data;
		node_data = (ds_DataType *)malloc(sizeof(ds_DataType));
		node_data->ds_int = i;
		list->AfterInster(list, node_data);
	}
	for (int i = 0; i < 5; i++)
		list->DelNode(list, list->headNode->next);

	for (int i = 0; i < 10; i++)
	{
		ds_DataType *node_data;
		node_data = (ds_DataType *)malloc(sizeof(ds_DataType));
		node_data->ds_int = 999;
		list->AfterInster(list, node_data);
	}
	for (int i = 0; i < 10; i++)
	{
		ds_DataType *node_data;
		node_data = (ds_DataType *)malloc(sizeof(ds_DataType));
		node_data->ds_int = 888;
		list->BeforeInster(list, node_data);
	}
	printSlist(list);
	printf("\n");

	for (int i = 0; i < 10; i++)
	{
		ds_DataType *node_data;
		node_data = (ds_DataType *)malloc(sizeof(ds_DataType));
		node_data->ds_int = 111;
		list->InsterNode(list, list->headNode, node_data);
	}

	printSlist(list);
	printf("\n");
	list->Reverse(list);
	printSlist(list);
	printf("\n");
	list->Free(&list);
	printSlist(list);
	return 0;
}
