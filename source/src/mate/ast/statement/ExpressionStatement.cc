#include "ExpressionStatement.hh"


mate::ast::statement::ExpressionStatement::ExpressionStatement(mate::ast::expression::Expression* exp){
   this->exp = exp;
}

mate::ast::statement::ExpressionStatement::~ExpressionStatement(){}

void mate::ast::statement::ExpressionStatement::execute(mate::executor::Context* context){
   if(this->exp!=NULL){
      this->exp->valuate(context);
   }
}