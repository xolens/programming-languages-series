#include "Data.hh"

const mate::ast::expression::Data mate::ast::expression::Data::_NULL = new mate::ast::expression::Data ();

mate::ast::expression::Data::~Data(){}

mate::ast::expression::Data::Data(){
    this->_type = mate::ast::expression::Type::_NULL;
}

mate::ast::expression::Data::Data(long double val){
    this->_value.doubleVal = val;
    this->_type = mate::ast::expression::Type::DOUBLE;
}

mate::ast::expression::Data::Data(long long val){
    this->_value.intVal = val;
    this->_type = mate::ast::expression::Type::INT;
}

mate::ast::expression::Data::Data(bool val){
    this->_value.boolVal = val;
    this->_type = mate::ast::expression::Type::BOOL;
}

mate::ast::expression::Data::Data(std::string val){
    this->_type = mate::ast::expression::Type::STRING;
    this->stringVal = val;
}

long double mate::ast::expression::Data::getDouble(){
    return this->_value.doubleVal;
}

long long mate::ast::expression::Data::getInt(){
    return this->_value.intVal;
}

bool mate::ast::expression::Data::getBool(){
    return this->_value.boolVal;
}

std::string mate::ast::expression::Data::getString(){
    return this->stringVal;
}

void mate::ast::expression::Data::setVal(long double val){
    this->_value.doubleVal = val;
    this->_type = mate::ast::expression::Type::DOUBLE;
}

void mate::ast::expression::Data::setVal(long long val){
    this->_value.intVal = val;
    this->_type = mate::ast::expression::Type::INT;
}

void mate::ast::expression::Data::setVal(bool val){
    this->_value.boolVal = val;
    this->_type = mate::ast::expression::Type::BOOL;
}

void mate::ast::expression::Data::setVal(std::string val){
    this->stringVal = val;
    this->_type = mate::ast::expression::Type::STRING;
}

mate::ast::expression::Type mate::ast::expression::Data::type(){
    return this->_type;
}

std::string mate::ast::expression::Data::valueAsString(){
    switch (_type) {
        case mate::ast::expression::Type::DOUBLE: return std::to_string(this->_value.doubleVal);
        case mate::ast::expression::Type::INT: return std::to_string(this->_value.intVal);
        case mate::ast::expression::Type::BOOL: return this->_value.boolVal?"true":"false";
        case mate::ast::expression::Type::STRING: return this->stringVal;
    }
    return "null";
}

std::string mate::ast::expression::Data::typeAsString(){
    switch (_type) {
        case mate::ast::expression::Type::DOUBLE: return "DOUBLE";
        case mate::ast::expression::Type::INT: return "INT";
        case mate::ast::expression::Type::BOOL: return "BOOL";
        case mate::ast::expression::Type::STRING: return "STRING";
    }
    return "any";
}