#include "Function.hh"

mate::ast::classifier::Function::Function(){}

mate::ast::classifier::Function::Function(mate::ast::classifier::FunctionHeader* _header){
    this->_header = _header;
    this->setModifiers(_header->getModifiers());
}

mate::ast::classifier::Function::Function(mate::ast::classifier::FunctionHeader* _header, mate::ast::statement::CompoundStatement* stm){
    this->_header = _header;
    this->_compoundStat = stm;
}

mate::ast::classifier::Function::~Function(){}

mate::ast::classifier::FunctionHeader* mate::ast::classifier::Function::getHeader(){
    return this->_header;
}

void mate::ast::classifier::Function::setHeader(mate::ast::classifier::FunctionHeader* h){
    this->_header = h;
}

mate::ast::statement::CompoundStatement* mate::ast::classifier::Function::getStatements(){
    return this->_compoundStat;
}

void mate::ast::classifier::Function::setStatements(mate::ast::statement::CompoundStatement* stm){
    this->_compoundStat = stm;
}

void mate::ast::classifier::Function::execute(mate::executor::Context* context){
    if(this->_compoundStat!=NULL){
	    this->_compoundStat->execute(context);
    }
}