#pragma once
#include <iostream>
#include <list>
#include <functional>
#include <stdexcept>
#include "Executable.hh"
#include "FunctionHeader.hh"
#include "../statement/CompoundStatement.hh"

namespace mate::ast::classifier {


class Function: public Executable, public Modifiable {

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

	void execute(mate::executor::Context* context) override;
};

} /* end namespace mate::ast::classifier */
