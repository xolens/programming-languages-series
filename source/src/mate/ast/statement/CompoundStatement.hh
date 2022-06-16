#pragma once
#include <list>
#include <iostream>
#include <string>
#include "Statement.hh"


namespace mate::ast::statement {

class CompoundStatement: public Statement {

private:
	std::list<mate::ast::statement::Statement*> _statements;


public:
	CompoundStatement();
	~CompoundStatement();

	std::list<mate::ast::statement::Statement*> getStatements();
	void addStatement(mate::ast::statement::Statement* s);

	void execute() override;

};


	


} /* end namespace mate::ast::statement */
