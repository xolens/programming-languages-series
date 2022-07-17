%defines "MateParser.y.hh"
%output "MateParser.y.cc"
%verbose
%define api.pure full
%locations
%define parse.error verbose
%param {yyscan_t  scanner}
%parse-param {mate::ast::classifier::Classifier*  _class}

%code requires{

	#include <iostream>
	#include <list>

	#include "../ast/classifier/Classifier.hh"
	#include "../ast/classifier/Property.hh"
	#include "../ast/classifier/Modifiable.hh"
	#include "../ast/statement/CompoundStatement.hh"
	#include "../ast/statement/Statement.hh"
	#include "../ast/statement/PrintStatement.hh"
	#include "../ast/statement/ExpressionStatement.hh"
	#include "../ast/statement/DeclarationStatement.hh"
	#include "../ast/classifier/FunctionHeader.hh"
	#include "../mate.hh"
	#include "../ast/classifier/Function.hh"

	#include "../ast/expression/Data.hh"
	#include "../ast/expression/ObjectType.hh"
	#include "../ast/expression/ArrayType.hh"
	#include "../ast/expression/Expression.hh"
	#include "../ast/expression/AssignmentExpression.hh"
	#include "../ast/expression/IdentifierExpression.hh"
	#include "../ast/expression/PrimaryExpression.hh"
	#include "../ast/expression/BinaryExpression.hh"
	#include "../ast/expression/UnaryExpression.hh"
	#include "../ast/expression/ConditionnalExpression.hh"
	#include "../ast/expression/DataTypeExpression.hh"
	#include "../ast/expression/NamespaceExpression.hh"
	#include "../ast/expression/InstanciationExpression.hh"

}


%code provides
{
	extern int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param , yyscan_t yyscanner);
	extern void yyerror(YYLTYPE* yylloc, yyscan_t scanner, mate::ast::classifier::Classifier* _class, const char* msg);
}

%union {
	long long _Int;
	long double _Double;
	bool _Bool;
	char _String[1000];
	mate::ast::statement::Statement* _Statement;
	mate::ast::statement::CompoundStatement* _CompoundStatement;
	mate::ast::classifier::FunctionHeader* _FunctionHeader;
	mate::ast::classifier::Function* _Function;
	mate::ast::classifier::Modifiable* _Modifiable;
	std::list<mate::ast::classifier::Modifiable*>* _ModifiableList;
	mate::ast::classifier::Property* _Property;
	mate::ast::expression::ObjectType* _ObjectType;
	mate::ast::expression::Data* _Data;
	mate::ast::expression::Expression* _Expression;
	std::list<mate::ast::expression::Expression*>* _ExpressionList;
	mate::ast::expression::Operator _Operator;
	std::list<mate::ast::statement::Statement*>* _StatementList;
	std::list<mate::ast::classifier::Modifier>* _ClassItemModifierList;
	mate::ast::classifier::Modifier _ClassItemModifier;
	mate::ast::statement::DeclarationStatement* _DeclarationStatement;
	mate::ast::expression::DataTypeExpression* _DataType;
	std::list<mate::ast::expression::DataTypeExpression*>* _DataTypeList;
	mate::ast::expression::NamespaceExpression* _NamespaceExpression;

	std::list<mate::ast::statement::DeclarationInitializer*>* _DeclarationInitializerList;
	mate::ast::statement::DeclarationInitializer* _DeclarationInitializer;
}

%type  <_FunctionHeader> function_header function_header_item
%type  <_Property> property
%type  <_Modifiable> class_item modifiable_class_item
%type  <_ModifiableList> modifiable_class_items
%type  <_CompoundStatement> compound_statement
%type  <_Function> function
%type  <_StatementList> statements
%type  <_Statement> statement print_statement exp_statement
%type  <_Data> primitive

%type  <_Expression> primary_expression expression assignment_expression
%type  <_Expression> conditional_expression logical_or_expression logical_and_expression inclusive_or_expression 
%type  <_Expression> exclusive_or_expression and_expression equality_expression relational_expression shift_expression
%type  <_Expression> additive_expression unary_expression postfix_expression multiplicative_expression




%type  <_Expression> instanciation
%type  <_ExpressionList> expression_list

%type  <_DeclarationInitializer> declaration_initializer
%type  <_DeclarationInitializerList> declaration_initializers

%type  <_NamespaceExpression> namespace
%type  <_DataType> data_type
%type  <_DataTypeList> data_type_list
%type  <_DeclarationStatement> internal_declaration declaration

%type  <_ClassItemModifierList> modifiers
%type  <_ClassItemModifier> modifier


%type  <_Operator> assignment_operator unary_operator

%token <_String> IDENTIFIER STRING_LITERAL
%token <_Int> INTEGER
%token <_Double> DOUBLE
%token <_Bool> BOOL

%token ADD_EQ SUB_EQ MUL_EQ DIV_EQ MOD_EQ INC DEC

