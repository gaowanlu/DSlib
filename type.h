
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
struct _SeqList* _SeqList_inster(struct _SeqList**List,size_t num,union _SeqList_node inster_node,int flag){
	//flag==1则延长表长，向后推
	if(flag==1){
		if(num>=0||num<=(*List)->size-1){//符合插入的位置
			//则需要在原先表的基础之上扩大一个表长,采用数据暂存
			struct _SeqList*temp_List;
			_SeqList_init(&temp_List);
			temp_List->size=(*List)->size;
			temp_List->getLength(&temp_List);
			//将List中的数据暂时备份在temp_List

		}else{//不符合的插入位置
			return NULL;
		}



	}
	//flag==0则不延长表，直接向后，表尾数据可能丢失
	else if(flag==0){



	}


	return List;
}
#endif





