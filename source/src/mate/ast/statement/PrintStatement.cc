#include "PrintStatement.hh"

mate::ast::statement::PrintStatement::PrintStatement(std::string _value){
   this->_value = _value;
}

mate::ast::statement::PrintStatement::~PrintStatement(){}