%token ELLIPSIS
%token RIGHT_EQ LEFT_EQ AND_EQ XOR_EQ OR_EQ
%token RIGHT LEFT
%token AND2 OR2
%token EQ2 LS_EQ GT_EQ NOT_EQ

%token CLASS 
%token PUBLIC PRIVATE PROTECTED
%token STATIC VAR FINAL NEW
%token PRINT

%start entry_point

%%

entry_point
	: CLASS IDENTIFIER '{'  '}' { _class->setName($2); }
	| CLASS IDENTIFIER '{' modifiable_class_items '}' { _class->setName($2); _class->addItems($4); }
	;

modifiable_class_items
	: modifiable_class_item { $$ =  new std::list<mate::ast::classifier::Modifiable*>(); $$->push_front($1); }
	| modifiable_class_items modifiable_class_item { $$->push_back($2); }
	;

modifiable_class_item
	: class_item { $$ = $1;  }
	| modifiers class_item { $$ = $2; $$->setModifiers($1);  }
	;

modifiers
	: modifier { $$ =  new std::list<mate::ast::classifier::Modifier>(); $$->push_front($1); }
	| modifiers modifier { $$->push_back($2); }
	;

modifier
	: PUBLIC { $$ = mate::ast::classifier::Modifier::PUBLIC; }
	| PRIVATE { $$ = mate::ast::classifier::Modifier::PRIVATE; }
	| PROTECTED { $$ = mate::ast::classifier::Modifier::PROTECTED; }
	| STATIC { $$ = mate::ast::classifier::Modifier::STATIC; }
	| FINAL { $$ = mate::ast::classifier::Modifier::FINAL; }
	;

class_item
	: function { $$ = $1; }
	| property { $$ = $1; }
	| function_header_item { $$ = $1; }
	;

function
	: function_header compound_statement { $$ = new mate::ast::classifier::Function($1, $2);  }
	;

function_header
	: data_type IDENTIFIER '(' data_type IDENTIFIER ')' { $$ = new mate::ast::classifier::FunctionHeader(); }
	;

function_header_item
	: function_header ';' { $$ = $1; }
	;

compound_statement
	: '{' '}' { $$ = new mate::ast::statement::CompoundStatement(); }
	| '{' statements '}' { $$ = new mate::ast::statement::CompoundStatement(); $$->addStatement($2); }
	;

property
	: declaration ';' { $$ =  new mate::ast::classifier::Property($1); }
	;

statements
	: statement { $$ =  new std::list<mate::ast::statement::Statement*>(); $$->push_front($1); }
	| statements statement { $$->push_back($2); }
	;

statement
	: print_statement { $$ = $1; }
	| exp_statement { $$ = $1; }
	;

print_statement
	: PRINT '(' expression ')' ';' { $$ = new mate::ast::statement::PrintStatement($3); }
	;

exp_statement
	: expression ';' { $$ = new mate::ast::statement::ExpressionStatement($1); }
	| internal_declaration ';' { $$ = $1; }
	;

internal_declaration
	: FINAL declaration { $$ = $2; $$->setFinal(true); }
	| VAR declaration { $$ = $2; }
	;

declaration
	: data_type declaration_initializers { $$ = mate::ast::statement::DeclarationStatement::of($1, $2); }
	;

declaration_initializers
	: declaration_initializer { $$ = new std::list<mate::ast::statement::DeclarationInitializer*>(); $$->push_back($1); }
	| declaration_initializers ',' declaration_initializer { $$->push_back($3); }
	;

declaration_initializer
	: IDENTIFIER { $$ = mate::ast::statement::DeclarationInitializer::of($1); }
	| IDENTIFIER '=' expression { $$ = mate::ast::statement::DeclarationInitializer::of($1, $3); }
	;

data_type
	: namespace { $$ = mate::ast::expression::DataTypeExpression::ofObject($1->get()); }
	| namespace '<' '>' { $$ = mate::ast::expression::DataTypeExpression::ofTemplate($1->get(), NULL); }
	| namespace '<' data_type_list '>' { $$ = mate::ast::expression::DataTypeExpression::ofTemplate($1->get(), $3); }
	| namespace '['  ']' { $$ = mate::ast::expression::DataTypeExpression::ofArray($1->get()); }
	;

data_type_list
	: data_type { $$ = new std::list<mate::ast::expression::DataTypeExpression*>(); $$->push_back($1); }
	| data_type_list ',' data_type { $$->push_back($3); }
	;

namespace
	: IDENTIFIER { $$ = new mate::ast::expression::NamespaceExpression($1); }
	| namespace '.' IDENTIFIER { $$->add($3); }
	;

expression
	: assignment_expression { $$ = $1; }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { $$ = new mate::ast::expression::AssignmentExpression($1, $2, $3); }
	;

