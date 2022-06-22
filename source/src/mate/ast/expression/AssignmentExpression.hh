#pragma once
#include "Expression.hh"

namespace mate::ast::expression {

class AssignmentExpression: public Expression {

private:
	Expression* op1;
	Expression* op2;
	Operator op;

public:
	AssignmentExpression(Expression* op1, Operator op, Expression* op2);
	~AssignmentExpression();

};

} /* end namespace mate::ast::expression */
