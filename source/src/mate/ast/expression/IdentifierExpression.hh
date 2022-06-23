#pragma once
#include <string>
#include "Expression.hh"
#include "./../../executor/Context.hh"


namespace mate::ast::expression {

class IdentifierExpression: public mate::ast::expression::Expression {

private:
	std::string identifier;

public:
	IdentifierExpression(std::string identifier);
	~IdentifierExpression();

	std::string getIdentifier();
	std::string reference(mate::executor::Context* context);
	mate::ast::expression::Data* valuate(mate::executor::Context* context) override;
	
};

} /* end namespace mate::ast::expression */
