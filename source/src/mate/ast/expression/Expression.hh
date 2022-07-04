#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Data.hh"
#include "./../../executor/Context.hh"


namespace mate::executor { class Context; }

namespace mate::ast::expression {

enum class Operator{
	EQ,		 		// "="
	ADD_EQ, 		// "+="
	SUB_EQ, 		// "-="
	MUL_EQ, 		// "*="
	DIV_EQ, 		// "/="
	MOD_EQ, 		// "%="

	LEFT_EQ, 		// "<<="
	RIGHT_EQ, 		// ">>="
	AND_EQ, 		// "&="
	XOR_EQ, 		// "^="
	OR_EQ, 			// "|="

	ADD, 			// "+"
	SUB, 			// "-"
	MUL, 			// "*"
	DIV, 			// "/"
	MOD, 			// "%"
	TILDE, 			// "~"

	INC, 			// "++"
	DEC, 			// "--"

	OR,				// |
	AND,			// &
	XOR,			// ^

	AND2,			// &&
	OR2,			// ||
	
	EQ2,		 	// "=="
	NOT_EQ,			// ! 
	LS,				// <
	GT,				// >
	LS_EQ,			// <=
	GT_EQ,			// >=

	LEFT,			// >>>
	RIGHT,			// <<<
};

class Expression{

private:

public:
	Expression();
	~Expression();

	virtual mate::ast::expression::Data* valuate(mate::executor::Context* context);
	virtual std::string reference(mate::executor::Context* context);
};


} /* end namespace mate::ast::expression */
