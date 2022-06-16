#pragma once
#include <list>
#include <iostream>
#include <string>
#include "Statement.hh"


namespace mate::ast::statement {

class PrintStatement: public Statement {

private:
	std::string _value;


public:
	PrintStatement(std::string _value);
	~PrintStatement();

	void execute() override;

};


	


} /* end namespace mate::ast::statement */
