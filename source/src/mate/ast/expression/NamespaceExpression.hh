#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Expression.hh"


namespace mate::ast::expression {

class NamespaceExpression: public mate::ast::expression::Expression {

private:
	std::list<std::string> identifiers;

public:
	NamespaceExpression(std::string identifier);
	~NamespaceExpression();

	std::string get();
	std::string package();
	std::string name();
	void add(std::string identifier);

	mate::ast::expression::Data* valuate(mate::executor::Context* context) override;

};

} /* end namespace mate::ast::expression */
