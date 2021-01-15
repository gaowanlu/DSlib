#include<stdio.h>
#include"./SequenceList.h"
int main(int argc,char**argv){
    struct SequenceList list;
    list.max=10;
    SequenceList_init(&list);
    int i=0;
    printf("hello world\n");
    for(i=0;i<list.max;++i){
        list.el[i].int_data=i;
        list.el[i].id=888;
        list.el[i].name='g';
    }

    //打印测试
    for(i=0;i<list.max;++i){
        printf("%d\n",i);
        printf("\t%d\n",list.el[i].int_data);
        printf("\t%d\n",list.el[i].id);
        printf("\t%c\n",list.el[i].name);
    }
    struct CommonType* data=SequenceList_value(&list,2);
    if(data)
        printf("--%d\n",data->id);    
    //释放顺序表内存的方法
    list.max=0;
    SequenceList_init(&list);
    return 0;
}
