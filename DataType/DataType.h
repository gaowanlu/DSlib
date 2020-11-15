#ifndef __DATATYPE_H__
#define __DATATYPE_H__


#ifndef bool
#define bool int
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif


typedef union ds_DataType{
	int ds_int;
	double ds_double;
	float ds_float;
	char ds_char;
}ds_DataType;
#endif

