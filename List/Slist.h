#ifndef __SLIST_H__
#define __SLIST_H__
#include <stdio.h>
#include <stdlib.h>
#include "../DataType/DataType.h"

struct ds_Slist;
struct ds_Slist *ds_InitSlist(void);
struct ds_SlistNode;
struct ds_SlistNode *ds_Slist_BeforeInster(struct ds_Slist *Slist, union ds_DataType *InsterData);
struct ds_SlistNode *ds_Slist_AfterInster(struct ds_Slist *Slist, union ds_DataType *InsterData);
void ds_Slist_Free(struct ds_Slist **Slist);
bool ds_Slist_DelNode(struct ds_Slist *Slist, struct ds_SlistNode *DelNode);
struct ds_SlistNode *ds_Slist_InsterNode(struct ds_Slist *Slist, struct ds_SlistNode *BeforeNode, union ds_DataType *InsterNode);
bool ds_Slist_Reverse(struct ds_Slist *Slist);

typedef struct ds_SlistNode
{
	union ds_DataType *data;
	struct ds_SlistNode *next;
} ds_SlistNode;

typedef struct ds_Slist
{
	struct ds_SlistNode *headNode;
	struct ds_SlistNode *endNode;
	struct ds_SlistNode *(*BeforeInster)(struct ds_Slist *Slist, union ds_DataType *InsterData);
	struct ds_SlistNode *(*AfterInster)(struct ds_Slist *Slist, union ds_DataType *InsterData);
	void (*Free)(struct ds_Slist **Slist);
	bool (*DelNode)(struct ds_Slist *Slist, struct ds_SlistNode *DelNode);
	struct ds_SlistNode *(*InsterNode)(struct ds_Slist *Slist, struct ds_SlistNode *BeforeNode, union ds_DataType *InsterNode);
	bool (*Reverse)(struct ds_Slist *Slist);

} ds_Slist;

struct ds_Slist *ds_InitSlist(void)
{
	struct ds_Slist *Slist;
	Slist = (struct ds_Slist *)malloc(sizeof(struct ds_Slist) * 1);
	if (!Slist)
	{ //内存申请失败
		return NULL;
	}
	Slist->headNode = (struct ds_SlistNode *)malloc(sizeof(struct ds_SlistNode) * 1);
	if (!(Slist->headNode))
	{ //申请内存失败
		free(Slist);
		return NULL;
	}
	Slist->endNode = Slist->headNode;
	Slist->headNode->next = NULL;
	//函数指针,指向
	Slist->BeforeInster = ds_Slist_BeforeInster;
	Slist->Free = ds_Slist_Free;
	Slist->AfterInster = ds_Slist_AfterInster;
	Slist->DelNode = ds_Slist_DelNode;
	Slist->InsterNode = ds_Slist_InsterNode;
	Slist->Reverse = ds_Slist_Reverse;
	return Slist;
}

struct ds_SlistNode *ds_Slist_BeforeInster(struct ds_Slist *Slist, union ds_DataType *InsterData)
{
	if (!Slist || !InsterData)
	{
		return NULL;
	}
	struct ds_SlistNode *newNode;
	newNode = (struct ds_SlistNode *)malloc(sizeof(struct ds_SlistNode) * 1);
	if (!newNode)
	{ //内存申请失败
		return NULL;
	}
	newNode->data = InsterData;
	newNode->next = Slist->headNode->next;
	if (Slist->headNode->next == NULL)
	{ //更新尾指针
		Slist->endNode = newNode;
	}
	Slist->headNode->next = newNode;
	return newNode;
}

struct ds_SlistNode *ds_Slist_AfterInster(struct ds_Slist *Slist, union ds_DataType *InsterData)
{
	if (!Slist || !InsterData)
	{
		return NULL;
	}
	struct ds_SlistNode *newNode;
	newNode = (struct ds_SlistNode *)malloc(sizeof(struct ds_SlistNode) * 1);
	if (!newNode)
	{
		return NULL;
	}
	Slist->endNode->next = newNode;
	newNode->data = InsterData;
	newNode->next = NULL;
	Slist->endNode = newNode;
	return newNode;
}

