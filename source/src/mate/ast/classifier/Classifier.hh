#pragma once

#include "Function.hh"
#include "Modifiable.hh"

namespace mate::ast::classifier {

class Classifier: public mate::ast::classifier::Modifiable {

private:
	std::string  _name;
    mate::ast::classifier::Function* _function;
	
public:
	Classifier();
	~Classifier();

	std::string getName();
	void setName(std::string  s);
	
	mate::ast::classifier::Function* getFunction();
	void setFunction(mate::ast::classifier::Function* f);
	void execute();

};

} /* end namespace mate::ast::classifier */
