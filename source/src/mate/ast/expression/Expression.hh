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

	virtual mate::ast::expression::Data* valuate(mate::executor::Context* context);
	virtual std::string reference(mate::executor::Context* context);
};


} /* end namespace mate::ast::expression */
