#include "BinaryExpression.hh"

mate::ast::expression::BinaryExpression::BinaryExpression(mate::ast::expression::Expression* op1, mate::ast::expression::Operator op, mate::ast::expression::Expression* op2){
   this->op1 = op1;
   this->op2 = op2;
   this->op = op;
}

mate::ast::expression::BinaryExpression::~BinaryExpression(){}

mate::ast::expression::Data* mate::ast::expression::BinaryExpression::valuate(mate::executor::Context* context){
    mate::ast::expression::Data* d1 = NULL;
   mate::ast::expression::Data* d2 = NULL;
   bool boolVal1;
   
   if(this->op1 != NULL){
      d1 = this->op1->valuate(context);
   }
   
   if(this->op2 != NULL){
      d2 = this->op2->valuate(context);
   }

   if(d1 == NULL){
      d1 = mate::ast::expression::Data::_NULL;
   }

   if(d2 == NULL){
      d2 = mate::ast::expression::Data::_NULL;
   }

   
   switch (op) {
      case mate::ast::expression::Operator::ADD:
         if(d1->type() == mate::ast::expression::Type::STRING || d2->type() == mate::ast::expression::Type::STRING ){
            return mate::ast::expression::Data::ofString(d1->valueAsString() + d2->valueAsString());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofInt(d1->getInt() + d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofDouble(d1->getDouble() + d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofDouble(d1->getInt() + d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofDouble(d1->getDouble() + d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::MUL:
         if((d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::STRING) 
               || (d1->type() == mate::ast::expression::Type::STRING && d2->type() == mate::ast::expression::Type::INT)){
            int count; std::string strVal; std::string finalVal;
            if(d1->type() == mate::ast::expression::Type::INT){
               count = d1->getInt();
               strVal = d2->getString();
            }else{
               count = d2->getInt();
               strVal = d1->getString();
            }
            if(count <0){
               count = -count;
               std::reverse(strVal.begin(), strVal.end());
            }
            for(int i=0; i<count ; i++){
               finalVal = finalVal + strVal;
            }
            return mate::ast::expression::Data::ofString(finalVal);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofInt(d1->getInt() * d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofDouble(d1->getDouble() * d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofDouble(d1->getInt() * d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofDouble(d1->getDouble() * d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::DIV:
         if(d1->type() == mate::ast::expression::Type::STRING && d2->type() == mate::ast::expression::Type::INT){
            
            std::string strVal = d1->getString();
            int intVal =  d2->getInt();

            if(intVal < 0){
               intVal = -intVal;
               std::reverse(strVal.begin(), strVal.end());
            }
            int count = strVal.length()/intVal;
            std::string finalVal = strVal.substr (0,count);
            
            return mate::ast::expression::Data::ofString(finalVal);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofInt(d1->getInt() / d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofDouble(d1->getDouble() / d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofDouble(d1->getInt() / d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofDouble(d1->getDouble() / d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::MOD:
         if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofInt(d1->getInt() % d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::SUB:
         if(d1->type() == mate::ast::expression::Type::STRING || d2->type() == mate::ast::expression::Type::STRING ){
            std::string strVal = d2->valueAsString();
            std::reverse(strVal.begin(), strVal.end());
            return mate::ast::expression::Data::ofString(d1->valueAsString() + strVal);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofInt(d1->getInt() - d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofDouble(d1->getDouble() - d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofDouble(d1->getInt() - d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofDouble(d1->getDouble() - d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::LS:
         if(d1->type() == mate::ast::expression::Type::STRING && d2->type() == mate::ast::expression::Type::STRING ){
            return mate::ast::expression::Data::ofBool(d1->getString().compare(d2->getString()) < 0);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getInt() < d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() < d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getInt() < d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() < d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::LS_EQ:
         if(d1->type() == mate::ast::expression::Type::STRING && d2->type() == mate::ast::expression::Type::STRING ){
            return mate::ast::expression::Data::ofBool(d1->getString().compare(d2->getString()) <= 0);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getInt() <= d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() <= d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getInt() <= d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() <= d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::GT:
         if(d1->type() == mate::ast::expression::Type::STRING && d2->type() == mate::ast::expression::Type::STRING ){
            return mate::ast::expression::Data::ofBool(d1->getString().compare(d2->getString()) > 0);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getInt() > d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() > d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getInt() > d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() > d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::GT_EQ:
         if(d1->type() == mate::ast::expression::Type::STRING && d2->type() == mate::ast::expression::Type::STRING ){
            return mate::ast::expression::Data::ofBool(d1->getString().compare(d2->getString()) >= 0);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getInt() >= d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() >= d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getInt() >= d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() >= d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::EQ2:
         if(d1->type() == mate::ast::expression::Type::STRING && d2->type() == mate::ast::expression::Type::STRING ){
            return mate::ast::expression::Data::ofBool(d1->getString().compare(d2->getString()) == 0);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getInt() == d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() == d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getInt() == d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() == d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::NOT_EQ:
         if(d1->type() == mate::ast::expression::Type::STRING && d2->type() == mate::ast::expression::Type::STRING ){
            return mate::ast::expression::Data::ofBool(d1->getString().compare(d2->getString()) != 0);
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getInt() != d2->getInt());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() != d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::DOUBLE ){
            return mate::ast::expression::Data::ofBool(d1->getInt() != d2->getDouble());
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofBool(d1->getDouble() != d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::LEFT:
         if(d2->type() == mate::ast::expression::Type::INT ){
            int intVal =  d2->getInt();
            if(intVal>=0){
               if(d1->type() == mate::ast::expression::Type::STRING){
                  std::string strVal = d1->valueAsString();
                  if(intVal < strVal.length()){
                     std::string finalVal = strVal.substr (intVal, strVal.length());
                     return mate::ast::expression::Data::ofString(finalVal);
                  }else{
                     return mate::ast::expression::Data::ofString("");
                  }
               }else if(d1->type() == mate::ast::expression::Type::INT){
                  return mate::ast::expression::Data::ofInt(d1->getInt() << intVal);
               }
            }else{
               intVal = -intVal;
               if(d1->type() == mate::ast::expression::Type::STRING){
                  std::string strVal = d1->valueAsString();
                  if(intVal < strVal.length()){
                     std::string finalVal = strVal.substr (0, strVal.length()-intVal);
                     return mate::ast::expression::Data::ofString(finalVal);
                  }else{
                     return mate::ast::expression::Data::ofString("");
                  }
               }else if(d1->type() == mate::ast::expression::Type::INT){
                  return mate::ast::expression::Data::ofInt(d1->getInt() >> intVal);
               }
            }
         }
         break;
      case mate::ast::expression::Operator::RIGHT:
         if(d2->type() == mate::ast::expression::Type::INT ){
            int intVal =  d2->getInt();
            if(intVal>=0){
               if(d1->type() == mate::ast::expression::Type::STRING){
                  std::string strVal = d1->valueAsString();
                  if(intVal < strVal.length()){
                     std::string finalVal = strVal.substr (intVal, strVal.length());
                     return mate::ast::expression::Data::ofString(finalVal);
                  }else{
                     return mate::ast::expression::Data::ofString("");
                  }
               }else if(d1->type() == mate::ast::expression::Type::INT){
                  return mate::ast::expression::Data::ofInt(d1->getInt() >> intVal);
               }
            }else{
               intVal = -intVal;
               if(d1->type() == mate::ast::expression::Type::STRING){
                  std::string strVal = d1->valueAsString();
                  if(intVal < strVal.length()){
                     std::string finalVal = strVal.substr (0, strVal.length()-intVal);
                     return mate::ast::expression::Data::ofString(finalVal);
                  }else{
                     return mate::ast::expression::Data::ofString("");
                  }
               }else if(d1->type() == mate::ast::expression::Type::INT){
                  return mate::ast::expression::Data::ofInt(d1->getInt() << intVal);
               }
            }
         }
         break;
      case mate::ast::expression::Operator::AND2:
         if(d1->type() == mate::ast::expression::Type::STRING){
            boolVal1 = d1->getString().length()>0;
         }else if(d1->type() == mate::ast::expression::Type::INT){
            boolVal1 = d1->getInt() != 0 ;
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE){
            boolVal1 = d1->getDouble() != 0;
         }else if(d1->type() == mate::ast::expression::Type::BOOL){
            boolVal1 = d1->getBool();
         }
         if(!boolVal1){
            return mate::ast::expression::Data::ofBool(boolVal1);
         }
         if(d2->type() == mate::ast::expression::Type::STRING){
            return mate::ast::expression::Data::ofBool(d2->getString().length()>0);
         }else if(d2->type() == mate::ast::expression::Type::INT){
            return mate::ast::expression::Data::ofBool(d2->getInt() != 0 );
         }else if(d2->type() == mate::ast::expression::Type::DOUBLE){
            return mate::ast::expression::Data::ofBool(d2->getDouble() != 0);
         }else if(d2->type() == mate::ast::expression::Type::BOOL){
            return mate::ast::expression::Data::ofBool(d2->getBool());
         }

         break;
      case mate::ast::expression::Operator::OR2:
         if(d1->type() == mate::ast::expression::Type::STRING){
            boolVal1 = d1->getString().length()>0;
         }else if(d1->type() == mate::ast::expression::Type::INT){
            boolVal1 = d1->getInt() != 0 ;
         }else if(d1->type() == mate::ast::expression::Type::DOUBLE){
            boolVal1 = d1->getDouble() != 0;
         }else if(d1->type() == mate::ast::expression::Type::BOOL){
            boolVal1 = d1->getBool();
         }

         if(boolVal1){
            return mate::ast::expression::Data::ofBool(boolVal1);
         }
         if(d2->type() == mate::ast::expression::Type::STRING){
            return mate::ast::expression::Data::ofBool(d2->getString().length()>0);
         }else if(d2->type() == mate::ast::expression::Type::INT){
            return mate::ast::expression::Data::ofBool(d2->getInt() != 0 );
         }else if(d2->type() == mate::ast::expression::Type::DOUBLE){
            return mate::ast::expression::Data::ofBool(d2->getDouble() != 0);
         }else if(d2->type() == mate::ast::expression::Type::BOOL){
            return mate::ast::expression::Data::ofBool(d2->getBool());
         }

         break;
      case mate::ast::expression::Operator::AND:
         if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofInt(d1->getInt() & d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::XOR:
         if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofInt(d1->getInt() ^ d2->getInt());
         }
         break;
      case mate::ast::expression::Operator::OR:
         if(d1->type() == mate::ast::expression::Type::INT && d2->type() == mate::ast::expression::Type::INT ){
            return mate::ast::expression::Data::ofInt(d1->getInt() | d2->getInt());
         }
         break;
    }

   return NULL;
}