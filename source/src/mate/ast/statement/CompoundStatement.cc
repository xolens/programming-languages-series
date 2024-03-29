#include "CompoundStatement.hh"

mate::ast::statement::CompoundStatement::CompoundStatement(){}

mate::ast::statement::CompoundStatement::~CompoundStatement(){}

std::list<mate::ast::statement::Statement*> mate::ast::statement::CompoundStatement::getStatements(){
   return this->_statements;
}

void mate::ast::statement::CompoundStatement::addStatement(mate::ast::statement::Statement* s){
   if(s!=NULL){
      this->_statements.push_back(s);
   }
}

void mate::ast::statement::CompoundStatement::addStatement(std::list<mate::ast::statement::Statement*>* statements){
   for (mate::ast::statement::Statement* s: *statements) {
      this->_statements.push_back(s);
   }
}


void mate::ast::statement::CompoundStatement::execute(mate::executor::Context* context){
   for (mate::ast::statement::Statement*  s : this->_statements ) {
      s->execute(context);
   }
}