bool ds_Slist_DelNode(struct ds_Slist *Slist, struct ds_SlistNode *DelNode)
{
	if (!Slist || !DelNode)
	{
		return false;
	}
	struct ds_SlistNode *BeforeNode = Slist->headNode;
	struct ds_SlistNode *AfterNode = Slist->headNode->next;
	while (AfterNode && AfterNode != DelNode)
	{
		BeforeNode = AfterNode;
		AfterNode = AfterNode->next;
	}
	if (AfterNode == DelNode && AfterNode->next == NULL)
	{ //修改尾节点指针
		Slist->endNode = BeforeNode;
		BeforeNode->next = NULL;
	}
	if (AfterNode == DelNode)
	{
		BeforeNode->next = AfterNode->next;
		free(AfterNode->data);
		free(AfterNode);
	}
	return true;
}

struct ds_SlistNode *ds_Slist_InsterNode(struct ds_Slist *Slist, struct ds_SlistNode *BeforeNode, union ds_DataType *InsterNode)
{ //在某个节点的后面插入新的节点
	//要在链表中搜索这个节点,因为可能链表中没有这个节点
	struct ds_SlistNode *TempNode;
	TempNode = Slist->headNode;
	while (TempNode && TempNode != BeforeNode)
	{
		TempNode = TempNode->next;
	}
	if (TempNode == BeforeNode)
	{
		if (TempNode->next == NULL)
		{ //如果在尾节点后面插入新的节点，要改变尾指针
			struct ds_SlistNode *newNode = NULL;
			newNode = (struct ds_SlistNode *)malloc(sizeof(struct ds_SlistNode) * 1);
			if (!newNode)
			{ //内存申请失败
				return NULL;
			}
			newNode->data = InsterNode;
			newNode->next = TempNode->next;
			TempNode->next = newNode;
			Slist->endNode = newNode;
			return newNode;
		}
		else
		{ //不是尾节点
			struct ds_SlistNode *newNode = NULL;
			newNode = (struct ds_SlistNode *)malloc(sizeof(struct ds_SlistNode) * 1);
			if (!newNode)
			{ //内存申请失败
				return NULL;
			}
			newNode->data = InsterNode;
			newNode->next = TempNode->next;
			TempNode->next = newNode;
			return newNode;
		}
	}
	return NULL;
}

bool ds_Slist_Reverse(struct ds_Slist *Slist)
{
	if (!Slist)
	{ //链表为空
		return 0;
	}
	struct ds_SlistNode *TempNode = NULL;
	TempNode = Slist->headNode->next;
	Slist->headNode->next = NULL;
	while (TempNode)
	{
		if (Slist->headNode->next == NULL)
		{ //要改变尾指针
			Slist->endNode = TempNode;
			TempNode = TempNode->next;
			Slist->endNode->next = NULL;
			Slist->headNode->next = Slist->endNode;
		}
		else
		{
			struct ds_SlistNode *p = TempNode;
			TempNode = TempNode->next;
			p->next = Slist->headNode->next;
			Slist->headNode->next = p;
		}
	}
	return 1;
}

void ds_Slist_Free(struct ds_Slist **list)
{
	if (!list)
	{
		return;
	}
	struct ds_Slist *Slist = *list;
	if (!Slist)
	{
		return;
	}
	struct ds_SlistNode *TempSlistNode = Slist->headNode;
	while (TempSlistNode)
	{
		struct ds_SlistNode *FreeNode = TempSlistNode;
		TempSlistNode = TempSlistNode->next;
		free(FreeNode->data);
		free(FreeNode);
	}
	*list = NULL;
}

#endif
