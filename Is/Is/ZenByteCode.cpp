#include "pch.h"
#include "ZenByteCode.h"

ZenByteCode::ZenByteCode() {


}

void ZenByteCode::AddOp(OpCode op) {
	code.push_back(op);
}

size_t ZenByteCode::Length()
{

	return code.size();

}

OpCode ZenByteCode::GetOp(int index) {

	return code[index];

}
