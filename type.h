#ifndef __TYPE_H__
#define __TYPE_H__
union _SeqList_node{
	int data_int;
	float data_float;
	char data_char;
	double data_double;
};
struct _SeqList{
	size_t size;
	union _SeqList_node*data;
	struct _SeqList* (*getLength)(struct _SeqList*List);
};
#endif





