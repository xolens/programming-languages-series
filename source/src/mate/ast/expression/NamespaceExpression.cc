#include "NamespaceExpression.hh"
#include "./../../executor/Context.hh"

mate::ast::expression::NamespaceExpression::NamespaceExpression(std::string identifier){
   this->identifiers.push_back(identifier);
}

mate::ast::expression::NamespaceExpression::~NamespaceExpression(){}

mate::ast::expression::Data* mate::ast::expression::NamespaceExpression::valuate(mate::executor::Context* context){
   std::cout << "\nvaluate: NamespaceExpression";
   return NULL;
}

std::string mate::ast::expression::NamespaceExpression::get(){
   std::string str;
   int count = 0;
   for (std::string s : this->identifiers) {
      if(count>0){
         str+= ".";
      }
      str+= s;
      count++;
   }
   return str;
}

std::string mate::ast::expression::NamespaceExpression::package(){
   std::string pkg;
   auto it = this->identifiers.begin();
    for (int i = 0; i < this->identifiers.size() - 1; i++){
      if(i>0){
         pkg+= ".";
      }
      pkg+= *it;
      it++;
   }
   return pkg;
}

std::string mate::ast::expression::NamespaceExpression::name(){
   if(this->identifiers.size()>0){
      return this->identifiers.back();
   }
   return "";
}

void mate::ast::expression::NamespaceExpression::add(std::string identifier){
   this->identifiers.push_back(identifier);
}