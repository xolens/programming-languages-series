#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
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

	std::string reference(mate::executor::Context* context) override;
	mate::ast::expression::Data* valuate(mate::executor::Context* context) override;

};

} /* end namespace mate::ast::expression */
