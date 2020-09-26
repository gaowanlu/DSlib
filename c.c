#include<stdio.h>
#include<stdlib.h>
#include"DSlib.h"
int main(void){
	struct _String* string;
	_String_init(&string);
	string->set(&string,"hxbdhcjseuhdwi");
	string->print(&string);
	struct _String* string2;
	_String_init(&string2);
	string2->set(&string2,"jseu");
	string2->print(&string2);
	printf("%ld\n",_String_bf(&string,&string2));
	return 0;
}
