#pragma once
#include <iostream>
#include <list>
#include "Expression.hh"
#include "DataTypeExpression.hh"
#include "NamespaceExpression.hh"


namespace mate::ast::expression {

class InstanciationExpression: public mate::ast::expression::Expression {

private:
	mate::ast::expression::DataTypeExpression* dataType;
	std::list<mate::ast::expression::Expression*>* params;
	bool inferedType;
	bool hasArrayValues;

public:
	InstanciationExpression(mate::ast::expression::DataTypeExpression* dataType, std::list<mate::ast::expression::Expression*>* params, bool hasArrayValues);
	~InstanciationExpression();

	mate::ast::expression::Data* valuate(mate::executor::Context* context) override;
	
};

} /* end namespace mate::ast::expression */
