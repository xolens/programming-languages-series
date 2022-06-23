#include "AssignmentExpression.hh"

mate::ast::expression::AssignmentExpression::AssignmentExpression(mate::ast::expression::Expression* op1, mate::ast::expression::Operator op, mate::ast::expression::Expression* op2){
   this->op1 = op1;
   this->op2 = op2;
   this->op = op;
}

mate::ast::expression::AssignmentExpression::~AssignmentExpression(){}

mate::ast::expression::Data* mate::ast::expression::AssignmentExpression::valuate(mate::executor::Context* context){
   std::string lValRef;

   if(mate::ast::expression::IdentifierExpression* exp = dynamic_cast<mate::ast::expression::IdentifierExpression*>(this->op1)){
      lValRef = exp->reference(context);
      if(lValRef.empty()){
         lValRef = context->putData(exp->getIdentifier(), mate::ast::expression::Data::_NULL);
      }
   }else if(mate::ast::expression::UnaryExpression* exp = dynamic_cast<mate::ast::expression::UnaryExpression*>(this->op1)){
      lValRef = exp->reference(context);
   }else{
      // Error: not a LVALUE
      return NULL;
   }

   if(lValRef.empty()){
      // Error: ref not found
      return NULL;
   }
     
   mate::ast::expression::Data* finalVal = NULL;

   switch (op) {
      case mate::ast::expression::Operator::EQ:
         finalVal = this->op2->valuate(context);
         break;
      case mate::ast::expression::Operator::ADD_EQ:
         finalVal = (new mate::ast::expression::BinaryExpression(
            op1, mate::ast::expression::Operator::ADD, op2
         ))->valuate(context);
         break;
      case mate::ast::expression::Operator::MUL_EQ:
         finalVal = (new mate::ast::expression::BinaryExpression(
            op1, mate::ast::expression::Operator::MUL, op2
         ))->valuate(context);
         break;
      case mate::ast::expression::Operator::DIV_EQ:
         finalVal = (new mate::ast::expression::BinaryExpression(
            op1, mate::ast::expression::Operator::DIV, op2
         ))->valuate(context);
         break;
      case mate::ast::expression::Operator::MOD_EQ:
         finalVal = (new mate::ast::expression::BinaryExpression(
            op1, mate::ast::expression::Operator::MOD, op2
         ))->valuate(context);
         break;
      case mate::ast::expression::Operator::SUB_EQ:
         finalVal = (new mate::ast::expression::BinaryExpression(
            op1, mate::ast::expression::Operator::SUB, op2
         ))->valuate(context);
         break;
   }
   context->updateByRef(lValRef, finalVal);
   return finalVal;
}