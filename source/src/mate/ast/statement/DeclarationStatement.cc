#include "DeclarationStatement.hh"
#include "./../../executor/Context.hh"


mate::ast::statement::DeclarationInitializer::~DeclarationInitializer(){}

mate::ast::statement::DeclarationInitializer::DeclarationInitializer(std::string identifier, mate::ast::expression::Expression* initializer){
    this->_identifier = identifier;
    this->_initializer = initializer;
}

std::string mate::ast::statement::DeclarationInitializer::identifier(){
    return this->_identifier;
}

mate::ast::expression::Expression* mate::ast::statement::DeclarationInitializer::initializer(){
    return this->_initializer;
}

// --------------------------------------------------


mate::ast::statement::DeclarationStatement::DeclarationStatement(mate::ast::expression::DataTypeExpression* _type, std::list<mate::ast::statement::DeclarationInitializer*>* _initializers){
    this->_final = false;
    this->_type = _type;
    this->_initializers = _initializers;
}

mate::ast::statement::DeclarationStatement::~DeclarationStatement(){}


bool mate::ast::statement::DeclarationStatement::final(){
    return this->_final;
}

void mate::ast::statement::DeclarationStatement::setFinal(bool _final){
    this->_final = _final;
}

mate::ast::expression::DataTypeExpression* mate::ast::statement::DeclarationStatement::type(){
    return this->_type;
}

void mate::ast::statement::DeclarationStatement::execute(mate::executor::Context* context){
   if(this->_initializers!=NULL){
        for (mate::ast::statement::DeclarationInitializer* exp : *this->_initializers ) {
            if(exp!=NULL && exp->initializer()!=NULL){
                context->putData(exp->identifier(), exp->initializer()->valuate(context));
            }else{
                context->putData(exp->identifier(), NULL);
            }
        }
    }
}

bool mate::ast::statement::DeclarationStatement::hasIdentifier(std::string identifier){
    for (mate::ast::statement::DeclarationInitializer* exp : *this->_initializers ) {
        if(exp!=NULL && exp->identifier()==identifier){
            return true;
        }
    }
    return false;
}


std::list<std::string> mate::ast::statement::DeclarationStatement::identifiers(){
	std::list<std::string> ids;
    for (mate::ast::statement::DeclarationInitializer* exp : *this->_initializers ) {
        ids.push_back(exp->identifier());
    }
    return ids;
}