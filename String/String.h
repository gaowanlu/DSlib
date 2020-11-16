#ifndef __String_H__
#define __String_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef __DATATYPE_H__
#include"../DataType/DataType.h"
#endif

struct ds_String;
struct ds_String* ds_InitString(char*string);
void   ds_String_Free(struct ds_String**string);
struct ds_String* ds_String_AddString(struct ds_String*string,char*addString);
struct ds_String* ds_String_Reverse(struct ds_String*string);


typedef struct ds_String{
	char*data;
	size_t length;
	void (*Free)(struct ds_String**string);
	struct ds_String* (*AddString)(struct ds_String*string,char*addString);
	struct ds_String* (*Reverse)(struct ds_String*string);
}ds_String;


struct ds_String* ds_InitString(char*string){
	//判断string指针是否为空
	bool string_null=0;
	if(string==NULL){//string指针为空
		string_null=1;
	}
	struct ds_String*NewString=NULL;
	NewString=(struct ds_String*)malloc(sizeof(struct ds_String));
	
	if(!NewString){
		return NULL;
	}
	NewString->length=0;
	NewString->length=strlen(string);
	//为NewString->data申请空间
	NewString->data=NULL;
	NewString->data=(char*)malloc(sizeof(char)*((NewString->length)+1));
	
	if(!NewString->data){
		free(NewString);
		return NULL;
	}
	//字符串拷贝
	if(1){
		size_t i=0;
		for(i=0;i<NewString->length;i++){
			NewString->data[i]=string[i];
		}
		NewString->data[NewString->length]='\0';
	}
	//拷贝成功
	
	//函数指针，指向
	NewString->Free=ds_String_Free;
	NewString->AddString=ds_String_AddString;
	NewString->Reverse=ds_String_Reverse;
	return NewString;
}


void   ds_String_Free(struct ds_String**string){
	if((!string)||!(*string)){
		return;
	}
	if((*string)->data){
		free((*string)->data);
		(*string)->length=0;
	}
	free(*string);
	*string=NULL;
}



struct ds_String* ds_String_AddString(struct ds_String*string,char*addString){//向字符串后面增添新的字符串
	if(!string||!addString){
		return string;
	}
	//需要重新计算所需空间大小
	size_t addString_length=strlen(addString);
	//重新申请内存空间
	string->data=(char*)realloc(string->data,sizeof(char)*(string->length+addString_length+1));
	if(string->data==NULL){
		printf("ds_String_AddString 执行失败\n");
		return NULL;
	}
	if(1){
		int i=string->length;
		for(i;i<string->length+addString_length+1;i++){
			string->data[i]=addString[i-string->length];
		}
		string->data[string->length+addString_length]='\0';
	}
	string->length=string->length+addString_length;//更新字符串的长度
	return string;
}



struct ds_String* ds_String_Reverse(struct ds_String*string){
	//字符串的转置
	if(!string||!string->data){
		return NULL;
	}
	if(1){
		size_t before=0,after=string->length-1;
		while(before<after){
			char temp=string->data[before];
			string->data[before]=string->data[after];
			string->data[after]=temp;
			before++;
			after--;
		}
	}
	return string;
}

#endif

