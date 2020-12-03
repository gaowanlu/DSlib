#include "./SeqList.h"
int main(void)
{
	ds_SeqList *list = ds_InitSeqList(30);
	int i = 0;
	union ds_DataType *data=(union ds_DataType*)malloc(sizeof(union ds_DataType)*1);
	for (i = 0; i < 10; i++)
	{
		data->ds_int = 8989;
		list->Push(list, data);
	}
	for(i=0;i<9;i++){
		data->ds_int=i;
		list->Add(list,data);
	}
	for (i = 0; i < 10; i++)
	{
		data->ds_int = 8989;
		list->Push(list, data);
	}
	data->ds_int = 1111;
	list->Insert(list,list->cur-1,data);
	for(i=0;i<10;i++)
	list->Del(list,0);
	for (i = 0; i < list->cur; i++)
	{
		printf("%d\n", list->data[i].ds_int);
	}
	free(list->data);
	free(list);
	return 0;
}
