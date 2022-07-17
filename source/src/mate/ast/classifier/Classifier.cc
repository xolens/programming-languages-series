#include "Classifier.hh"

mate::ast::classifier::Classifier::Classifier(){
}

mate::ast::classifier::Classifier::~Classifier(){}


std::string  mate::ast::classifier::Classifier::getName(){
    return this->_name;
}

void mate::ast::classifier::Classifier::setName(std::string  s){
    this->_name = s;
}

void mate::ast::classifier::Classifier::addItems(std::list<mate::ast::classifier::Modifiable*>* classItems){
    for (mate::ast::classifier::Modifiable* m: *classItems) {
        if(mate::ast::classifier::Property* exp = dynamic_cast<mate::ast::classifier::Property*>(m)){
            this->addProperty(exp);
        }else if(mate::ast::classifier::Function* exp = dynamic_cast<mate::ast::classifier::Function*>(m)){
            this->addFunction(exp);
        }
    }
}

std::list<mate::ast::classifier::Function*> mate::ast::classifier::Classifier::getFunctions(){
    return this->_functions;
}

void mate::ast::classifier::Classifier::addFunction(mate::ast::classifier::Function* f){
	this->_functions.push_back(f);
}

std::list<mate::ast::classifier::Property*> mate::ast::classifier::Classifier::getProperties(){
    return this->_properties;
}

void mate::ast::classifier::Classifier::addProperty(mate::ast::classifier::Property* p){
	this->_properties.push_back(p);
}

void mate::ast::classifier::Classifier::execute(mate::executor::Context* context){
  if(!this->_functions.empty()){
        mate::ast::classifier::Function* _function = this->getFunctions().front();
        if(_function!=NULL){
            _function->execute(context);
        }
    }
}