#pragma once
#include <list>
#include <string>
#include <map>
#include "../expression/ObjectType.hh"
#include "Modifiable.hh"


namespace mate::ast::classifier {

class FunctionHeader: public mate::ast::classifier::Modifiable {

private:
	mate::ast::expression::ObjectType* _returnType;
	std::string _name;
	std::map<std::string, mate::ast::expression::ObjectType*> _args;

public:
	FunctionHeader();
	FunctionHeader(mate::ast::expression::ObjectType* _returnType, std::string _name);
	~FunctionHeader();

	std::string getName();
	void setName(std::string s);
	std::string fullName();
	
	std::map<std::string, mate::ast::expression::ObjectType*> getArgs();
	void setArgs(std::map<std::string, mate::ast::expression::ObjectType*> args);

	mate::ast::expression::ObjectType* getReturnType();
	void setReturnType(mate::ast::expression::ObjectType* t);
};

}