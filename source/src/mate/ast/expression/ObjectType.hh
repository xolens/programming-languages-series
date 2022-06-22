#pragma once
#include <iostream>
#include <list>

namespace mate::ast::expression {

class ObjectType {

private:
	std::string _value;

public:
	ObjectType(std::string _value);
	~ObjectType();

	void setValue(std::string _value);
	std::string getValue();
};

} /* end namespace mate::ast::expression */
