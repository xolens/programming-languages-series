#pragma once
#include <list>
#include <string>
#include "Statement.hh"
#include "./../../executor/Context.hh"


namespace mate::ast::statement {

class CompoundStatement: public Statement {

private:
	std::list<mate::ast::statement::Statement*> _statements;


public:
	CompoundStatement();
	~CompoundStatement();

	std::list<mate::ast::statement::Statement*> getStatements();
	void addStatement(mate::ast::statement::Statement* s);
	void addStatement(std::list<mate::ast::statement::Statement*>* statements);

	void execute(mate::executor::Context* context) override;

};


	


} /* end namespace mate::ast::statement */
