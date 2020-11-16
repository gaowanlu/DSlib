#include"./String.h"
int main(void){
	ds_String*myname=ds_InitString("gaowanlu");


	myname->AddString(myname," hello world");
	printf("%s\n",myname->data);	
	myname->Reverse(myname);
	printf("%s\n",myname->data);	
	


	ds_String_Free(&myname);
	return 0;
}

