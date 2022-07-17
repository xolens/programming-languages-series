#include "DataTypeExpression.hh"

mate::ast::expression::DataTypeExpression::DataTypeExpression(std::string _varType){
    this->_varType = _varType;
    this->_constraintTypes = NULL;
    this->_decType = mate::ast::expression::DataType::OBJECT;
}

mate::ast::expression::DataTypeExpression::DataTypeExpression(std::string _varType, std::list<mate::ast::expression::DataTypeExpression*>* _constraintTypes){
    this->_varType = _varType;
    this->_constraintTypes = _constraintTypes;
    this->_decType = mate::ast::expression::DataType::TEMPLATE;
}

mate::ast::expression::DataTypeExpression::DataTypeExpression(std::string _varType, mate::ast::expression::DataType _decType){
    this->_varType = "";
    this->_constraintTypes = NULL;
    this->_decType = _decType;
}

mate::ast::expression::DataTypeExpression::~DataTypeExpression(){}

std::string mate::ast::expression::DataTypeExpression::varType(){
    return this->_varType;
}

std::list<mate::ast::expression::DataTypeExpression*>* mate::ast::expression::DataTypeExpression::constraintTypes(){
    return this->_constraintTypes;
}

mate::ast::expression::DataType mate::ast::expression::DataTypeExpression::decType(){
    return this->_decType;
}

std::string mate::ast::expression::DataTypeExpression::dataType(){
    switch (_decType) {
        case mate::ast::expression::DataType::OBJECT: return "OBJECT";
        case mate::ast::expression::DataType::TEMPLATE: return "TEMPLATE";
        case mate::ast::expression::DataType::ARRAY: return "ARRAY";
    }
    return "";
}