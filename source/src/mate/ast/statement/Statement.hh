#pragma once

namespace mate::ast::statement {

class Statement{

public:
	Statement();
	~Statement();
	
	virtual void  execute();

};

} /* end namespace mate::ast::classifier */
