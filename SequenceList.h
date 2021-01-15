#ifndef __SEQUENCELIST_H__
#define __SEQUENCELIST_H__
#include<stdlib.h>
#include<stdio.h>
//首先使用通用数据结构
#ifndef __COMMONTYPE_H__
#include"./CommonType.h"
#endif

//建立顺序表抽象数据类型
struct SequenceList{
    struct CommonType*el;
    size_t cur;
    size_t max;
};

//初始化顺序表
struct SequenceList* SequenceList_init(struct SequenceList*list){
    if(!list){//传进来的为空指针,则返回不做处理
        return NULL;
    }
    if(list->el){//如果现在已经拥有空间,则将其进行释放
        //--------------------------------------------------------------------------
        //        以下代码块可以自行添加，为CommonType内的指针释放内存           start
        //--------------------------------------------------------------------------
        //                                 code
        //--------------------------------------------------------------------------
        //        以下代码块可以自行添加，为CommonType内的指针释放内存             end
        //--------------------------------------------------------------------------
        //printf("顺序表空间被释放\n");
        free(list->el);
        list->el=NULL;
    }
    //检测max的大小是否合法
    if(list->max<=0){
        list->cur=0;
        list->el=NULL;
        return list;//max不合法则结束
    }else{//max是合法的
        //申请内存空间
        list->el=(struct CommonType*)malloc(sizeof(struct CommonType)*list->max);
        list->cur=0;
        if(!list->el){//申请内存失败
            list->max=0;
        }
        //--------------------------------------------------------------------------
        //        以下代码块可以自行添加，为CommonType内的指针申请内存           start
        //--------------------------------------------------------------------------
        //                                 code
        //--------------------------------------------------------------------------
        //        以下代码块可以自行添加，为CommonType内的指针申请内存             end
        //--------------------------------------------------------------------------
        return list;
    }
    return list;
}


//顺序表取值操作
struct CommonType* SequenceList_value(struct SequenceList*list,size_t get){
    //检测指针
    if(!list){
        return NULL;
    }
    //检测get cur max el
    if(!list->el||list->cur==0||get<0||get>=list->cur){
        return NULL;
    }
    //合法行为则执行操作，返回相应CommonType类型指针
    return (list->el+get);
}


//顺序标push操作:将el放入顺序表表尾的位置
struct CommonType* SequenceList_push(struct SequenceList*list,struct CommonType*el){
	//检测指针
	if(!list||!list->el||list->cur>=list->max){
		return NULL;
	}



}








#endif
