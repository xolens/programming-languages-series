#pragma once

#include "Function.hh"
#include "Property.hh"
#include "Modifiable.hh"
#include "Executable.hh"

namespace mate::ast::classifier {

class Classifier: public Executable, public mate::ast::classifier::Modifiable {

private:
	std::string  _name;
	std::list<mate::ast::classifier::Property*> _properties;
    std::list<mate::ast::classifier::Function*> _functions;

public:
	Classifier();
	~Classifier();

	std::string getName();
	void setName(std::string  s);
	
	void addItems(std::list<mate::ast::classifier::Modifiable*>* classItems);

	std::list<mate::ast::classifier::Function*> getFunctions();
	void addFunction(mate::ast::classifier::Function* f);

	std::list<mate::ast::classifier::Property*> getProperties();
	void addProperty(mate::ast::classifier::Property* p);

	void execute(mate::executor::Context* context) override;

};

} /* end namespace mate::ast::classifier */
