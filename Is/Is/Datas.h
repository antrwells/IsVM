#pragma once
#include <malloc.h>

struct Value {

	void* value;
	size_t size;
	
    Value() {
		value = 0;
		size = 0;
	}

	Value(char* p, int vsize) {
		value = (void*)p;
		size = vsize;
	}

	void Make(size_t vsize) {
		value = malloc(vsize);
		size = vsize;
	}

	void Copy(char* from)
	{
		char* v = (char*)value;
		for (int i = 0; i < size; i++) {
			v[i] = from[i];
		}
	}
	Value(int v) {
		Make(sizeof(int));
		Copy((char*) & v);
	}


	Value(float v)
	{
		Make(sizeof(float));
		Copy((char*)&v);
	}
	Value(char v)
	{
		Make(sizeof(char));
		Copy((char*)v);
	}
	Value(double v) {
		Make(sizeof(double));
		Copy((char*)&v);
	}
	Value(long v) {
		Make(sizeof(long));
		Copy((char*)&v);
	}

};