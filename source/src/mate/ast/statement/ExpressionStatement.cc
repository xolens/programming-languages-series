#include "ExpressionStatement.hh"


mate::ast::statement::ExpressionStatement::ExpressionStatement(mate::ast::expression::Expression* exp){
   this->exp = exp;
}

mate::ast::statement::ExpressionStatement::~ExpressionStatement(){}
