#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#ifndef __DSLIB_H__
#define __DSLIB_H__

//顺序表
#ifndef ___SeqList__
#define ___SeqList__
union _SeqList_node;
struct _SeqList;
struct _SeqList* _SeqList_getMemory(struct _SeqList**List);
struct _SeqList* _SeqList_clear(struct _SeqList**List);
struct _SeqList* _SeqList_init(struct  _SeqList**List);
struct _SeqList* _SeqList_inster(struct _SeqList**List,size_t num,union _SeqList_node inster_node,int flag);
struct _SeqList* _SeqList_delete(struct _SeqList**List,size_t num,int flag);
union _SeqList_node{
	int data_int;
	float data_float;
	char data_char;
	double data_double;
};
struct _SeqList{
	size_t size;
	union _SeqList_node*data;
	struct _SeqList* (*getMemory)(struct _SeqList**List);
	struct _SeqList* (*clear)(struct _SeqList**List);
	struct _SeqList* (*inster)(struct _SeqList**List,size_t num,union _SeqList_node intser_node,int flag);
	struct _SeqList* (*delete)(struct _SeqList**List,size_t num,int flag);
};
struct _SeqList* _SeqList_getMemory(struct _SeqList**List){
	if(!List||!((*List)->size)){
		return NULL;
	}
	(*List)->data=(union _SeqList_node*)malloc(sizeof(union _SeqList_node)*((*List)->size));
	if(!((*List)->data)){
		return NULL;
	}
	return *List;
};
struct _SeqList* _SeqList_clear(struct _SeqList**List){
	if(!List){
		return NULL;
	}
	//to free
	free((*List)->data);
	(*List)->data=NULL;
	(*List)->size=0;
	return *List;
}
struct _SeqList* _SeqList_init(struct _SeqList**List){
	if(!List){
		return NULL;
	}
	//对二维指针申请内存，并将结构体内部的函数指针指向相应的函数
	*List=(struct _SeqList*)malloc(sizeof(struct _SeqList)*1);
	if(!*List){
		return NULL;
	}
	(*List)->getMemory=_SeqList_getMemory;
	(*List)->clear=_SeqList_clear;
	(*List)->inster=_SeqList_inster;
	(*List)->delete=_SeqList_delete;
	//表长初始化为零
	(*List)->size=0;
	return *List;
}
struct _SeqList* _SeqList_inster(struct _SeqList**List,size_t num,union _SeqList_node inster_node,int flag){
	if(!List){
		return NULL;
	}
	//flag==1则延长表长，向后推
	if(flag==1){
		if(num>=0||num<=(*List)->size){//符合插入的位置
			//则需要在原先表的基础之上扩大一个表长,采用数据暂存
			struct _SeqList*temp_List;
			_SeqList_init(&temp_List);
			temp_List->size=(*List)->size;
			temp_List->getMemory(&temp_List);
			if(!temp_List){
				return NULL;
			}
			//将List中的数据暂时备份在temp_List
			for(size_t i=0;i<(*List)->size;++i){//进行数据拷贝
				*(temp_List->data+i)=*((*List)->data+i);
			}
			//数据拷贝完毕,需要将原来的表进行内存扩展,使用realloc进行扩展data内存，以至于新的元素进行插入
			//规定在下标num处进行插入，num的范围即下标范围为[0,(*List)->size]
			//特殊情况：num==0则是前插入，num==0则是后插入
			//进行重新申请内存
			(*List)->data=(union _SeqList_node*)realloc((*List)->data,sizeof(union _SeqList_node)*((*List)->size+1));
			if(!(*List)->data){
				return NULL;
			}
			(*List)->size+=1;
			//内存扩展完毕
			//进行数据转移
			size_t old_num=0;//记录temp_List内的数据转移的进度
			for(size_t i=0;i<(*List)->size;++i){
				if(num==i){//如果等于插入的下标位置，则插入新的数据内容
					*((*List)->data+i)=inster_node;
				}else{//插入老的数据，内容
					*((*List)->data+i)=*(temp_List->data+old_num);
					++old_num;
				}
			}
			//插入完毕
		}else{//不符合的插入位置
			return NULL;
		}
	}
	//flag==0则不延长表，直接向后移动，如果表的每个空间都有数据，则会丢失最后一个数据
	else if(flag==0){
		//允许插入的下标范围是[0,size-1],只能在原有的空间进行插入
		if(num>=0&&num<(*List)->size){
			//进行数据的备份
			struct _SeqList*temp_List;
			_SeqList_init(&temp_List);
			temp_List->size=(*List)->size;
			temp_List->getMemory(&temp_List);
			if(!temp_List){
				return NULL;
			}
			for(size_t i=0;i<(*List)->size;++i){
				*(temp_List->data+i)=*((*List)->data+i);
			}
			//进行循环，遇到num下标则进行插入
			size_t old_num=0;//记录temp_List内数据转移的进度
			for(size_t i=0;i<(*List)->size;++i){
				if(num==i){
					*((*List)->data+i)=inster_node;
				}else{//转移老的数据
					*((*List)->data+i)=*(temp_List->data+old_num);
					++old_num;
				}
			}
		}else{
			return NULL;
		}
	}
	return *List;
}



