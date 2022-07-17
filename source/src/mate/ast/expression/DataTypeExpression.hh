#pragma once
#include <iostream>
#include <list>

#include "../statement/Statement.hh"
#include "Expression.hh"

namespace mate::ast::expression {

enum class DataType {
	OBJECT, // simple class instance type
	TEMPLATE, // parametrized class instance type
	ARRAY, // class instances array
};

class DataTypeExpression: public mate::ast::expression::Expression {

private:
	std::string _varType;
	std::list<mate::ast::expression::DataTypeExpression*>* _constraintTypes;
	mate::ast::expression::DataType _decType;

public:
	DataTypeExpression(std::string _varType);
	DataTypeExpression(std::string _varType, std::list<mate::ast::expression::DataTypeExpression*>* _constraintTypes);
	DataTypeExpression(std::list<mate::ast::expression::DataTypeExpression*>* _constraintTypes);
	DataTypeExpression(std::string _varType, mate::ast::expression::DataType _decType);
	~DataTypeExpression();

	std::string dataType();
	std::string varType();
	std::list<mate::ast::expression::DataTypeExpression*>* constraintTypes();
	mate::ast::expression::DataType decType();

	static DataTypeExpression* ofObject(std::string _varType){
		return new DataTypeExpression(_varType);
	}

	static DataTypeExpression* ofTemplate(std::string _varType, std::list<mate::ast::expression::DataTypeExpression*>* _constraintTypes){
		return new DataTypeExpression(_varType, _constraintTypes);
	}

	static DataTypeExpression* ofTemplate(std::string _varType){
		return new DataTypeExpression(_varType, NULL);
	}

	static DataTypeExpression* ofArray(std::string _varType){
		return new DataTypeExpression(_varType, mate::ast::expression::DataType::ARRAY);
	}

};

} /* end namespace mate::ast::expression */
