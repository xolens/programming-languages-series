#pragma once
#include "Statement.hh"
#include "../expression/Expression.hh"

namespace mate::executor { class Context; }

namespace mate::ast::statement {

class ExpressionStatement: public mate::ast::statement::Statement {

private:
	mate::ast::expression::Expression* exp;

public:
	ExpressionStatement(mate::ast::expression::Expression* exp);
	~ExpressionStatement();

};

} /* end namespace mate::ast::statement */
