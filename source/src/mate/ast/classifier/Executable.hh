#pragma once
#include "./../../executor/Context.hh"

namespace mate::ast::classifier {

class Executable{

public:
	Executable();
	~Executable();
	
	virtual void execute(mate::executor::Context* context);

};

} /* end namespace mate::ast::classifier */
