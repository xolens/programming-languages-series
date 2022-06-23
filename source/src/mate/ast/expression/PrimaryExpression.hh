#pragma once
#include <iostream>
#include <list>
#include "Expression.hh"
#include "Data.hh"


namespace mate::ast::expression {

class PrimaryExpression: public mate::ast::expression::Expression {

private:
	mate::ast::expression::Data* primitive;

public:
	PrimaryExpression(mate::ast::expression::Data* primitive);
	~PrimaryExpression();

	mate::ast::expression::Data* valuate(mate::executor::Context* context) override;

};


	


} /* end namespace mate::ast::expression */
