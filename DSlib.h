#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#ifndef __DSLIB_H__
#define __DSLIB_H__

//顺序表
union _SeqList_node;
struct _SeqList;
struct _SeqList* _SeqList_getMemory(struct _SeqList**List);
struct _SeqList* _SeqList_clear(struct _SeqList**List);
struct _SeqList* _SeqList_init(struct  _SeqList**List);
struct _SeqList* _SeqList_inster(struct _SeqList**List,size_t num,union _SeqList_node inster_node,int flag);
struct _SeqList* _SeqList_delete(struct _SeqList**List,size_t num,int flag);
void             _SeqList_free(struct _SeqList**List);
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
	void             (*free)(struct _SeqList**List);
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
	(*List)->free=_SeqList_free;
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

void _SeqList_free(struct _SeqList**List){
	if(!List){
		return ;
	}
	//将data指针申请的内存释放
	free((*List)->data);
	(*List)->data=NULL;
	//将*List释放
	free(*List);
	*List=NULL;
	return ;
}


//字符串
struct _String;
struct _String* _String_init(struct _String**string);
struct _String* _String_set(struct _String**string,char*data);
struct _String* _String_clear(struct _String**string);
char**          _String_get(struct _String**string);
void            _String_free(struct _String**string);
void            _String_print(struct _String**string);
char**          _String_reverse(struct _String**string);
void            _String_copy(struct _String**string_1,struct _String**string_2);
size_t          _String_bf(struct _String**string_1,struct _String**string_2);
size_t          _String_kmp(struct _String**string_1,struct _String**stirng_2);
struct _String{
	char*data;
	size_t size;
	struct _String* (*set)(struct _String**string,char*data);
	struct _String* (*clear)(struct _String**string);
	char**          (*get)(struct _String**string);
	void            (*free)(struct _String**string);
	void            (*print)(struct _String**string);
	char**          (*reverse)(struct _String**string);
	void            (*copy)(struct _String**string_1,struct _String**stirng_2);
	size_t          (*bf)(struct _String**string_1,struct _String**string_2);
	size_t          (*kmp)(struct _String**string_1,struct _String**string_2);
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
	(*string)->get=_String_get;
	(*string)->free=_String_free;
	(*string)->print=_String_print;
	(*string)->reverse=_String_reverse;
	(*string)->copy=_String_copy;
	(*string)->bf=_String_bf;
	(*string)->kmp=_String_kmp;
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


char** _String_get(struct _String**string){
	if(!string){
		return NULL;
	}
	return &((*string)->data);
}


void _String_free(struct _String**string){
	if(!string){
		return ;
	}
	//销毁对象
	free(*string);
	*string=NULL;
	return ;
}

void _String_print(struct _String**string){
	if(!string){
		return ;
	}
	//打印data
	if((*string)->data)
	printf("%s\n",(*string)->data);
	return ;
}

char** _String_reverse(struct _String**string){
	//将data倒置
	if(!string||!(*string)->data||(*string)->size==0){
		return NULL;
	}
	size_t before=0;
	size_t after=(*string)->size-1;
	while(before<=after){
		char temp;
		temp=*((*string)->data+before);
		*((*string)->data+before)=*((*string)->data+after);
		*((*string)->data+after)=temp;
		before+=1;
		after-=1;
	}
	return &((*string)->data);
}

void _String_copy(struct _String**string_1,struct _String**string_2){
	if(!string_1||!string_2||!(*string_2)){
		return ;
	}
	(*string_2)->set(string_2,*((*string_1)->get(string_1)));
	return ;
}

size_t _String_kmp(struct _String**string_1,struct _String**string_2){
	//kmp字符串匹配算法，在string_1内s搜索string_2
	if(!string_1||!string_2||!(*string_1)||!(*string_2)){
		return -1;
	}
	if((*string_1)->size<=0||(*string_1)<=0||(*string_1)->size<(*string_2)->size||(*string_1)->size==0||(*string_2)->size==0){
		return -1;
	}
	char *string=(*string_1)->data;
	char *find_string=(*string_2)->data;
	//进行创建next数组
	size_t *next;
	next=(size_t *)malloc(sizeof(size_t)*((*string_2)->size+1));
	if(!next){
		return -1;
	}
	//动态规划得到next数组
	if(1){
		//temp_string
		char*temp_string;
		//复制字符串
		temp_string=(char*)malloc(sizeof(char)*((*string_2)->size+1));
		if(!temp_string){
			return -1;
		}
		temp_string[0]=' ';
		for(size_t i=1;i<((*string_2)->size+1);++i){
			temp_string[i]=*((*string_2)->data+i-1);
		}
		//利用temp_string寻找next数组
		size_t j=1,k=0;
		next[1]=0;
		while(j<((*string_2)->size+1)){
			/*next
			if(k==0||temp_string[j]==temp_string[k]){
				next[++j]=++k;
			}else{
				k=next[k];
			}*/
			//nextval
			if(k==0||temp_string[j]==temp_string[k]){
				++k;
				++j;
				if(temp_string[j]==temp_string[k]){
					next[j]=next[k];
				}else{
					next[j]=k;
				}
			}else{
				k=next[k];
			}

		}
		//输出next数组
		//for(size_t i=1;i<((*string_2)->size+1);++i){
		//	printf("%ld",next[i]);
		//}
		//printf("\n");
		//free(temp_string);
		//temp_string=NULL;
	}
	//kmp匹配
	size_t result=-1;
	if(1){	
		char*temp_string_1;
		//复制字符串
		temp_string_1=(char*)malloc(sizeof(char)*((*string_1)->size+1));
		if(!temp_string_1){
			return -1;
		}
		temp_string_1[0]=' ';
		for(size_t i=1;i<((*string_1)->size+1);++i){
			temp_string_1[i]=*((*string_1)->data+i-1);
		}
		char*temp_string_2;
		//复制字符串
		temp_string_2=(char*)malloc(sizeof(char)*((*string_2)->size+1));
		if(!temp_string_2){
			return -1;
		}
		temp_string_2[0]=' ';
		for(size_t i=1;i<((*string_2)->size+1);++i){
			temp_string_2[i]=*((*string_2)->data+i-1);
		}
		//在temp_string_1内找temp_string_2
		size_t i=1,j=1;
		while(i<=((*string_1)->size)&&j<=((*string_2)->size)){
			if(j==0||temp_string_1[i]==temp_string_2[j]){
				++i;
				++j;
			}else{
				j=next[j];
			}
		}
		if(j>((*string_2)->size)){
			result=i-((*string_2)->size)-1;
		}else{
			result=-1;
		}
	}
	return result;
}

size_t _String_bf(struct _String**string_1,struct _String**string_2){
	//bf字符串暴力匹配算法,在string_1内搜索string_2
	size_t result=-1;
	//df
	if(!string_1||!string_2||!(*string_1)||!(*string_2)){
		return -1;
	}
	if((*string_1)->size<=0||(*string_1)<=0||(*string_1)->size<(*string_2)->size||(*string_1)->size==0||(*string_2)->size==0){
		return -1;
	}
	char *string=(*string_1)->data;
	char *find_string=(*string_2)->data;
	size_t i=0,j=0,k=0;
	for(i=0;i<(*string_2)->size;++i){
		int status=0;
		for(j=0;j<=(*string_1)->size-(*string_2)->size;++j){
			//printf("%c",*((*string_1)->data+j));
			if(*((*string_1)->data+j) == *((*string_2)->data+i)){//向后匹配
				size_t i_num=i,j_num=j;
				for(;i_num<(*string_2)->size;){
					if(*((*string_1)->data+j_num)!=*((*string_2)->data+i_num)){
						break;
					}
					i_num++;
					j_num++;
				}
				if(i_num==(*string_2)->size){
					result=j;
					status=1;
				}
			}
			if(status){
				break;
			}
		}
		if(status){
			break;
		}
	}
	return result;
}
#endif



