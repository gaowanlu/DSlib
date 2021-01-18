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
//返回相应下标的元素空间地址
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


//顺序表push操作:将el放入顺序表表尾的位置
struct CommonType* SequenceList_push(struct SequenceList*list,struct CommonType*el){
	//检测指针
	if(!list||!list->el||list->cur>=list->max||!el){
		return NULL;
	}
	//内容拷贝
	list->el[list->cur]=*el;
	list->cur+=1;
	//返回push到位置的地址
	return (list->el+list->cur)-1;
}


//顺序表pop操作:将下标cur-1的位置元素删除，并内容返回
//参数:list 为顺序表地址、el为将要pop的元素进行拷贝到el内
struct CommonType* SequenceList_pop(struct SequenceList*list,struct CommonType*el){
	//检测指针
	if(!list||!list->el||list->cur==0||!el){
		return NULL;
	}
	//内容拷贝
	*el=list->el[list->cur-1];
	list->cur=list->cur-1;
	//返回
	return el;
}


//顺序表insert操作
//功能在下标为index位置进行插入操作
//插入的范围为[0,list.cur]
//插入操作:在顺序表中第i个位置之前插入一个元素，需要从最后一个元素开始
//后移一位直到把第i个元素也后移一位，然后把新的的元素放到第i个位置
struct CommonType* SequenceList_insert(struct SequenceList*list,struct CommonType*el,size_t index){
	//检测指针与传进来的新元素是否真的存在,判断顺序表是否已经满了
	if(!list||!list->el||list->max==0||list->cur==list->max||!el){
		return NULL;
	}
	//检测下标是否合法
	if(index<0||index>list->cur){
		return NULL;
	}
	//进行插入相关操作
	//需要从末尾开始后移
	size_t i=list->cur;
	for(i=list->cur;i>index;i--){
		list->el[i]=list->el[i-1];
	}
	//现在下标为index的位置可以放入新的元素
	//printf("*%d\n",el->int_data);
	list->el[index]=*el;
	//更新cur
	list->cur+=1;
	//返回
	return (list->el+index);
	//@2021/1/17 21:48 现在家人们接我到家，在家里这么快乐的学习，简直太快乐了。我也要珍惜这些时光去学习、去陪伴家人。
	//编码人员:高万禄 2021/1/17 已测试无bug
}

//顺序表delete操作
//功能:删除某个合法下标位置的元素
//删除下标范围:[0,cur-1]
//删除后从index+1开始应该都向前移动一个位置
//返回值为0或者1，代表删除成功与失败
int SequenceList_delete(struct SequenceList*list,size_t index){
	//检测指针
	if(!list||!list->el||list->cur==0||list->max==0){
		return 0;
	}
	//检测index是否合法,不合法则返回0结束删除操作
	if(!(index>=0&&index<list->cur)){
		return 0;
	}
	//进行删除操作
	size_t i=0;
	for(i=index;i<list->cur;++i){
		list->el[i]=list->el[i+1];
	}
	//更新list->cur
	list->cur=list->cur-1;
	//返回1代表删除操作成功
	return 1;
}

//顺序表find操作
//功能：在顺序表中查找第一个查找的元素的下标
//返回:查找成功返回下标，查找失败返回-1
size_t SequenceList_find(struct SequenceList*list,struct CommonType*find){
	//检测指针
	if(!list||!list->el||!find||list->cur==0||list->max==0){
		return -1;
	}
	//迭代查找
	size_t i=0;
	for(i=0;i<list->cur;i++){
		if(list->el[i]==*find){
			break;
		}
	}
	if(i==list->cur){
		return -1;
	}
	return i
}





#endif
