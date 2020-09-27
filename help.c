#include<stdio.h>
#include<stdlib.h>
struct LinkListNode{
	int data;
	struct LinkListNode*next;
};
struct LinkList{
	struct LinkListNode*headNode;
	struct LinkListNode*end;
};
void input_for_list(struct LinkList*list){//采用尾插法
	list->headNode=(struct LinkListNode*)malloc(sizeof(struct LinkListNode)*1);
	if(!list->headNode){
		return ;
	}
	list->headNode->next=NULL;
	list->end=list->headNode;
	char input_char,input_enter;
	while(1){
		printf("是否输入数据 y or n\n");
		scanf("%c",&input_char);
		scanf("%c",&input_enter);
		if(input_char=='y'){//建立新节点
			struct LinkListNode*newnode;
			newnode=(struct LinkListNode*)malloc(sizeof(struct LinkListNode)*1);
			if(!newnode){
				return ;
			}
			printf("请输入一个整数\n");
			scanf("%d",&(newnode->data));
			scanf("%c",&input_enter);
			list->end->next=newnode;
			newnode->next=NULL;
			list->end=newnode;
		}else if(input_char=='n'){//结束输入
			break;
		}
	}	
}
void output_for_list(struct LinkList*list){
	struct LinkListNode*temp_node;
	temp_node=list->headNode->next;
	while(temp_node){
		printf("  %d  ",temp_node->data);
		temp_node=temp_node->next;
	}
	printf("\n");
	return ;
}


//合并两个从大到小内容的链表，保留list_1
void merge_list(struct LinkList*list_1,struct LinkList*list_2){
	struct LinkListNode*temp_1;
	struct LinkListNode*temp_2;
	temp_1=list_1->headNode->next;//指向表一的第一个节点
	temp_2=list_2->headNode->next;//指向表二的第一个节点
	//如果表一为空则将表二的第一个节点作为表一的第一个节点,然后表二为空
	if(!temp_1){
		list_1->headNode->next=temp_2=list_2->headNode->next;
		list_2->headNode->next=NULL;
		list_2->end=NULL;
	}
	//利用list_1->end只想新表的尾节点
	list_1->end=list_1->headNode;
	while(temp_1&&temp_2){
		if(temp_1->data>=temp_2->data){//连接表一的节点
			list_1->end->next=temp_1;
			list_1->end=temp_1;
			temp_1=temp_1->next;
		}else{//连接表二的节点
			list_1->end->next=temp_2;
			list_1->end=temp_2;
			temp_2=temp_2->next;
		}
	}
	list_1->end->next=temp_2?temp_2:temp_1;
	//释放表二头结点
	if(list_2->headNode){
	    free(list_2->headNode);
	    list_2->headNode=NULL;
	    list_2->end=NULL;
	}
	return ;
}

//将链表就地转置
void reverse_list(struct LinkList*list){
	if(!list||!list->headNode->next){
		return ;
	}
	struct LinkListNode*tempNode;
	tempNode=list->headNode->next->next;
	list->headNode->next->next=NULL;
	while(tempNode){
		struct LinkListNode*node=tempNode;
		tempNode=tempNode->next;
		node->next=list->headNode->next;
		list->headNode->next=node;
	}
	return ;
}
int main(void){
	struct LinkList list_1;
	struct LinkList list_2;
	printf("输入list_1\n");
	input_for_list(&list_1);
	printf("list_1:");
	output_for_list(&list_1);
	printf("输入list_2\n");
	input_for_list(&list_2);
	printf("list_2:");
	output_for_list(&list_2);
	merge_list(&list_1,&list_2);
	reverse_list(&list_1);
	printf("链表合并后为:");
	output_for_list(&list_1);
	return 0;
}
