#include "UnaryExpression.hh"

mate::ast::expression::UnaryExpression::UnaryExpression(mate::ast::expression::Operator op, mate::ast::expression::Expression* op1){
   this->op = op;
   this->op1 = op1;
   this->postfix = false;
}

mate::ast::expression::UnaryExpression::UnaryExpression(mate::ast::expression::Operator op, mate::ast::expression::Expression* op1, bool postfix){
   this->op = op;
   this->op1 = op1;
   this->postfix = postfix;
}

mate::ast::expression::UnaryExpression::~UnaryExpression(){}
