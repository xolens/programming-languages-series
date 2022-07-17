#pragma once
#include <iostream>
#include <list>

#include "Statement.hh"
#include "../expression/Expression.hh"
#include "../expression/DataTypeExpression.hh"

namespace mate::ast::statement {

class DeclarationInitializer {

private:
	std::string _identifier;
	mate::ast::expression::Expression* _initializer;

public:
	DeclarationInitializer(std::string identifier, mate::ast::expression::Expression* initializer);
	~DeclarationInitializer();

	std::string identifier();
	mate::ast::expression::Expression* initializer();

	static DeclarationInitializer* of(std::string _identifier){
		return new DeclarationInitializer(_identifier, NULL);
	}

	static DeclarationInitializer* of(std::string _identifier, mate::ast::expression::Expression* _initializer){
		return new DeclarationInitializer(_identifier, _initializer);
	}

};

// ---------------------------------

class DeclarationStatement: public mate::ast::statement::Statement {

private:
	bool _final;
	mate::ast::expression::DataTypeExpression* _type;
	std::list<mate::ast::statement::DeclarationInitializer*>* _initializers;

public:
	DeclarationStatement(mate::ast::expression::DataTypeExpression* _type, std::list<mate::ast::statement::DeclarationInitializer*>* _initializers);
	~DeclarationStatement();

	bool final();
	void setFinal(bool _final);
	mate::ast::expression::DataTypeExpression* type();
	std::list<mate::ast::statement::DeclarationInitializer*>* initializers();
	std::list<std::string> identifiers();

	bool hasIdentifier(std::string identifier);

	void execute(mate::executor::Context* context) override;

	static DeclarationStatement* of(mate::ast::expression::DataTypeExpression* _type, std::list<mate::ast::statement::DeclarationInitializer*>* _initializers){
		return new DeclarationStatement(_type,_initializers);
	}

};

} /* end namespace mate::ast::statement */
