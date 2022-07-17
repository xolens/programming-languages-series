#pragma once
#include <list>

namespace mate::ast::classifier {

enum class Modifier{
	PUBLIC,
	PRIVATE,
	PROTECTED,
	STATIC,
	FINAL,
};

class Modifiable {

private:
	std::list<mate::ast::classifier::Modifier>* _modifiers;

public:
	Modifiable();
	virtual ~Modifiable();

	void setModifiers(std::list<mate::ast::classifier::Modifier>* _modifiers);
	std::list<mate::ast::classifier::Modifier>* getModifiers();
	void addModifier(mate::ast::classifier::Modifier s);

};

} /* end namespace mate::ast::classifier */
