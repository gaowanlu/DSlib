#include<stdio.h>
#include<stdlib.h>
#include"DSlib.h"
int main(void){
	struct _String* string;
	_String_init(&string);
	string->set(&string,"hferbabaabeh");
	string->print(&string);
	struct _String* string2;
	_String_init(&string2);
	string2->set(&string2,"abaabe");
	string2->print(&string2);
	printf("%ld\n",string->kmp(&string,&string2));
	printf("%ld\n",string->bf(&string,&string2));
	string2->set(&string2,"er");
	printf("%ld\n",string->kmp(&string,&string2));
	printf("%ld\n",string->bf(&string,&string2));
	struct _SeqList*list;
	_SeqList_init(&list);
	list->size=10;
	list->getMemory(&list);
	for(int i=0;i<10;++i){
		_String_init(&(((list->data)+i)->data_string));
		((list->data)+i)->data_string->set(&(((list->data)+i)->data_string),"gaowanlu hello world");
	}
	for(int i=0;i<10;++i){	
		((list->data)+i)->data_string->print(&(((list->data)+i)->data_string));
	}
	return 0;
}

/*output content
hferbabaabeh
abaabe
5
5
-1
-1
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
gaowanlu hello world
*/
