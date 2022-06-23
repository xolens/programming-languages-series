#include "PrintStatement.hh"

mate::ast::statement::PrintStatement::PrintStatement(mate::ast::expression::Expression* _value){
   this->_value = _value;
}

mate::ast::statement::PrintStatement::~PrintStatement(){}


void mate::ast::statement::PrintStatement::execute(mate::executor::Context* context){
   if(this->_value!=NULL){
      mate::ast::expression::Data* data = this->_value->valuate(context);
      if(data!=NULL){
         std::cout << data->valueAsString();
         return;
      }
   }
   std::cout << "null" ;
}