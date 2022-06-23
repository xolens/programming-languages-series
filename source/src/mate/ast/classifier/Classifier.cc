#include "Classifier.hh"

mate::ast::classifier::Classifier::Classifier(){
    this->_function = NULL;
}

mate::ast::classifier::Classifier::~Classifier(){}


std::string  mate::ast::classifier::Classifier::getName(){
    return this->_name;
}

void mate::ast::classifier::Classifier::setName(std::string  s){
    this->_name = s;
}

mate::ast::classifier::Function* mate::ast::classifier::Classifier::getFunction(){
    return this->_function;
}

void mate::ast::classifier::Classifier::setFunction(mate::ast::classifier::Function* f){
	this->_function = f;
}

void mate::ast::classifier::Classifier::execute(mate::executor::Context* context){
    if(this->_function!=NULL){
	    this->_function->execute(context);
    }
}