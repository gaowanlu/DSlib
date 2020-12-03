#include<stdio.h>
#include<stdlib.h>


typedef int DataType;


void Merge(DataType*list,size_t low,size_t high){
	//辅助空间
	DataType*temp=(DataType*)malloc(sizeof(DataType)*(high-low+1));
	int mid=(high+low)/2;
	int i=low,j=mid+1,k=0;
	while(i<=mid&&j<=high){
		if(list[i]<=list[j]){
			temp[k++]=list[i];
			i++;
		}else{
			temp[k++]=list[j];
			j++;
		}
	}
	while(i<=mid){
		temp[k++]=list[i];
		i++;
	}
	while(j<=high){
		temp[k++]=list[j];
		j++;
	}
	//转移
	for(int i=low,k=0;i<=high;i++,k++){
		list[i]=temp[k];
	}
	free(temp);
}

void MergeSort(DataType*list,size_t low,size_t high){
	if(low<high){
		MergeSort(list,low,(low+high)/2);
		MergeSort(list,((low+high)/2)+1,high);
		Merge(list,low,high);
	}
}




int main(void){
	DataType list[10]={4,3,2,1,7,6,5,8,9,0};
	MergeSort(list,0,9);
	for(int i=0;i<10;i++){
		printf("%d\n",list[i]);
	}
	return 0;
}
