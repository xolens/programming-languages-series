#pragma once
#include <list>
#include <string>
#include <map>
#include "../expression/DataType.hh"
#include "Modifiable.hh"


namespace mate::ast::classifier {

class FunctionHeader: public mate::ast::classifier::Modifiable {

private:
	mate::ast::expression::DataType* _returnType;
	std::string _name;
	std::map<std::string, mate::ast::expression::DataType*> _args;

public:
	FunctionHeader();
	FunctionHeader(mate::ast::expression::DataType* _returnType, std::string _name);
	~FunctionHeader();

	std::string getName();
	void setName(std::string s);
	std::string fullName();
	
	std::map<std::string, mate::ast::expression::DataType*> getArgs();
	void setArgs(std::map<std::string, mate::ast::expression::DataType*> args);

	mate::ast::expression::DataType* getReturnType();
	void setReturnType(mate::ast::expression::DataType* t);
};

}