#include "AssignmentExpression.hh"

mate::ast::expression::AssignmentExpression::AssignmentExpression(mate::ast::expression::Expression* op1, mate::ast::expression::Operator op, mate::ast::expression::Expression* op2){
   this->op1 = op1;
   this->op2 = op2;
   this->op = op;
}

mate::ast::expression::AssignmentExpression::~AssignmentExpression(){}