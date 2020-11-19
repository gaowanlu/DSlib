#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdio.h>
#include <stdlib.h>

#ifndef __DATATYPE_H__
#include "../DataType/DataType.h"
#endif

//@计划Function
//Free，Del，Inster，Reverse，ToString，ToSlist，Add,

struct ds_SeqList;
struct ds_SeqList *ds_InitSeqList(size_t length);
bool ds_SeqList_Empty(struct ds_SeqList *list);
bool ds_SeqList_Full(struct ds_SeqList *list);
union ds_DataType *ds_SeqList_Push(struct ds_SeqList *list, union ds_DataType *pushData);			  //不可增长
union ds_DataType *ds_SeqList_Add(struct ds_SeqList *list, union ds_DataType *addData);				  //自动增长
union ds_DataType *ds_SeqList_Insert(struct ds_SeqList *list, size_t num, union ds_DataType *addData); //在表中间插入
bool  ds_SeqList_Del(struct ds_SeqList *list, size_t num);									  //在表中删除下标为num的元素
typedef struct ds_SeqList
{
	union ds_DataType *data;
	size_t length;
	size_t cur;
	bool (*Empty)(struct ds_SeqList *list);
	bool (*Full)(struct ds_SeqList *list);
	union ds_DataType *(*Push)(struct ds_SeqList *list, union ds_DataType *pushData);
	union ds_DataType *(*Add)(struct ds_SeqList *list, union ds_DataType *addData);
	union ds_DataType *(*Insert)(struct ds_SeqList *list, size_t num, union ds_DataType *addData);
	bool (*Del)(struct ds_SeqList *list, size_t num);
} ds_SeqList;

struct ds_SeqList *ds_InitSeqList(size_t size)
{
	if (size < 0)
	{ //申请空间小于0
		return NULL;
	}
	struct ds_SeqList *NewList = NULL;
	NewList = (struct ds_SeqList *)malloc(sizeof(struct ds_SeqList));
	if (!NewList)
	{
		return NULL;
	}
	NewList->data = NULL;
	NewList->data = (union ds_DataType *)malloc(sizeof(union ds_DataType) * size);
	NewList->length = size;
	NewList->cur = 0;
	NewList->Empty = ds_SeqList_Empty;
	NewList->Full = ds_SeqList_Full;
	NewList->Push = ds_SeqList_Push;
	NewList->Insert = ds_SeqList_Insert;
	NewList->Del = ds_SeqList_Del;
	NewList->Add = ds_SeqList_Add;
	return NewList;
}

bool ds_SeqList_Empty(struct ds_SeqList *list)
{
	if (!list || !(list->data))
	{
		return false;
	}
	if (list->cur == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ds_SeqList_Full(struct ds_SeqList *list)
{
	if (!list || !(list->data))
	{
		return true;
	}
	if (list->cur == list->length)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//注意Add与Push的区别
union ds_DataType *ds_SeqList_Push(struct ds_SeqList *list, union ds_DataType *pushData)
{
	if (!list || !(list->data) || !pushData)
	{
		return NULL;
	}
	//在末尾添加新的元素
	if (list->Full(list))
	{
		return NULL;
	}
	list->data[list->cur] = *pushData;
	list->cur += 1;
	return (list->data + list->cur - 1);
}

//接受的内存地址，在使用后必须人工释放
union ds_DataType *ds_SeqList_Pop(struct ds_SeqList *list)
{
	if (!list || !(list->data))
	{
		return NULL;
	}
	//判断是否为空
	if (list->Empty(list))
	{
		return NULL;
	}
	else
	{ //不为空
		//申请一个新的空间把东西先拷贝下来
		union ds_DataType *temp = (union ds_DataType *)malloc(sizeof(union ds_DataType));
		if (!temp)
		{ //空间申请失败
			return NULL;
		}
		*temp = list->data[list->cur - 1];
		list->cur -= 1;
		return temp;
	}
}

union ds_DataType *ds_SeqList_Add(struct ds_SeqList *list, union ds_DataType *addData)
{
	if (!list || !(list->data) || !addData)
	{
		return NULL;
	}
	//判断是否已满
	if (list->Full(list))
	{
		//重新申请内存
		list->data = (union ds_DataType *)realloc(list->data, sizeof(union ds_DataType) * (list->length + 1));
		if (list->data == NULL)
		{
			return NULL;
		}
		else
		{
			list->data[list->cur] = *addData;
			list->length += 1;
			list->cur += 1;
		}
	}
	else
	{
		list->data[list->cur] = *addData;
		list->cur += 1;
	}
	return (list->data + list->cur - 1);
}

union ds_DataType *ds_SeqList_Insert(struct ds_SeqList *list, size_t num, union ds_DataType *addData)
{
	if (!list || !(list->data) || num < 0 || num > list->cur - 1)
	{
		return NULL;
	}
	//判断是否为满
	if (list->Full(list))
	{ //满了，将会采用内存扩展
		list->data = (union ds_DataType *)realloc(list->data, sizeof(union ds_DataType) * (list->length + 1));
		if (list->data == NULL)
		{
			return NULL;
		}
		//数据向后推
		size_t after = list->cur;
		while (after > num)
		{
			list->data[after] = list->data[after - 1];
			after -= 1;
		}
		list->data[num] = *addData;
		list->cur += 1;
		list->length += 1;
		return (list->data + num);
	}
	else
	{ //没满,直接插入
		size_t after = list->cur;
		while (after > num)
		{
			list->data[after] = list->data[after - 1];
			after -= 1;
		}
		list->cur += 1;
		list->data[num] = *addData;
		return (list->data + num);
	}
}

bool ds_SeqList_Del(struct ds_SeqList *list, size_t num)
{
	if (!list || !(list->data) || num < 0 || num >= list->cur)
	{
		return false;
	}
	size_t before = num;
	while (before < list->cur - 1)
	{
		list->data[before] = list->data[before + 1];
		before += 1;
	}
	list->cur -= 1;
}

#endif
