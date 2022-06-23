#include "IdentifierExpression.hh"

mate::ast::expression::IdentifierExpression::IdentifierExpression(std::string identifier){
   this->identifier = identifier;
}

mate::ast::expression::IdentifierExpression::~IdentifierExpression(){}

std::string mate::ast::expression::IdentifierExpression::getIdentifier(){
   return this->identifier;
}

std::string mate::ast::expression::IdentifierExpression::reference(mate::executor::Context* context){
   std::string lValRef;
   if(context->hasIdentifier(this->identifier)){
      lValRef = context->getIdentifierRef(this->identifier);
   }
   return lValRef;
}

mate::ast::expression::Data* mate::ast::expression::IdentifierExpression::valuate(mate::executor::Context* context){
   return context->getDataByIdentifier(this->identifier);
}