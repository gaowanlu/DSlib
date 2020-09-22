#include<stdio.h>
#include<stdlib.h>
#include"type.h"
int main(void){
	struct _SeqList *List;
	_SeqList_init(&List);
	List->size=10;
	List->getLength(&List);
	int i=0;
	for(i=0;i<10;i++){
		(List->data+i)->data_int=i+999;
	}
	for(i=0;i<10;i++){
		printf("%d\n",(List->data+i)->data_int);
	}
	List->clear(&List);
	return 0;
/*运行结果
999
1000
1001
1002
1003
1004
1005
1006
1007
1008
*/
}
