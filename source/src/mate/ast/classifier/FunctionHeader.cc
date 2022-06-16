#include "FunctionHeader.hh"


mate::ast::classifier::FunctionHeader::FunctionHeader(){
    this->_returnType = NULL;
}

mate::ast::classifier::FunctionHeader::FunctionHeader(mate::ast::expression::DataType* _returnType, std::string _name){
    this->_name = _name;
    this->_returnType = _returnType;
}

mate::ast::classifier::FunctionHeader::~FunctionHeader(){}

std::string mate::ast::classifier::FunctionHeader::getName(){
    return this->_name;
}

void mate::ast::classifier::FunctionHeader::setName(std::string s){
    this->_name = s;
}

std::string mate::ast::classifier::FunctionHeader::fullName(){
    return this->_name;
}

std::map<std::string, mate::ast::expression::DataType*> mate::ast::classifier::FunctionHeader::getArgs(){
    return this->_args;
}

void mate::ast::classifier::FunctionHeader::setArgs(std::map<std::string, mate::ast::expression::DataType*> s){
    this->_args = s;
}

mate::ast::expression::DataType* mate::ast::classifier::FunctionHeader::getReturnType(){
    return this->_returnType;
}

void mate::ast::classifier::FunctionHeader::setReturnType(mate::ast::expression::DataType* t){
    this->_returnType = t;
}