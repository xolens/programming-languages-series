#pragma once
#include <iostream>
#include <list>
#include <functional>
#include <stdexcept>
#include "../statement/CompoundStatement.hh"
#include "FunctionHeader.hh"

namespace mate::ast::classifier {


class Function {

private:
	mate::ast::classifier::FunctionHeader* _header;
	mate::ast::statement::CompoundStatement* _compoundStat;


public:
	Function();
	Function(mate::ast::classifier::FunctionHeader* _header);
	Function(mate::ast::classifier::FunctionHeader* _header, mate::ast::statement::CompoundStatement* stm);
	~Function();

	FunctionHeader* getHeader();
	void setHeader(FunctionHeader* h);

	mate::ast::statement::CompoundStatement* getStatements();
	void setStatements(mate::ast::statement::CompoundStatement* stm);
};

} /* end namespace mate::ast::classifier */
