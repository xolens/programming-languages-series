#include "Modifiable.hh"

mate::ast::classifier::Modifiable::Modifiable(){
    this->_modifiers = NULL;
}

mate::ast::classifier::Modifiable::~Modifiable(){}

void mate::ast::classifier::Modifiable::setModifiers(std::list<mate::ast::classifier::Modifier>* _mod){
    this->_modifiers = _mod;
}

std::list<mate::ast::classifier::Modifier>* mate::ast::classifier::Modifiable::getModifiers(){
    return this->_modifiers;
}

void mate::ast::classifier::Modifiable::addModifier(mate::ast::classifier::Modifier  s){
    return this->_modifiers->push_back(s);;
}


