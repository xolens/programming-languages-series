#pragma once
#include "Expression.hh"


namespace mate::ast::expression {

class BinaryExpression: public mate::ast::expression::Expression {

private:
	mate::ast::expression::Expression* op1;
	mate::ast::expression::Expression* op2;
	mate::ast::expression::Operator op;

public:
	BinaryExpression(mate::ast::expression::Expression* op1, mate::ast::expression::Operator op, mate::ast::expression::Expression* op2);
	~BinaryExpression();

};


} /* end namespace mate::ast::expression */
