#include "ObjectType.hh"

mate::ast::expression::ObjectType::ObjectType(std::string _value){
    this->_value = _value;
}

mate::ast::expression::ObjectType::~ObjectType(){}

std::string mate::ast::expression::ObjectType::getValue(){
    return this->_value;
}

void mate::ast::expression::ObjectType::setValue(std::string _value){
    this->_value = _value;
}