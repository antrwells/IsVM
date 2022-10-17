#include "pch.h"
#include "ZenParser.h"
#include "ZTokenStream.h"
#include "ZenByteCode.h"
#include <map>

ZenParser::ZenParser(ZTokens* toks) {

	mTokens = toks;
	mCurrent = nullptr;
}

bool ZenParser::NextLine() {

	if (mCurrent == nullptr) {
		mCurrent = mTokens->Lines[0];
		mLine++;
		return true;
	}
	if (mTokens->Lines.size() == mLine)
	{
		return false;
	}
	mCurrent = mTokens->Lines[mLine];
	mLine++;
	return true;
}

ZenByteCode* ZenParser::Parse() {

	ZenByteCode* code = new ZenByteCode;

	int line = 0;

	std::vector<std::string> funcs;



	std::map<std::string, int> var_map;
	std::map<std::string, DataType> type_map;
	int stack_index = 0;

	int mem_start = 0;

	NextLine();

	while (true)
	{
		int toke_index = 0;
		while (!EOS())
		{
			auto token = Next();

			switch (token.mType)
			{
			case TokenType::TokenIdent:
			{
				std::string name = token.mText;
				if (name == "print")
				{
					OpCodeID id = OP_PUSHI;
					auto var = Next();

					switch (type_map[var.mText])
					{
					case DataType::Int:
						id = OpCodeID::OP_PUSHI;
						break;
					case DataType::Float:
						id = OpCodeID::OP_PUSHF;
						break;
					}

					OpCode push_par = OpCode(id);

					int index = var_map[var.mText];
					//push_par.data[0] = Value(std::stof(Next().mText));
					push_par.from = index;

					code->AddOp(push_par);
					OpCode p_op(OpCodeID::OP_PRINT);
					code->AddOp(p_op);
					//OpCode pop = OpCode(OpCodeID::OP_POP);
					//code->AddOp(pop);


				}
				else {

					if (Peek(0).mType == TokenType::TokenEquals)
					{
						if (var_map.count(name) == 0) {

							Error("Undeclared variable:" + name);

						}
						auto index = var_map[name];

						Next();
						if (Peek(0).mType != TokenType::ConstantNum)
						{
							Error("Expecting numeral.");
						}
						OpCode op(OpCodeID::OP_SET);
						op.data[0] = Value(std::stof(Next().mText));
						op.stackId = index;
						code->AddOp(op);


					}
				}
			}
			break;
			case TokenType::TokenInt:
			{

				std::string name = Next().mText;

				int mem = mem_start;
				mem_start += 4;
				var_map[name] = mem;
				type_map[name] = DataType::Int;

				if (Peek(0).mType == TokenType::TokenEquals)
				{
					Next();

					ParseExpression(code);



					OpCode op(OpCodeID::OP_MOVER);
					op.to = mem;
					op.regIndex = 7;
					//op.data[0] = Value(std::stof(Next().mText));
					//op.to = mem;

					code->AddOp(op);
				}



				break;
			}

			}
			
		}
		if (!NextLine()) {
			break;
		}
		printf("\n");
	}
	


	return code;


}

void ZenParser::ParseExpression(ZenByteCode* code) {

	std::vector<Token> expr_run;

	bool prev_op = false;
	bool prev_num = false;
	while (!EOS()) {

		auto token = Next();
		switch (token.mType)
		{
		case TokenType::ConstantNum:
			if (prev_num) {
				Error("You cannot have two values in a row in an expression.");
			}
			prev_num = true;
			prev_op = false;
			expr_run.push_back(token);
			break;
		case TokenType::TokenPlus:
		case TokenType::TokenMinus:
		case TokenType::TokenMultiply:
		case TokenType::TokenDivide:
			if (prev_op == true) {
				Error("Expecting value.");
			}
			if (!prev_num) {
				Error("Cannot start an expression with a standard operator.");
			}
			prev_op = true;
			prev_num = false;
			expr_run.push_back(token);
			break;
		}

	}

	for (int i = 0; i < expr_run.size(); i++) {

		auto tok = expr_run[i];

		if (tok.mType == TokenType::TokenPlus)
		{

			auto left = expr_run[i - 1];

			auto right = expr_run[i + 1];

			OpCode move_l(OpCodeID::OP_MOVER);
			move_l.regIndex = 0;
			
			OpCode move_r(OpCodeID::OP_MOVER);
			move_r.regIndex = 1;
			OpCode add(OpCodeID::OP_ADD);
			add.left = 0;
			add.right = 1;
			add.regIndex = 7;
			code->AddOp(move_l);
			code->AddOp(move_r);
			code->AddOp(add);


		}

	}

	int aa = 5;

}

void ZenParser::Error(std::string msg) {

	printf("Parser fail.\n");
	printf("err:");
	printf(msg.c_str());
	printf("\n");

	for (int i = 0; i < mCurrent->Length(); i++) {

		auto tok = mCurrent->GetToken(i);
		if (i+1 == mCurrent->TokenIndex()) {
			printf(" [ ");
		}
		printf(tok.mText.c_str());
		printf(" ");
		if (i+1 == mCurrent->TokenIndex()) {
			printf("] ");
		}

		//printf("\n");

	}
	printf("\n");
	exit(0);

}

