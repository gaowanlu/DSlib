#include<stdio.h>
#include<stdlib.h>
#include"DSlib.h"
int main(void){
	struct _String* string;
	_String_init(&string);
	string->set(&string,"gaowanlu is good person");
	string->print(&string);
	string->reverse(&string);
	string->print(&string);

	struct _String* string2;
	_String_init(&string2);
	string->copy(&string,&string2);
	string2->print(&string2);


	return 0;
}
