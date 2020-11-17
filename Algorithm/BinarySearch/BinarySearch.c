#include "/media/gaowanlu/DIST1/DSlib/DataType/DataType.h"
#include "/media/gaowanlu/DIST1/DSlib/List/SeqList.h"

int find(ds_SeqList *list, int x, int low, int high)
{
	//递归结束条件
	if (low > high)
	{
		return -1; //没有找到
	}
	//计算中间位置
	int middle = (low + high) / 2;
	if (x == list->data[middle].ds_int)
	{
		return middle;
	}
	else if (x < list->data[middle].ds_int)
	{
		return find(list, x, low, middle - 1);
	}
	else
	{
		return find(list, x, middle + 1, high);
	}
}

int main(void)
{
	ds_SeqList *list = ds_InitSeqList(100);
	for (int i = 0; i < 100; i++)
	{
		list->data[i].ds_int = i;
	}
	printf("[");
	for (int i = 0; i < 100; i++)
	{
		printf("%d", list->data[i].ds_int);
		if (i != 99)
		{
			printf(",");
		}
	}
	printf("]\n");
	while (1)
	{
		int findNum;
		char enter;
		scanf("%d", &findNum);
		scanf("%c", &enter);
		if (findNum < 0)
		{
			printf("程序结束\n");
			break;
		}
		printf("%d\n", find(list, findNum, 0, 99));
	}

	return 0;
}
