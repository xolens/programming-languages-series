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

std::string mate::ast::expression::UnaryExpression::reference(mate::executor::Context* context){
   if(this->op1!=NULL){
      return this->op1->reference(context);
   }
   return "";
}

mate::ast::expression::Data* mate::ast::expression::UnaryExpression::valuate(mate::executor::Context* context){
   mate::ast::expression::Data* d1 = NULL;
   if(this->op1 != NULL){
      d1 = this->op1->valuate(context);
   }
   
   if(d1 == NULL){
      d1 = mate::ast::expression::Data::_NULL;
   }

   
   switch (op) {
      case mate::ast::expression::Operator::ADD:
         if(d1->type() == mate::ast::expression::Type::STRING){
            return mate::ast::expression::Data::ofString(d1->valueAsString());
         }else if(d1->type() == mate::ast::expression::Type::INT){
            return mate::ast::expression::Data::ofInt(d1->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE){
            return mate::ast::expression::Data::ofDouble(d1->getDouble());
         }
         break;
      case mate::ast::expression::Operator::SUB:
         if(d1->type() == mate::ast::expression::Type::STRING){
            std::string strVal = d1->getString();
            std::reverse(strVal.begin(), strVal.end());
            return mate::ast::expression::Data::ofString(strVal);
         }else if(d1->type() == mate::ast::expression::Type::INT){
            return mate::ast::expression::Data::ofInt(-d1->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE){
            return mate::ast::expression::Data::ofDouble(-d1->getDouble());
         }
         break;
      case mate::ast::expression::Operator::INC:
      case mate::ast::expression::Operator::DEC:
         throw std::invalid_argument( "not implementation for ++ and --" );
         break;
    }

   return NULL;
}