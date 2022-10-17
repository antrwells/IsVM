#pragma once
#include "ZTokenStream.h"
#include "ZenByteCode.h"
class ZTokens;


class ZenParser
{
public:

	ZenParser(ZTokens* toks);
	ZenByteCode* Parse();
	void ParseExpression(ZenByteCode* code);
	bool NextLine();
	bool EOS() {
		return mCurrent->EOS();
	}
	Token Next() {
		return mCurrent->NextToken();
	}
	Token Peek(int id=0) {
		return mCurrent->PeekToken(id);
	}

	void Error(std::string msg);

private:

	ZTokens* mTokens = nullptr;
	ZTokenStream* mCurrent = nullptr;
	int mLine = 0;
};

