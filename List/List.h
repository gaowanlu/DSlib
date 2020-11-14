#ifndef __LIST_H__
#define __LIST_H__
#include<stdio.h>
#include<stdlib.h>
#include"../DataType/DataType.h"
struct ds_Slist;
struct ds_Slist* ds_InitSlist(void);
struct ds_SlistNode;
struct ds_SlistNode* ds_Slist_BeforeInster(struct ds_Slist*Slist,union ds_DataType*InsterData);
struct ds_SlistNode* ds_Slist_AfterInster(struct ds_Slist*Slist,union ds_DataType*InsterData);
void   ds_Slist_Free(struct ds_Slist*Slist);
int    ds_Slist_DelNode(struct ds_Slist*Slist,struct ds_SlistNode*DelNode);


typedef struct ds_SlistNode{
	union ds_DataType *data;
	struct ds_SlistNode*next;
}ds_SlistNode;


typedef struct ds_Slist{
	struct ds_SlistNode* headNode;
	struct ds_SlistNode* endNode;
	struct ds_SlistNode* (*BeforeInster)(struct ds_Slist*Slist,union ds_DataType*InsterData);
	struct ds_SlistNode* (*AfterInster)(struct ds_Slist*Slist,union ds_DataType*InsterData);
	void   (*Free)(struct ds_Slist*Slist);
	int    (*DelNode)(struct ds_Slist*Slist,struct ds_SlistNode*DelNode);
}ds_Slist;



struct ds_Slist* ds_InitSlist(void){
	struct ds_Slist*Slist;
	Slist=(struct ds_Slist*)malloc(sizeof(struct ds_Slist)*1);
	if(!Slist){//内存申请失败
		return NULL;
	}
	Slist->headNode=(struct ds_SlistNode*)malloc(sizeof(struct ds_SlistNode)*1);
	if(!(Slist->headNode)){//申请内存失败
		free(Slist);
		return NULL;
	}
	Slist->endNode=Slist->headNode;
	Slist->headNode->next=NULL;
	//函数指针,指向
	Slist->BeforeInster=ds_Slist_BeforeInster;
	Slist->Free=ds_Slist_Free;
	Slist->AfterInster=ds_Slist_AfterInster;
	Slist->DelNode=ds_Slist_DelNode;
	return Slist;
}



struct ds_SlistNode* ds_Slist_BeforeInster(struct ds_Slist*Slist,union ds_DataType*InsterData){
	if(!Slist||!InsterData){
		return NULL;
	}
	struct ds_SlistNode*newNode;
	newNode=(struct ds_SlistNode*)malloc(sizeof(struct ds_SlistNode)*1);
	if(!newNode){//内存申请失败
		return NULL;
	}
	newNode->data=InsterData;
	newNode->next=Slist->headNode->next;
	if(Slist->headNode->next==NULL){//更新尾指针
		Slist->endNode=newNode;
	}
	Slist->headNode->next=newNode;
	return newNode;
}


struct ds_SlistNode* ds_Slist_AfterInster(struct ds_Slist*Slist,union ds_DataType*InsterData){
	if(!Slist||!InsterData){
		return NULL;
	}
	struct ds_SlistNode*newNode;
	newNode=(struct ds_SlistNode*)malloc(sizeof(struct ds_SlistNode)*1);
	if(!newNode){
		return NULL;
	}
	Slist->endNode->next=newNode;
	newNode->data=InsterData;
	newNode->next=NULL;
	Slist->endNode=newNode;
	return newNode;
}

int    ds_Slist_DelNode(struct ds_Slist*Slist,struct ds_SlistNode*DelNode){
	if(!Slist||!DelNode){
		return 0;
	}
	struct ds_SlistNode*BeforeNode=Slist->headNode;
	struct ds_SlistNode*AfterNode=Slist->headNode->next;
	while(AfterNode&&AfterNode!=DelNode){
		BeforeNode=AfterNode;
		AfterNode=AfterNode->next;
	}
	if(AfterNode==DelNode&&AfterNode->next==NULL){//修改尾节点指针
		Slist->endNode=BeforeNode;
		BeforeNode->next=NULL;
	}
	if(AfterNode==DelNode){
		BeforeNode->next=AfterNode->next;
		free(AfterNode->data);
		free(AfterNode);
	}
	return 1;
}

void   ds_Slist_Free(struct ds_Slist*Slist){
	if(!Slist){
		return;
	}
	struct ds_SlistNode* TempSlistNode=Slist->headNode;
	while(TempSlistNode){
		struct ds_SlistNode*FreeNode=TempSlistNode;
		TempSlistNode=TempSlistNode->next;
		free(FreeNode);
	}
}

















#endif