assignment_operator
	: '=' { $$ = mate::ast::expression::Operator::EQ; }
	| ADD_EQ { $$ = mate::ast::expression::Operator::ADD_EQ; }
	| SUB_EQ { $$ = mate::ast::expression::Operator::SUB_EQ; }
	| MUL_EQ { $$ = mate::ast::expression::Operator::MUL_EQ; }
	| DIV_EQ { $$ = mate::ast::expression::Operator::DIV_EQ; }
	| MOD_EQ { $$ = mate::ast::expression::Operator::MOD_EQ; }
	| LEFT_EQ { $$ = mate::ast::expression::Operator::LEFT_EQ; }
	| RIGHT_EQ { $$ = mate::ast::expression::Operator::RIGHT_EQ; }
	| AND_EQ { $$ = mate::ast::expression::Operator::AND_EQ; }
	| XOR_EQ { $$ = mate::ast::expression::Operator::XOR_EQ; }
	| OR_EQ { $$ = mate::ast::expression::Operator::OR_EQ; }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ =  new mate::ast::expression::ConditionnalExpression($1, $3, $5); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR2 logical_and_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::OR2, $3); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND2 inclusive_or_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::AND2, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::OR, $3); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::XOR, $3); }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::AND, $3); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ2 relational_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::EQ2, $3); }
	| equality_expression NOT_EQ relational_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::NOT_EQ, $3); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::LS, $3); }
	| relational_expression '>' shift_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::GT, $3); }
	| relational_expression LS_EQ shift_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::LS_EQ, $3); }
	| relational_expression GT_EQ shift_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::GT_EQ, $3); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT additive_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::LEFT, $3); }
	| shift_expression RIGHT additive_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::RIGHT, $3); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::ADD, $3); }
	| additive_expression '-' multiplicative_expression { $$ = new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::SUB, $3); }
	;

multiplicative_expression
	: unary_expression { $$ = $1; }
	| multiplicative_expression '*' unary_expression { $$ = new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::MUL, $3); }
	| multiplicative_expression '/' unary_expression { $$ = new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::DIV, $3); }
	| multiplicative_expression '%' unary_expression { $$ = new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::MOD, $3); }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| unary_operator unary_expression { $$ = new mate::ast::expression::UnaryExpression($1, $2); }
	;

unary_operator
	: '+' { $$ = mate::ast::expression::Operator::ADD; }
	| '-' { $$ = mate::ast::expression::Operator::SUB; }
	| INC { $$ = mate::ast::expression::Operator::INC; }
	| DEC { $$ = mate::ast::expression::Operator::DEC; }
	| '~' { $$ = mate::ast::expression::Operator::TILDE; }
	| '!' { $$ = mate::ast::expression::Operator::NOT_EQ; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression INC { $$ =  new mate::ast::expression::UnaryExpression(mate::ast::expression::Operator::INC, $1, true); }
	| postfix_expression DEC { $$ =  new mate::ast::expression::UnaryExpression(mate::ast::expression::Operator::DEC, $1, true); }
	;

primary_expression
	: primitive { $$ = new mate::ast::expression::PrimaryExpression($1); }
	| '(' expression ')' { $$ = $2; }
	| IDENTIFIER { $$ = new mate::ast::expression::IdentifierExpression($1); }
	| instanciation { $$ = $1; }
	;


instanciation
	: NEW data_type '(' ')' { $$ = new mate::ast::expression::InstanciationExpression($2, NULL, false); }
	| NEW data_type '(' expression_list ')' { $$ = new mate::ast::expression::InstanciationExpression($2, $4, false); }
	| NEW data_type '{' '}' { $$ = new mate::ast::expression::InstanciationExpression($2, NULL, true); }
	| NEW data_type '{' expression_list '}' { $$ = new mate::ast::expression::InstanciationExpression($2, $4, true); }
	| '[' ']' { $$ = new mate::ast::expression::InstanciationExpression(NULL, NULL, true); }
	| '[' expression_list ']' { $$ = new mate::ast::expression::InstanciationExpression(NULL, $2, true); }
	;

expression_list
	: assignment_expression { $$ =  new std::list<mate::ast::expression::Expression*>(); $$->push_front($1); }
	| expression_list ',' assignment_expression { $$->push_back($3); }
	;


primitive
	: INTEGER { $$ = mate::ast::expression::Data::ofInt($1); }
	| DOUBLE { $$ = mate::ast::expression::Data::ofDouble($1); }
	| STRING_LITERAL { $$ = mate::ast::expression::Data::ofString($1); }
	| BOOL { $$ = mate::ast::expression::Data::ofBool($1); }
	;
%%


void yyerror(YYLTYPE* yylloc, yyscan_t scanner, mate::ast::classifier::Classifier* _class, const char* msg)
{
   std::cerr << "Error: " << msg << " at line: " << yylloc->last_line << ", column: " << yylloc->first_column  <<")\n";
}
