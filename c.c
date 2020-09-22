#include<stdio.h>
#include<stdlib.h>
#include"type.h"
struct _SeqList** _SeqList_getLength(struct _SeqList**List){
	if(!*List||!((*List)->size)){
		return NULL;
	}
	(*List)->data=(union _SeqList_node*)malloc(sizeof(union _SeqList_node)*((*List)->size));
	if(!((*List)->data)){
		return NULL;
	}
	return List;
};
struct _SeqList** _SeqList_clear(struct _SeqList**List){
	if(!List){
		return NULL;
	}
	//to free
	free((*List)->data);
	(*List)->data=NULL;
	(*List)->size=0;
	return List;
}
struct _SeqList* _SeqList_init(struct _SeqList**List){
	//对二维指针申请内存，并将结构体内部的函数指针指向相应的函数
	*List=(struct _SeqList*)malloc(sizeof(struct _SeqList)*1);
	if(!*List){
		return 0;
	}
	(*List)->getLength=_SeqList_getLength;
	(*List)->clear=_SeqList_clear;
	return *List;
}
int main(void){
	struct _SeqList *List;
	_SeqList_init(&List);
	List->size=10;
	List->getLength(&List);
	int i=0;
	for(i=0;i<10;i++){
		(List->data+i)->data_int=i;
	}
	for(i=0;i<10;i++){
		printf("%d\n",(List->data+i)->data_int);
	}
	List->clear(&List);
	return 0;

}