struct _SeqList* _SeqList_delete(struct _SeqList**List,size_t num,int flag){
	if(!List){
		return NULL;
	}
	//下标num限制
	if(num<0||num>=(*List)->size){
		return NULL;
	}
	//分为两种情况,删除一个则表内存空间减一，或者直接进行赋空
	//flag==1则删除且内存减一,flag==0则是赋空操作
	if(flag==1){
		//进行内容拷贝
		struct _SeqList*temp_List;
		_SeqList_init(&temp_List);
		temp_List->size=(*List)->size;
		temp_List->getMemory(&temp_List);
		if(!temp_List){
			return NULL;
		}
		for(size_t i=0;i<(*List)->size;++i){
			*(temp_List->data+i)=*((*List)->data+i);
		}
		//释放List 表内存，重新申请，表长减一
		if((*List)->size-1>=0){
			free((*List)->data);
			(*List)->data=NULL;
			(*List)->data=(union _SeqList_node*)malloc(sizeof(union _SeqList_node)*((*List)->size-1));
			if(!(*List)->data){
				return NULL;
			}
			(*List)->size-=1;
			size_t new_num=0;//记录转移进度
			for(size_t i=0;i<temp_List->size;++i){
				if(i==num){
				}else{
					*((*List)->data+new_num)=*(temp_List->data+i);
					new_num+=1;
				}
			}
		}else{
			return NULL;
		}

	}else if(flag==0){
		union _SeqList_node null_node;
		*((*List)->data+num)=null_node;//表的长度不变
	}
}
#endif


//字符串
#ifndef ___String__
#define ___String__
struct _String;
struct _String* _String_init(struct _String**string);
struct _String* _String_set(struct _String**string,char*data);
struct _String* _String_clear(struct _String**string);
struct _String{
	char*data;
	size_t size;
	struct _String* (*set)(struct _String**string,char*data);
	struct _String* (*clear)(struct _String**string);
};
struct _String* _String_init(struct _String**string){
	if(!string){
		return NULL;
	}
	//为一维指针申请一个空间
	*string=(struct _String*)malloc(sizeof(struct _String)*1);
	if(!*string){//内存申请失败
		return NULL;
	}
	//函数指针指向相应函数
	(*string)->set=_String_set;
	(*string)->clear=_String_clear;
	//字符串长度初始化为零
	(*string)->size=0;
	return *string;
}

struct _String* _String_set(struct _String**string,char*data){
	if(!string||!data){
		return NULL;
	}
	size_t data_size=strlen(data);
	//如果string->data不为NULL则进行内存释放
	if((*string)->data!=NULL){
		free((*string)->data);
		(*string)->data=NULL;
	}
	//为*string->data重新申请内存
	(*string)->data=(char*)malloc(sizeof(char)*data_size);
	if(!(*string)->data){
		return NULL;
	}
	//字符复制
	for(size_t i=0;i<data_size;++i){
		*((*string)->data+i)=*(data+i);
	}
	//字符号长度更新
	(*string)->size=data_size;
	return *string;
}

struct _String* _String_clear(struct _String**string){
	if(!string){
		return NULL;
	}
	//释放字符串指针的空间
	if(!(*string)->data){
		return NULL;
	}
	free((*string)->data);
	(*string)->data=NULL;
	(*string)->size=0;
	return *string;
}

#endif

#endif

