#include "Expression.hh"

mate::ast::expression::Expression::Expression(){}


mate::ast::expression::Expression::~Expression(){}

mate::ast::expression::Data* mate::ast::expression::Expression::valuate(mate::executor::Context* context){ return NULL; }
std::string mate::ast::expression::Expression::reference(mate::executor::Context* context){ return ""; }
