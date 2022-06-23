#pragma once
#include "Expression.hh"
#include "BinaryExpression.hh"
#include "UnaryExpression.hh"
#include "IdentifierExpression.hh"

namespace mate::ast::expression {

class AssignmentExpression: public Expression {

private:
	Expression* op1;
	Expression* op2;
	Operator op;

public:
	AssignmentExpression(Expression* op1, Operator op, Expression* op2);
	~AssignmentExpression();

	mate::ast::expression::Data* valuate(mate::executor::Context* context) override;

};

} /* end namespace mate::ast::expression */
