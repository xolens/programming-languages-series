#include "ConditionnalExpression.hh"

mate::ast::expression::ConditionnalExpression::ConditionnalExpression(mate::ast::expression::Expression* condition, mate::ast::expression::Expression* ifExpr, mate::ast::expression::Expression* elseExpr){
   this->condition = condition;
   this->ifExpr = ifExpr;
   this->elseExpr = elseExpr;
}

mate::ast::expression::ConditionnalExpression::~ConditionnalExpression(){}
