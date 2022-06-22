#include "PrimaryExpression.hh"

mate::ast::expression::PrimaryExpression::PrimaryExpression(mate::ast::expression::Data* primitive){
   this->primitive = primitive;
}

mate::ast::expression::PrimaryExpression::~PrimaryExpression(){}
