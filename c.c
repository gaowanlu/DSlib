#include<stdio.h>
#include<stdlib.h>
#include"DSlib.h"
int main(void){
	struct _SeqList *List;
	_SeqList_init(&List);
	List->size=10;
	List->getMemory(&List);
	//先进行内容赋值
	for(size_t i=0;i<List->size;++i){
		(List->data+i)->data_int=i;
	}
	//输出测试
	for(size_t i=0;i<List->size;++i){
		printf("%d\n",(List->data+i)->data_int);
	}
	//进行插入函数测试
	union _SeqList_node new_node;
	new_node.data_int=888;
	List->inster(&List,List->size-1,new_node,0);
	List->delete(&List,0,1);
	List->delete(&List,List->size-2,0);
	//输出进行验证
	for(size_t i=0;i<List->size;++i){
		printf("%d\n",(List->data+i)->data_int);
	}
	List->clear(&List);



	struct _String *string;
	_String_init(&string);
	string->set(&string,"gaowanlu");
	printf("%s\n",string->data);
	printf("%ld\n",string->size);
	string->set(&string,"chenxiaoming");
	printf("%s\n",string->data);
	printf("%ld\n",string->size);

	string->clear(&string);
	printf("%s\n",string->data);
	return 0;
/*运行结果
0
1
2
3
4
5
6
7
8
9
0
1
2
3
4
5
6
7
8
888
*/
}
