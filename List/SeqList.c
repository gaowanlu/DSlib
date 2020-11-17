#include "./SeqList.h"
int main(void)
{
	ds_SeqList *list = ds_InitSeqList(10);
	for (int i = 0; i < list->length; i++)
	{
		list->data[i].ds_int = i;
	}
	union ds_DataType *data=(union ds_DataType*)malloc(sizeof(union ds_DataType)*1);
	for(int i=0;i<10;i++){
		data->ds_int=i;
		list->Add(list,data);
	}


	for (int i = 0; i < list->length; i++)
	{
		printf("%d\n", list->data[i].ds_int);
	}
	free(list->data);
	free(list);
	return 0;
}
