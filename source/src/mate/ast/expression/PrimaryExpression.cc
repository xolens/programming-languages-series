#include "PrimaryExpression.hh"

mate::ast::expression::PrimaryExpression::PrimaryExpression(mate::ast::expression::Data* primitive){
   this->primitive = primitive;
}

mate::ast::expression::PrimaryExpression::~PrimaryExpression(){}

mate::ast::expression::Data* mate::ast::expression::PrimaryExpression::valuate(mate::executor::Context* context){
   return this->primitive;
}
