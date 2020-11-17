#ifndef __SEQLIST_H__
#define __SEQLIST_H__


#include<stdio.h>
#include<stdlib.h>


#ifndef __DATATYPE_H__
#include"../DataType/DataType.h"
#endif


//@计划Function
//Free，Del，Inster，Reverse，ToString，ToSlist，Add,


struct ds_SeqList;
struct ds_SeqList* ds_InitSeqList(size_t length);

typedef struct ds_SeqList{
	union ds_DataType *data;
	size_t length;
	size_t cur;
}ds_SeqList;


struct ds_SeqList* ds_InitSeqList(size_t size){
	if(size<0){//申请空间小于0
		return NULL;
	}
	struct ds_SeqList*NewList=NULL;
	NewList=(struct ds_SeqList*)malloc(sizeof(struct ds_SeqList));
	if(!NewList){
		return NULL;
	}
	NewList->data=NULL;
	NewList->data=(union ds_DataType*)malloc(sizeof(union ds_DataType)*size);
	NewList->length=size;
	NewList->cur=0;
	return NewList;
}

#endif

