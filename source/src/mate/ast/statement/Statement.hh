#pragma once
#include "./../../executor/Context.hh"

namespace mate::ast::statement {

class Statement{

public:
	Statement();
	~Statement();
	
	virtual void execute(mate::executor::Context* context);

};

} /* end namespace mate::ast::classifier */
