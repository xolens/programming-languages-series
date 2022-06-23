#pragma once
#include <iostream>
#include "Statement.hh"
#include "../expression/Expression.hh"
#include "../expression/Data.hh"


namespace mate::ast::statement {

class PrintStatement: public Statement {

private:
	mate::ast::expression::Expression* _value;


public:
	PrintStatement(mate::ast::expression::Expression* _value);
	~PrintStatement();

	void execute(mate::executor::Context* context) override;

};

} /* end namespace mate::ast::statement */
