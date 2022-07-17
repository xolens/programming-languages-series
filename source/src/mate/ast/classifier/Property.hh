#pragma once
#include <iostream>
#include <list>

#include "Modifiable.hh"
#include "../statement/DeclarationStatement.hh"


namespace mate::ast::classifier {

class Property: public Modifiable {

private:
	mate::ast::statement::DeclarationStatement* declaration;


public:
	Property();
	Property(mate::ast::statement::DeclarationStatement* declaration);
	~Property();

	std::string getName();
	mate::ast::statement::DeclarationStatement* getDeclaration();
	void setDeclaration(mate::ast::statement::DeclarationStatement* s);

	bool hasIdentifier(std::string identifier);
	std::list<std::string> identifiers();
	
};

} /* end namespace mate::ast::classifier */
