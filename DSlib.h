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
union _SeqList_node{
	int data_int;
	float data_float;
	char data_char;
	double data_double;
	struct _String* data_string;
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
			//将temp_List内存释放
			temp_List->free(&temp_List);
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
			//使用过temp_List后我们应该将其内存进行释放
			temp_List->free(&temp_List);
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
		//
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
			temp_List->free(&temp_List);
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
long long       _String_kmp(struct _String**string_1,struct _String**stirng_2,long long start);
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
	long long       (*kmp)(struct _String**string_1,struct _String**string_2,long long start);
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


//kmp调用库内部函数strat-----------------------
long long int* _String_kmp_get_next(char*string){
	if(!string){
		return NULL;
	}
	//申请与字符串同长的数组
	long long int*next=NULL;
	next=(long long int*)malloc(sizeof(long long int)*strlen(string));
	if(!next){
		return NULL;
	}
	if(strlen(string)==0){
		return next;
	}
	long long int k=-1,j=0;
	next[0]=-1;
	while(j<strlen(string)){
		if(k==-1||string[k]==string[j]){
			next[++j]=++k;
		}else{
			k=next[k];
		}
	}
	return next;
}

long long int* _String_kmp_get_nextval(char*string){
	if(!string){
		return NULL;
	}
	long long int*nextval=NULL;
	nextval=(long long int*)malloc(sizeof(long long int)*strlen(string));
	if(!nextval){
		return NULL;
	}
	if(strlen(string)==0){
		return nextval;
	}
	long long int k=-1,j=0;
	nextval[0]=-1;
	while(j<strlen(string)){
		if(k==-1||string[k]==string[j]){
			++k;
			++j;
			if(string[k]==string[j]){
				nextval[j]=nextval[k];
			}else{
				nextval[j]=k;
			}
		}else{
			k=nextval[k];
		}
	}
	return nextval;
}

long long int _String_kmp_kmp(char*father,char*son,long long int*next,long long int start){
	long long int i=start,j=0;
	//i为主串标志，j为子串标志
	long long father_length=strlen(father);
	long long son_length=strlen(son);
	while(i<father_length&&j<son_length){
		if(j==-1||father[i]==son[j]){
			i++;
			j++;
		}else{
			j=next[j];
		}
	}
	if(j>=son_length){
		return i-strlen(son);
	}else{
		return -1;//没有找到
	}
}
//kmp调用库内部函数end---------------------------------------------


long long _String_kmp(struct _String**string_1,struct _String**string_2,long long start){
	//kmp字符串匹配算法，在string_1内s搜索string_2
	if(!string_1||!string_2||!(*string_1)||!(*string_2)){
		return -1;
	}
	char *string=(*string_1)->data;
	char *find_string=(*string_2)->data;
	//进行创建next数组
	long long int*next=_String_kmp_get_nextval(find_string);
	long long return_num= _String_kmp_kmp(string,find_string,next,start);
	free(next);
	return return_num;
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




//链表
//first decleare
union _LinkList_node_data;
struct _LinkList_node;
struct _LinkList;
struct _LinkList* _LinkList_init(struct _LinkList**link);
void _LinkList_afterInster(struct _LinkList**link,struct _LinkList_node*node);
void _LinkList_beforeInster(struct _LinkList**link,struct _LinkList_node*node);
void _LinkList_delete(struct _LinkList**link,struct _LinkList_node*node);
void _LinkList_free(struct _LinkList**link);
void _LinkList_reverse(struct _LinkList**link);
int _LinkList_empty(struct _LinkList**link);
union _LinkList_node_data{
	int data_int;
	double data_double;
	float data_float;
	char data_char;
};
struct _LinkList_node{
	union _LinkList_node_data data;
	struct _LinkList_node *next;
};
struct _LinkList{
	struct _LinkList_node *headNode;
	void (*afterInster)(struct _LinkList**link,struct _LinkList_node*node);
	void (*beforeInster)(struct _LinkList**link,struct _LinkList_node*node);
	void (*delete)(struct _LinkList**link,struct _LinkList_node*node);
	void (*free)(struct _LinkList**link);
	void (*reverse)(struct _LinkList**link);
	int  (*empty)(struct _LinkList**link);
	struct _LinkList_node* (*centerNode)(struct _LinkList**link);
};

struct _LinkList* _LinkList_init(struct _LinkList**link){
	//链表初始化
	if(!link){
		return NULL;
	}
	*link=(struct _LinkList*)malloc(sizeof(struct _LinkList)*1);
	if(!*link){
		return NULL;
	}
	(*link)->headNode=(struct _LinkList_node*)malloc(sizeof(struct _LinkList_node)*1);
	if(!(*link)->headNode){
		return NULL;
	}
	(*link)->headNode->next=NULL;
	//函数指针指向函数
	(*link)->afterInster=_LinkList_afterInster;
	(*link)->beforeInster=_LinkList_beforeInster;
	(*link)->delete=_LinkList_delete;
	(*link)->free=_LinkList_free;
	(*link)->reverse=_LinkList_reverse;
	return *link;
}

void _LinkList_afterInster(struct _LinkList**link,struct _LinkList_node*node){
	//链表尾插法
	//尾插节点要找到最后一个结点
	if(!link||!*link||!node){
		return;
	}
	struct _LinkList_node*temp_node=(*link)->headNode;
	while(temp_node->next!=NULL){
		temp_node=temp_node->next;
	}
	//现在temp_node就是链表的尾节点
	//建立新的节点插入
	struct _LinkList_node*new_node=NULL;
	new_node=(struct _LinkList_node*)malloc(sizeof(struct _LinkList_node)*1);
	if(!new_node){
		return;
	}
	//data转移
	new_node->data=node->data;
	//插入
	temp_node->next=new_node;
	new_node->next=NULL;
	//插入完毕
	return ;
}

void _LinkList_beforeInster(struct _LinkList**link,struct _LinkList_node*node){
	if(!link||!*link||!node){//指针为假
		return;
	}
	//链表头插法
	//新建头结点
	struct _LinkList_node*newnode=NULL;
	newnode=(struct _LinkList_node*)malloc(sizeof(struct _LinkList_node)*1);
	if(!newnode){
		return;
	}
	//data转移
	newnode->data=node->data;
	newnode->next=(*link)->headNode->next;
	(*link)->headNode->next=newnode;
	//头插入节点完毕
	return;
}

void _LinkList_delete(struct _LinkList**link,struct _LinkList_node*node){
	//链表节点删除,需要给定所要删除节点的地址,node为所要删除的节点
	if(!link||!*link||!node){//指针不合法
		return;
	}
	//遍历表
	struct _LinkList_node* temp_node=(*link)->headNode;
	while(temp_node){
		if(temp_node->next==node){//如果temp_node是node的前一个节点,则将node节点删除并释放
			temp_node->next=node->next;
			free(node);
			break;
		}
		temp_node=temp_node->next;
	}
	return ;
}

void _LinkList_free(struct _LinkList**link){
	//链表空间释放
	if(!link||!*link){
		return;
	}
	struct _LinkList_node* temp_node=(*link)->headNode;
	while(temp_node){
		struct _LinkList_node*free_node=temp_node;
		temp_node=temp_node->next;
		free(free_node);
	}
	//free *link
	free(*link);
	return ;
}

void _LinkList_reverse(struct _LinkList**link){
	//就地逆置链表
	if(!link||!*link){
		return;
	}
	//printf("reverse\n");
	//我们从headNode后面进行断开然后讲节点进行前插
	struct _LinkList_node*temp_node=(*link)->headNode->next;
	(*link)->headNode->next=NULL;
	//然后开始前插
	while(temp_node){
		//printf(".%d\n",temp_node->data.data_int);
		struct _LinkList_node *inster_node=temp_node;
		temp_node=temp_node->next;
		inster_node->next=(*link)->headNode->next;
		(*link)->headNode->next=inster_node;
	}
	return ;
}

int _LinkList_empty(struct _LinkList**link){
	//判断链表是否为空
	if(!link||!*link||!(*link)->headNode||!(*link)->headNode->next){
		return 1;
	}else{
		return 0;
	}
}

//单向循环链表
//first decleare

//双向链表




//双向循环链表




//顺序栈



//链栈



//顺序队列



//链队列


//双端队列



//矩阵存储与压缩



#endif



