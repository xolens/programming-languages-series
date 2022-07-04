#pragma once
#include <iostream>
#include <list>
#include "Expression.hh"


namespace mate::ast::expression {

class ConditionnalExpression: public mate::ast::expression::Expression {

private:
	mate::ast::expression::Expression* condition;
	mate::ast::expression::Expression* ifExpr;
	mate::ast::expression::Expression* elseExpr;

public:
	ConditionnalExpression(mate::ast::expression::Expression* condition, mate::ast::expression::Expression* ifExpr, mate::ast::expression::Expression* elseExpr);
	~ConditionnalExpression();

};


	


} /* end namespace mate::ast::expression */
