#pragma once
#include <string>
#include <vector>
#include "Datas.h"
#define MAX_MEM (1024*256) //256mb



enum OpCodeID {

	OP_PUSH, OP_PULL, OP_POP, OP_SET, OP_PRINT, OP_MOVEI, OP_MOVEF, OP_MOVEB, OP_MOVED, OP_MOVEL,
	OP_PUSHF, OP_PUSHI, OP_PUSHD, OP_PUSHL, OP_MOVER,OP_ADD
};

enum CondFlags {
	FL_POS = 1 << 0, /* P */
	FL_ZRO = 1 << 1, /* Z */
	FL_NEG = 1 << 2, /* N */
};

enum DataType {
	Int,Float,Long,Double,String,Class,Byte
};



class OpCode {
public:
	OpCodeID ID;
	OpCode(OpCodeID id)
	{
		ID = id;
	}
	Value data[32];
	int stackId = -1;
	int from, to;
	int left = 0;
	int right = 0;
	int regIndex = 0;
	
};

class ZenByteCode
{
public:

	ZenByteCode();
//	void DefineClass(std::string name);
//	void AddString(std::string);
	//void AddBytes(char* bytes, int num);
	void AddOp(OpCode op);

	size_t Length();
	OpCode GetOp(int index);
private:

	std::vector<OpCode> code;


};

