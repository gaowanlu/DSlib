#include"./DirectInsertionSort.h"
#define SORTDATATYPE int
#define SORTDSDATA ds_int
void ds_DirectInsertionSort(struct ds_SeqList*list,size_t before,size_t after){
    //从[before,after]排序
    if(before<0||after>=list->cur||after<before){//不合法
        return;
    } 
    size_t i, j;
    for (i = before+1; i <= after;i++){
        if(list->data[i].SORTDSDATA<list->data[i-1].SORTDSDATA){
            union ds_DataType temp = list->data[i];
            list->data[i] = list->data[i - 1];
            for (j = i - 2;  j >= before&&list->data[j].SORTDSDATA > temp.SORTDSDATA;j--)
                list->data[j + 1] = list->data[j];
            list->data[j+1] = temp;
        }
    }
}

int main(void){
    int i = 0;
    ds_Sort sort;
    sort.list = ds_InitSeqList(10);
    union ds_DataType data;
    for (i = 10; i > 0;i--){
        data.ds_int = i;
        sort.list->Push(sort.list, &data);
    }
    ds_DirectInsertionSort(sort.list, 0, sort.list->cur-1);
    printf("{ ");
    for (i = 0; i < sort.list->cur;i++){
        printf(" %d ", sort.list->data[i].ds_int);
        if(i!=sort.list->cur-1){
            printf(",");
        }
    }
    printf(" }\n");




    sort.list->Free(&(sort.list));
    return 0;
}