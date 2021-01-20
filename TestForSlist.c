#include<stdio.h>
#include<stdlib.h>
#include"./Slist.h"
int main(int argc,char**argv){
	//构建空单向链表
	struct SlistNode*link=Slist_init();
	struct SlistNode data;
	int i;
	//头插法
	for(i=0;i<10;i++){
		data.el.int_data=i;
		Slist_before(link,&data);
	}
	//尾插法
	for(i=0;i<10;i++){
		data.el.int_data=i+99;
		Slist_after(link,&data);
	}
	//输出链表
	struct SlistNode*tempNode=link->next;
	while(tempNode){
		printf("%d\n",tempNode->el.int_data);
		tempNode=tempNode->next;
	}
	//节点取值
	struct SlistNode*getNode=Slist_value(link,20);
	if(getNode){
		printf("--%d\n",getNode->el.int_data);
	}
	//节点插入
	struct SlistNode insertNode;
	insertNode.el.int_data=999;
	Slist_insert(link,&insertNode,15);
	//节点删除
	Slist_delete(link,15);
	//输出链表
	tempNode=link->next;
	while(tempNode){
		printf("%d\n",tempNode->el.int_data);
		tempNode=tempNode->next;
	}
	//释放链表
	Slist_free(link);
	return 0;
}
