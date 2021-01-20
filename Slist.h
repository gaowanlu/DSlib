//Slist:单向链表
#ifndef __SLIST_H__
#define __SLIST_H__
#include<stdlib.h>
//引入CommonType
#ifndef __COMMONTYPE_H__
#include"./CommonType.h"
#endif

//单向链表节点数据结构定义
struct SlistNode{
	struct CommonType el;//节点数据
	struct SlistNode*next;//节点指针域
};

//初始化Slist(单向链表)
//默认：单向链表具有头节点
struct SlistNode* Slist_init(void){
	//创建一个新的空节点
	struct SlistNode*newNode=(struct SlistNode*)malloc(sizeof(struct SlistNode));
	//如果申请内存失败
	if(!newNode){
		return NULL;
	}
	//指针域指向空
	newNode->next=NULL;
	//初始化单向链表成功
	return newNode;
}


//释放链表内存空间
//返回1 0，代表释放成功与失败
int Slist_free(struct SlistNode* headNode){
	//检测指针
	if(!headNode){
		return 0;
	}
	//从头节点开始释放
	struct SlistNode*tempNode=headNode;
	while(tempNode){
		struct SlistNode* freeNode=tempNode;
		tempNode=tempNode->next;
		free(freeNode);
	}
	//释放内存成功
	return 1;
}


//单向链表的创建，分为头插法与尾插法

//Slist头插法
//返回插入节点地址，插入失败返回NULL
struct SlistNode* Slist_before(struct SlistNode* headNode,struct SlistNode* newNode){
	//检测指针
	if(!headNode||!newNode){
		return NULL;
	}
	//进行头插法加入新的节点
	struct SlistNode*insertNode=NULL;
	insertNode=(struct SlistNode*)malloc(sizeof(struct SlistNode));
	if(!insertNode){
		return NULL;
	}
	//内容拷贝
	*insertNode=*newNode;
	//将新节点加入
	insertNode->next=headNode->next;
	headNode->next=insertNode;
	//返回新插入的节点的地址
	return insertNode;
}

//Slist尾插法
//返回插入节点地址，插入失败返回NULL
struct SlistNode* Slist_after(struct SlistNode* headNode,struct SlistNode* newNode){
	//检测指针
	if(!headNode||!newNode){
		return NULL;
	}
	//进行尾插法加入新的节点
	struct SlistNode*insertNode=NULL;
	insertNode=(struct SlistNode*)malloc(sizeof(struct SlistNode));
	if(!insertNode){//内存申请失败
		return NULL;
	}
	//内容拷贝
	*insertNode=*newNode;
	//寻找末尾节点
	struct SlistNode*lastNode=headNode;
	while(lastNode->next!=NULL){
		lastNode=lastNode->next;
	}
	//加入新节点
	lastNode->next=insertNode;
	insertNode->next=NULL;
	//返回新节点地址
	return insertNode;
}


//Slist取值
//功能：获得Slist第n个节点的地址
//返回：第n个节点的地址，头节点为第0个节点,没有则返回NULL
struct SlistNode* Slist_value(struct SlistNode* headNode,size_t index){
	//检测指针
	if(!headNode){
		return NULL;
	}
	//检测下标
	if(index<0){
		return NULL;
	}
	//开始迭代
	struct SlistNode*tempNode=headNode;
	size_t i=0;
	for(i=0;i<index;++i){
		if(!tempNode){
			break;
		}
		tempNode=tempNode->next;
	}
	//返回找到的节点地址
	return tempNode;
}



//Slist插入
//功能：在第n个节点的位置插入新节点，也就是原来的第n个节点变为原来的第n+1个
//返回：插入成功返回新节点地址，否则返回NULL
struct SlistNode* Slist_insert(struct SlistNode* headNode,struct SlistNode* newNode,size_t index){
	//检测指针
	if(!headNode||!newNode){
		return NULL;
	}
	//检测下标
	if(index<=0){//下标不合法
		return NULL;
	}
	//还应注意下标可能越界
	size_t i=1;
	struct SlistNode* tempNode=headNode;
	//开始迭代,找到第index-1个节点
	while(i!=index){
		if(tempNode==NULL){
			break;
		}
		tempNode=tempNode->next;
		i++;
	}
	//判断tempNode
	if(!tempNode){//不能插入
		return NULL;
	}
	//进行新节点的插入
	struct SlistNode*insertNode=NULL;
	insertNode=(struct SlistNode*)malloc(sizeof(struct SlistNode));
	if(!insertNode){
		return NULL;
	}
	//内容拷贝
	*insertNode=*newNode;
	//指针指向改变
	insertNode->next=tempNode->next;
	tempNode->next=insertNode;
	//返回新节点地址
	return insertNode;
}


//Slist删除
//功能：删除指定节点
//返回：删除成功返回1否则返回0
int Slist_delete(struct SlistNode* headNode,size_t index){
	//检测指针
	if(!headNode){
		return 0;
	}
	//检测下标
	if(index<=0){
		return 0;
	}
	size_t i=0;
	struct SlistNode*tempNode=headNode;
	while(i!=index-1){
		if(tempNode==NULL){
			break;
		}
		tempNode=tempNode->next;
		i++;
	}
	if(!tempNode||!tempNode->next){
		return 0;
	}
	struct SlistNode*freeNode=tempNode->next;
	tempNode->next=tempNode->next->next;
	//释放要删除的节点
	free(freeNode);
	return 1;//删除成功
}
#endif

