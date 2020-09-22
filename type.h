
#ifndef __TYPE_H__
#define __TYPE_H__
union _SeqList_node;
struct _SeqList;
struct _SeqList** getLength(struct _SeqList**List);
struct _SeqList** clear(struct _SeqList**List);
struct _SeqList** init(struct  _SeqList**List);
union _SeqList_node{
	int data_int;
	float data_float;
	char data_char;
	double data_double;
};
struct _SeqList{
	size_t size;
	union _SeqList_node*data;
	struct _SeqList** (*getLength)(struct _SeqList**List);
	struct _SeqList** (*clear)(struct _SeqList**List);
};
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
#endif





