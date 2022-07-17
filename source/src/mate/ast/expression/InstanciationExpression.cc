#include "InstanciationExpression.hh"
#include "./../../executor/Context.hh"

mate::ast::expression::InstanciationExpression::InstanciationExpression(mate::ast::expression::DataTypeExpression* dataType, std::list<mate::ast::expression::Expression*>* params, bool hasArrayValues){
   this->dataType = dataType;
   this->params = params;
   this->hasArrayValues = hasArrayValues;
}

mate::ast::expression::InstanciationExpression::~InstanciationExpression(){}

mate::ast::expression::Data* mate::ast::expression::InstanciationExpression::valuate(mate::executor::Context* context){
   std::cout << "\nvaluate: InstanciationExpression";
   return NULL;
}