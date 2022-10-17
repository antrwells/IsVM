#pragma once
#include "ZenByteCode.h"
#include "Datas.h"

#define STACK_MAX  2048
#define MAX_MEM 1024*256

enum Result {

	RUN_OK,
	RUN_COMPILE_ERROR,
	RUN_RUNTIME_ERROR

};

enum Reg {

	R_R0, R_R1, R_R2, R_R3, R_R4, R_R5, R_R6, R_R7,
	R_PC, R_COND, R_COUNT

};

class IVM
{
public:

	IVM();
	void SetCode(ZenByteCode& code);
	Result RunCode(ZenByteCode& code);
	void InitVM();
	void FreeVM();
	void Push(Value v)
	{
		stack[stackLevel] = v;
		stackLevel++;
	}
	Value Pop() {
		auto r = stack[stackLevel - 1];
		stackLevel--;
		return r;
	}

	void WriteValue(Value mem,int os)
	{
		char* mem_os = mMem + os;
		char* mp = (char*)mem.value;
		for (int i = 0; i < mem.size; i++) {
			mem_os[i] = mp[i];
		}
	}

	Value ReadFloat(int from) {

		Value nv(mMem + from, 4);
		return nv;
	}
	Value ReadInt(int from) {

		Value nv(mMem + from, 4);
		return nv;
	}


private:
	
	ZenByteCode chunk;
	Value stack[STACK_MAX];
	int stackLevel = 0;
	Value* stackTop;
	uint8_t* ip;
	Value regs[R_COUNT];
	char* mMem;

};

