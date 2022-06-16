#pragma once
#include <iostream>
#include <string>
#include "DataType.hh"

namespace mate::ast::expression {

class ArrayType: public DataType {

private:

public:
	ArrayType(std::string _value);
	~ArrayType();

};

} /* end namespace mate::ast::expression */
