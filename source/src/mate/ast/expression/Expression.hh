#pragma once
#include <iostream>
#include <list>


namespace mate::executor { class Context; }

namespace mate::ast::expression {

enum class Operator{
	EQ,		 		// "="
	ADD_EQ, 		// "+="
	SUB_EQ, 		// "-="
	MUL_EQ, 		// "*="
	DIV_EQ, 		// "/="
	MOD_EQ, 		// "%="

	ADD, 			// "+"
	SUB, 			// "-"
	MUL, 			// "*"
	DIV, 			// "/"
	MOD, 			// "%"

	INC, 			// "++"
	DEC, 			// "--"
};

class Expression{

private:

public:
	Expression();
	~Expression();

};


} /* end namespace mate::ast::expression */
