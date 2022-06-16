#include "DataType.hh"

mate::ast::expression::DataType::DataType(std::string _value){
    this->_value = _value;
}

mate::ast::expression::DataType::~DataType(){}

std::string mate::ast::expression::DataType::getValue(){
    return this->_value;
}

void mate::ast::expression::DataType::setValue(std::string _value){
    this->_value = _value;
}