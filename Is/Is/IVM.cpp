#include "pch.h"
#include "IVM.h"
#include <malloc.h>
#include "ZenByteCode.h"
IVM::IVM() {

	mMem = (char*)malloc(MAX_MEM);


}
void IVM::SetCode(ZenByteCode& code)
{

	chunk = code;

}


Result IVM::RunCode(ZenByteCode& code) {

	int size = code.Length();

	int i = 0;
	while (i < size) {

		OpCode op = code.GetOp(i);
		switch (op.ID) {
		case OP_MOVEI:
		{
			int move_to = op.to;
			WriteValue(op.data[0], move_to);
		}
			break;
		case OP_MOVEF:
		{
			int move_to = op.to;
			WriteValue(op.data[0], move_to);
		}
			break;
		case OP_PUSHI:
		{

			int from = op.from;
			Push(ReadInt(from));
		}
			break;
		case OP_PUSHF:
		{
			int from = op.from;
			
			Push(ReadFloat(from));

		}
			break;
		case OP_SET:
		
		
			break;
		case OP_PRINT:
		{
			int vv = 5;

			auto va = Pop();
			float* fp = (float*)va.value;
			printf("%f", *fp);

			printf("Print::%f\n", *(float*)va.value);	 
			int aa = 5;
		}
			break;
		case OP_MOVER:

			break;
		}
		i++;
	}
	

	return RUN_OK;

}