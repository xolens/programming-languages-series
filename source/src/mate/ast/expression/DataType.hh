#pragma once
#include <iostream>
#include <list>

namespace mate::ast::expression {

class DataType {

private:
	std::string _value;

public:
	DataType(std::string _value);
	~DataType();

	void setValue(std::string _value);
	std::string getValue();
};

} /* end namespace mate::ast::expression */
