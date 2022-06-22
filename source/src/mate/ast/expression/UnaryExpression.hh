#pragma once
#include "Expression.hh"


namespace mate::ast::expression {

class UnaryExpression: public mate::ast::expression::Expression {

private:
	mate::ast::expression::Operator op;
	mate::ast::expression::Expression* op1;
	bool postfix;

public:
	UnaryExpression(mate::ast::expression::Operator op, mate::ast::expression::Expression* op1);
	UnaryExpression(mate::ast::expression::Operator op, mate::ast::expression::Expression* op1, bool postfix);
	~UnaryExpression();

};

} /* end namespace mate::ast::expression */
