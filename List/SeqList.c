#include "./SeqList.h"
int main(void)
{
	ds_SeqList *list = ds_InitSeqList(10);
	for (int i = 0; i < list->length; i++)
	{
		list->data[i].ds_int = i;
	}
	for (int i = 0; i < list->length; i++)
	{
		printf("%d\n", list->data[i].ds_int);
	}
	free(list->data);
	free(list);
	return 0;
}
