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
struct ds_SeqList* ds_InitSeqList(void);


typedef struct ds_SeqList{
	union ds_DataType *data;
	size_t length;
}ds_SeqList;


struct ds_SeqList* ds_InitSeqList(void){
	struct ds_SeqList*NewList=NULL;
	NewList=(struct ds_SeqList*)malloc(sizeof(struct ds_SeqList));
	if(!NewList){
		return NULL;
	}
	NewList->data=NULL;
	NewList->length=0;
	return NewList;
}

#endif

