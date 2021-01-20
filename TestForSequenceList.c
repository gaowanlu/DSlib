#include<stdio.h>
#include"./SequenceList.h"
int main(int argc,char**argv){
    struct SequenceList list;
    list.max=10;
    SequenceList_init(&list);
	int i=0;
	while(list.cur!=list.max){
		struct CommonType el;
		el.int_data=i++;
		SequenceList_push(&list,&el);
	}
	for(i=0;i<list.cur;++i){
		printf("%d\n",list.el[i].int_data);
	}
	//进行pop测试
	while(list.cur!=0){
		struct CommonType el;
		SequenceList_pop(&list,&el);
		printf("%d\n",el.int_data);
	}
	//现在顺序表已经被pop空了
	//我们将在下标为0的位置进行insert操作
	struct CommonType el;
	el.int_data=999;
	for(i=0;i<15;i++){
		el.int_data=i;
		SequenceList_insert(&list,&el,0);
	}
	//输出验证
	for(i=0;i<list.cur;i++){
		printf("--%d\n",list.el[i].int_data);
	}
	//删除操作
	SequenceList_delete(&list,0);
	SequenceList_delete(&list,2);
	SequenceList_delete(&list,4);
	SequenceList_delete(&list,0);
	SequenceList_delete(&list,0);
	//清空顺序表
	list->cur=0;


	//输出验证
	for(i=0;i<list.cur;i++){
		printf("**%d\n",list.el[i].int_data);
	}
    //释放顺序表内存的方法
    list.max=0;
    SequenceList_init(&list);
    return 0;
}
