#pragma once
#include <iostream>
#include <string>
#include "ObjectType.hh"

namespace mate::ast::expression {

class ArrayType: public ObjectType {

private:

public:
	ArrayType(std::string _value);
	~ArrayType();

};

} /* end namespace mate::ast::expression */
