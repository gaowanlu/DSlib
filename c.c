#include<stdio.h>
#include<stdlib.h>
#include"DSlib.h"
int main(void){
	struct _String* string;
	_String_init(&string);
	string->set(&string,"hferbabaabeh");
	string->print(&string);
	struct _String* string2;
	_String_init(&string2);
	string2->set(&string2,"abaabe");
	string2->print(&string2);
	printf("%ld\n",string->kmp(&string,&string2));
	printf("%ld\n",string->bf(&string,&string2));
	string2->set(&string2,"er");
	printf("%ld\n",string->kmp(&string,&string2));
	printf("%ld\n",string->bf(&string,&string2));
	//进行链表测试
	struct _LinkList*list;
	_LinkList_init(&list);
	struct _LinkList_node TEMP;
	(TEMP.data).data_int=0;
	for(int i=0;i<10;i++){
		(TEMP.data).data_int=i;
		//list->afterInster(&list,&TEMP);
		list->beforeInster(&list,&TEMP);
	}
	//输出链表
	struct _LinkList_node *loop=list->headNode->next;
	while(loop){
		printf("%d\n",(loop->data).data_int);
		loop=loop->next;
	}
	//link to reverse
	printf("reverse\n");
	list->reverse(&list);
	loop=list->headNode->next;
	while(loop){
		//printf("::::\n");
		printf("%d\n",(loop->data).data_int);
		loop=loop->next;
	}
	return 0;
}

/*output content
hferbabaabeh
abaabe
5
5
-1
-1
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
*/
