#include "Property.hh"

mate::ast::classifier::Property::Property(){}

mate::ast::classifier::Property::~Property(){}

mate::ast::classifier::Property::Property(mate::ast::statement::DeclarationStatement* declaration){
    this->declaration = declaration;
}

std::string mate::ast::classifier::Property::getName(){
    return "{ no defined }";  
}

mate::ast::statement::DeclarationStatement* mate::ast::classifier::Property::getDeclaration(){
    return this->declaration;
}

void mate::ast::classifier::Property::setDeclaration(mate::ast::statement::DeclarationStatement* s){
    this->declaration = s;
}

bool mate::ast::classifier::Property::hasIdentifier(std::string identifier){
    return this->declaration!=NULL && this->declaration->hasIdentifier(identifier);
}

std::list<std::string> mate::ast::classifier::Property::identifiers(){
    return this->declaration->identifiers();
}