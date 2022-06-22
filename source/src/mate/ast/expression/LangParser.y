%defines "LangParser.y.hh"
%output "LangParser.y.cc"
%verbose
%define api.pure full
%locations
%define api.prefix {lang}
%define parse.error verbose
%param {yyscan_t  scanner}
%parse-param {mate::parser::lang::LangDriver*  driver}
%define api.token.prefix {LANG_}

%code requires
{

	#include <iostream>
	#include <cstdlib>
	#include <fstream>
	#include <list>

	#include <cstring>
   
	#include "LangDriver.hh"

	#include "../../ast/classifier/Modifier.hh"
	#include "../../ast/classifier/Property.hh"
	#include "../../ast/classifier/Function.hh"
	#include "../../util/list/IndexedList.hh"
	#include "../../ast/statement/Statement.hh"
	#include "../../ast/statement/ExpressionStatement.hh"
	#include "../../ast/statement/EmptyStatement.hh"
	#include "../../ast/statement/JumpStatement.hh"
	#include "../../ast/statement/TryCatchStatement.hh"
	#include "../../ast/statement/IfStatement.hh"
	#include "../../ast/statement/DoWhileStatement.hh"
	#include "../../ast/statement/WhileStatement.hh"
	#include "../../ast/statement/ForEachStatement.hh"
	#include "../../ast/statement/ForStatement.hh"
	#include "../../ast/statement/ThrowStatement.hh"
	#include "../../ast/statement/SwitchStatement.hh"
	#include "../../ast/statement/CompoundStatement.hh"
	#include "../../ast/statement/DeclarationStatement.hh"
	#include "../../ast/statement/DeclarationStatement.hh"
	
	#include "../../ast/expression/Expression.hh"
	#include "../../ast/expression/ValuationExpression.hh"
	#include "../../ast/expression/IdentifierExpression.hh"
	#include "../../ast/expression/NamespaceExpression.hh"
	#include "../../ast/expression/DataTypeExpression.hh"
	#include "../../ast/expression/AssignmentExpression.hh"
	#include "../../ast/expression/BinaryExpression.hh"
	#include "../../ast/expression/UnaryExpression.hh"
	#include "../../ast/expression/PointerExpression.hh"
	#include "../../ast/expression/PropertyAccessExpression.hh"
	#include "../../ast/expression/PrimaryExpression.hh"
	#include "../../ast/expression/ArrayAccessExpression.hh"
	#include "../../ast/expression/FunctionCallExpression.hh"
	#include "../../ast/expression/InstanciationExpression.hh"
	#include "../../ast/expression/ArrayInstanciationExpression.hh"
	#include "../../ast/expression/ConditionnalExpression.hh"
	#include "../../ast/data/Data.hh"


}

%code provides
{
	extern int langlex(LANGSTYPE * yylval_param, LANGLTYPE * yylloc_param , yyscan_t yyscanner);
	extern void langerror(LANGLTYPE* yylloc, yyscan_t scanner, mate::parser::lang::LangDriver* driver, const char* msg);
}

%union {
	long long _Int;
	long double _Double;
	bool _Bool;
	char _String[1000];
	mate::ast::classifier::Property* _Property;
	mate::ast::classifier::Function* _Function;
	mate::ast::classifier::Constructor* _Constructor;
	mate::ast::classifier::FunctionHeader* _FunctionHeader;
	mate::util::list::IndexedList<mate::ast::expression::DataTypeExpression*, std::string> *_DataTypeStringIndexedList;
	mate::ast::statement::Statement* _Statement;
	mate::ast::expression::Expression* _Expression;
	mate::ast::expression::NamespaceExpression* _NamespaceExpression;
	mate::ast::expression::AssignmentExpression* _AssignmentExpression;
	mate::ast::statement::EmptyStatement* _EmptyStatement;
	mate::ast::statement::CompoundStatement* _CompoundStatement;
	std::list<mate::ast::statement::Statement*>* _StatementList;
	std::list<mate::ast::expression::Expression*>* _ExpressionList;
	mate::ast::expression::InstanciationExpression* _InstanciationExpression;
	mate::ast::statement::CaseStatement* _CaseStatement;
	std::list<mate::ast::statement::CaseStatement*>* _CaseStatementList;
	mate::ast::expression::Data* _Primitive;
	mate::ast::expression::DataTypeExpression* _DataTypeExpression;
	std::list<mate::ast::expression::DataTypeExpression*>* _DataTypeExpressionList;
	std::list<std::string>* _StringList;
	std::list<mate::ast::statement::DeclarationInitializer*>* _DeclarationInitializerList;
	mate::ast::statement::DeclarationInitializer* _DeclarationInitializer;
	mate::ast::statement::DeclarationStatement* _DeclarationStatement;
	mate::ast::classifier::Modifier _Modifier;
	std::list<mate::ast::classifier::Modifier>* _ModifierList;

	mate::ast::expression::Data* _Array;
	mate::ast::expression::Operator _Operator;


}

%token <_Int> INTEGER
%token <_Double> DOUBLE
%token <_Bool> BOOL
%token <_String> IDENTIFIER STRING_LITERAL
%token <_String> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token <_String> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token <_String> XOR_ASSIGN OR_ASSIGN
%token <_String> INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP

%type  <_Array> dict_entry dict_entries

%type  <_DeclarationStatement> internal_declaration_exp internal_declaration declaration
%type  <_DeclarationInitializerList> declaration_initializers
%type  <_DeclarationInitializer> declaration_initializer
%type  <_DataTypeExpression> data_type
%type  <_DataTypeExpressionList> data_types
%type  <_Modifier> class_item_modifier
%type  <_ModifierList> class_item_modifiers
%type  <_NamespaceExpression> namespace
%type  <_Operator> assignment_operator
%type  <_Operator> unary_operator
%type  <_Property> property
%type  <_Function> function_definition
%type  <_Constructor> constructor
%type  <_FunctionHeader> function_header
%type  <_DataTypeStringIndexedList> function_params
%type  <_CompoundStatement> compound_statement
%type  <_StatementList> block_item_list
%type  <_ExpressionList> argument_expression_list colon_assignment_expressions

%type  <_Statement> statement block_item closed_statement simple_statement expression_statement
%type  <_Statement> try_catch_statement throw_statement jump_statement
%type  <_Statement> open_statement selection_statement
%type  <_CaseStatementList> labeled_statements
%type  <_CaseStatement> labeled_statement

%type  <_Expression> expression assignment_expression unary_expression conditional_expression
%type  <_Expression> logical_or_expression multiplicative_expression additive_expression shift_expression
%type  <_Expression> relational_expression equality_expression and_expression
%type  <_Expression> exclusive_or_expression inclusive_or_expression logical_and_expression
%type  <_Expression> postfix_expression primary_expression dictionary instanciation array_instanciation
%type  <_Primitive> primitive
%type  <_InstanciationExpression> var_instanciation

%token VOID

%token PACKAGE USE AS NEW
%token CLASS ENUM INTERFACE IMPLEMENTS EXTENDS
%token ELLIPSIS THIS 
%token THROWS THROW TRY CATCH FINALLY
%token PUBLIC PRIVATE PROTECTED STATIC FINAL ABSTRACT

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR CONTINUE BREAK RETURN

%start entry_point

%%

primitive
	: INTEGER { $$ = mate::ast::expression::Data::ofInt($1); }
	| BOOL { $$ = mate::ast::expression::Data::ofBool($1); }
	| DOUBLE { $$ = mate::ast::expression::Data::ofDouble($1); }
	| STRING_LITERAL { $$ = mate::ast::expression::Data::ofString($1); }
	;

primary_expression
	: IDENTIFIER  { $$ = new mate::ast::expression::IdentifierExpression($1); }
	| primitive { $$ =  new mate::ast::expression::PrimaryExpression($1); }
	| THIS { $$ =  new mate::ast::expression::PrimaryExpression(mate::ast::expression::Data::ofThis()); }
	| IDENTIFIER '(' ')' { $$ =  new mate::ast::expression::FunctionCallExpression(NULL, $1, NULL); }
	| IDENTIFIER '(' argument_expression_list ')' { $$ =  new mate::ast::expression::FunctionCallExpression(NULL, $1, $3); }
	| '(' expression ')' { $$ =  $2; }
	| instanciation { $$ = $1; }
	| dictionary { $$ = $1; }
	;

dictionary
	: '{' dict_entries '}'  { $$ = new mate::ast::expression::ValuationExpression($2); }
	;

dict_entries
	: dict_entry { $$ = new mate::ast::expression::Data::Data(); /* $$->addItem($1); */ }
	| dict_entries ',' dict_entry { /* $$->addItem($3); */ }
	;


dict_entry
	: expression { $$ = new mate::ast::expression::Data::Data(); /* $$->addItem($1); */ }
	| dict_entry ':' expression { /* $$->addItem($3); */ }
	;

instanciation
	: var_instanciation  { $$ = $1; }
	| array_instanciation  { $$ = $1; }
	;

var_instanciation
	: NEW data_type '(' ')' { $$ = new mate::ast::expression::InstanciationExpression($2, NULL); }
	| NEW data_type '(' argument_expression_list ')' { $$ = new mate::ast::expression::InstanciationExpression($2, $4); }
	;

array_instanciation
	: NEW data_type dictionary { $$ = new mate::ast::expression::ArrayInstanciationExpression($2, $3); }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' colon_assignment_expressions ']' { $$ =  new mate::ast::expression::ArrayAccessExpression($1, $3); }
	| postfix_expression '.' IDENTIFIER '(' ')' { $$ =  new mate::ast::expression::FunctionCallExpression($1, $3, NULL); }
	| postfix_expression '.' IDENTIFIER '(' argument_expression_list ')' { $$ =  new mate::ast::expression::FunctionCallExpression($1, $3, $5); }
	| postfix_expression '.' IDENTIFIER { $$ =  new mate::ast::expression::PointerExpression($1, $3); }
	| postfix_expression INC_OP { $$ =  new mate::ast::expression::UnaryExpression(mate::ast::expression::Operator::INC, $1, true); }
	| postfix_expression DEC_OP { $$ =  new mate::ast::expression::UnaryExpression(mate::ast::expression::Operator::DEC, $1, true); }
	;

colon_assignment_expressions
	: { $$ = new std::list<mate::ast::expression::Expression*>(); }
	| expression  { $$ = new std::list<mate::ast::expression::Expression*>(); $$->push_back($1); }
	| colon_assignment_expressions ':' expression { $$ = new std::list<mate::ast::expression::Expression*>(); $$->push_back($3); }
	| colon_assignment_expressions ':' { $$ = new std::list<mate::ast::expression::Expression*>(); $$->push_back(NULL); }
	;

argument_expression_list
	: assignment_expression { $$ =  new std::list<mate::ast::expression::Expression*>(); $$->push_front($1); }
	| argument_expression_list ',' assignment_expression { $$->push_back($3); }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ =  new mate::ast::expression::UnaryExpression(mate::ast::expression::Operator::INC, $2); }
	| DEC_OP unary_expression { $$ =  new mate::ast::expression::UnaryExpression(mate::ast::expression::Operator::DEC, $2); }
	| unary_operator unary_expression { $$ =  new mate::ast::expression::UnaryExpression($1, $2); }
	;

unary_operator
	: '&' { $$ = mate::ast::expression::Operator::AND; }
	| '*' { $$ = mate::ast::expression::Operator::MUL; }
	| '+' { $$ = mate::ast::expression::Operator::ADD; }
	| '-' { $$ = mate::ast::expression::Operator::SUB; }
	| '~' { $$ = mate::ast::expression::Operator::TILD; }
	| '!' { $$ = mate::ast::expression::Operator::NEGATE; }
	;

multiplicative_expression
	: unary_expression { $$ = $1; }
	| multiplicative_expression '*' unary_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::MUL, $3); }
	| multiplicative_expression '/' unary_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::DIV, $3); }
	| multiplicative_expression '%' unary_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::MOD, $3); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::ADD, $3); }
	| additive_expression '-' multiplicative_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::SUB, $3); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::LEFT, $3); }
	| shift_expression RIGHT_OP additive_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::RIGHT, $3); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::LESSER, $3); }
	| relational_expression '>' shift_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::GREATER, $3); }
	| relational_expression LE_OP shift_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::LESSER_EQ, $3); }
	| relational_expression GE_OP shift_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::GREATER_EQ, $3); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::EQUAL, $3); }
	| equality_expression NE_OP relational_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::NOT_EQUAL, $3); }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::AND, $3); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::XOR, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::OR, $3); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::AND2, $3); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ =  new mate::ast::expression::BinaryExpression($1, mate::ast::expression::Operator::OR2, $3); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ =  new mate::ast::expression::ConditionnalExpression($1, $3, $5); }
	;

assignment_expression
	: conditional_expression { $$ =  $1; }
	| unary_expression assignment_operator assignment_expression { $$ =  new mate::ast::expression::AssignmentExpression($1, $2, $3); }
	;

assignment_operator
	: '=' { $$ = mate::ast::expression::Operator::ASSIGN; }
	| MUL_ASSIGN { $$ = mate::ast::expression::Operator::MUL_ASSIGN; }
	| DIV_ASSIGN { $$ = mate::ast::expression::Operator::DIV_ASSIGN; }
	| MOD_ASSIGN { $$ = mate::ast::expression::Operator::MOD_ASSIGN; }
	| ADD_ASSIGN { $$ = mate::ast::expression::Operator::ADD_ASSIGN; }
	| SUB_ASSIGN { $$ = mate::ast::expression::Operator::SUB_ASSIGN; }
	| LEFT_ASSIGN { $$ = mate::ast::expression::Operator::LEFT_ASSIGN; }
	| RIGHT_ASSIGN { $$ = mate::ast::expression::Operator::RIGHT_ASSIGN; }
	| AND_ASSIGN { $$ = mate::ast::expression::Operator::AND_ASSIGN; }
	| XOR_ASSIGN { $$ = mate::ast::expression::Operator::XOR_ASSIGN; }
	| OR_ASSIGN { $$ = mate::ast::expression::Operator::OR_ASSIGN; }
	;

expression
	: assignment_expression { $$ = (mate::ast::expression::AssignmentExpression*) $1; }
/*	| expression ',' assignment_expression { $$ =  $1; $$->setNext((mate::ast::expression::AssignmentExpression*) $3); } */
	;

statement
	: open_statement
    | closed_statement

open_statement
	: IF '(' expression ')' statement { $$ =  new mate::ast::statement::IfStatement($3, $5, NULL); }
	| IF '(' expression ')' closed_statement ELSE open_statement { $$ =  new mate::ast::statement::IfStatement($3, $5, $7); }
	| WHILE '(' expression ')' open_statement { $$ = new mate::ast::statement::WhileStatement($3, $5); }
	| FOR '(' expression_statement expression_statement ')' open_statement { $$ = new mate::ast::statement::ForStatement($3, $4, NULL, $6); }
	| FOR '(' expression_statement expression_statement expression ')' open_statement { $$ = new mate::ast::statement::ForStatement($3, $4, new mate::ast::statement::ExpressionStatement($5), $7); }
	| FOR '(' declaration expression_statement ')' open_statement { $$ = new mate::ast::statement::ForStatement($3, $4, NULL, $6); }
	| FOR '(' declaration expression_statement expression ')' open_statement { $$ = new mate::ast::statement::ForStatement($3, $4, new mate::ast::statement::ExpressionStatement($5), $7); }
	| FOR '(' data_type IDENTIFIER ':' assignment_expression ')' open_statement { $$ = new mate::ast::statement::ForEachStatement($4, $5, $7, $9); }
	;

closed_statement
	: simple_statement 
	| IF '(' expression ')' closed_statement ELSE closed_statement { $$ =  new mate::ast::statement::IfStatement($3, $5, $7); }
	| WHILE '(' expression ')' closed_statement { $$ = new mate::ast::statement::WhileStatement($3, $5); }
	| FOR '(' expression_statement expression_statement ')' closed_statement { $$ = new mate::ast::statement::ForStatement($3, $4, NULL, $6); }
	| FOR '(' expression_statement expression_statement expression ')' closed_statement { $$ = new mate::ast::statement::ForStatement($3, $4, new mate::ast::statement::ExpressionStatement($5), $7); }
	| FOR '(' declaration expression_statement ')' closed_statement { $$ = new mate::ast::statement::ForStatement($3, $4, NULL, $6); }
	| FOR '(' declaration expression_statement expression ')' closed_statement { $$ = new mate::ast::statement::ForStatement($3, $4, new mate::ast::statement::ExpressionStatement($5), $7); }
	| FOR '(' data_type IDENTIFIER ':' assignment_expression ')' closed_statement { $$ = new mate::ast::statement::ForEachStatement($4, $5, $7, $9); }
	;

simple_statement
	: expression_statement { $$ = $1; } 
	| compound_statement { $$ = $1; } 
	| throw_statement { $$ = $1; }
	| jump_statement { $$ = $1; }
	| DO statement WHILE '(' expression ')' { $$ = new mate::ast::statement::DoWhileStatement($5, $2); }
	| try_catch_statement { $$ = $1; }
	| selection_statement { $$ = $1; } 
	;

try_catch_statement
	: TRY compound_statement CATCH '(' function_params ')' compound_statement { $$ = new mate::ast::statement::TryCatchStatement($2, $7, NULL, $5); }
	| TRY compound_statement CATCH '(' function_params ')'  compound_statement FINALLY compound_statement { $$ = new mate::ast::statement::TryCatchStatement($2, $7, $9, $5); }
	;

selection_statement
	: SWITCH '(' expression ')' '{' labeled_statements '}' { $$ =  new mate::ast::statement::SwitchStatement($3, $6, NULL); }
	| SWITCH '(' expression ')' '{' labeled_statements DEFAULT ':' '}' { $$ =  new mate::ast::statement::SwitchStatement($3, $6, NULL); }
	| SWITCH '(' expression ')' '{' labeled_statements DEFAULT ':' block_item_list '}' { $$ =  new mate::ast::statement::SwitchStatement($3, $6, $9); }
	; 

labeled_statements
	: labeled_statement { $$ =  new std::list<mate::ast::statement::CaseStatement*>(); $$->push_front($1); }
	| labeled_statements labeled_statement { $$->push_back($2); }
	; 

labeled_statement
	: CASE expression ':' { $$ =  new mate::ast::statement::CaseStatement($2, NULL); }
	| CASE expression ':' block_item_list { $$ =  new mate::ast::statement::CaseStatement($2, $4); }
	; 

compound_statement
	: '{' '}' { $$ =  new mate::ast::statement::CompoundStatement(); }
	| '{' block_item_list '}' { $$ =  new mate::ast::statement::CompoundStatement(); $$->addStatements($2); }
	;

block_item_list
	: block_item { $$ =  new std::list<mate::ast::statement::Statement*>(); $$->push_front($1); }
	| block_item_list block_item { $$->push_back($2); }
	;

block_item
	: declaration { $$ =  $1; }
	| statement { $$ =  $1; }
	;

expression_statement
	: ';' { $$ = new mate::ast::statement::EmptyStatement(); }
	| expression ';'  { $$ =  new mate::ast::statement::ExpressionStatement($1); }
	;

jump_statement
	: CONTINUE ';' { $$ = mate::ast::statement::JumpStatement::of(mate::ast::statement::Type::CONTINUE);}
	| BREAK ';' { $$ = mate::ast::statement::JumpStatement::of(mate::ast::statement::Type::BREAK);}
	| RETURN ';' { $$ = mate::ast::statement::JumpStatement::of(mate::ast::statement::Type::RETURN);}
	| RETURN expression ';' { $$ = mate::ast::statement::JumpStatement::of(mate::ast::statement::Type::RETURN, $2);}
	;

entry_point
	: translation_unit { driver->classifier->init(); }
	;

translation_unit
	: package_statement classifier
	| package_statement use_statements classifier
	| use_statements classifier 
	| classifier
	;

package_statement
	: PACKAGE namespace ';' { driver->classifier->setNamespace($2->get()); }

namespace
	: IDENTIFIER { $$ = new mate::ast::expression::NamespaceExpression($1); }
	| namespace '.' IDENTIFIER { $$->add($3); }
	;

use_statements
	: use_statement
	| use_statements use_statement
	;

use_statement
	: USE namespace ';' { driver->classifier->addUse($2); }
	| USE namespace AS IDENTIFIER ';' { driver->classifier->addUse($2, $4); }
	;

throw_statement
	: THROWS var_instanciation { $$ = new mate::ast::expression::ThrowStatement($2); }
	;

classifier
	: class_definition { driver->classifier->classType(); }
	| enum_definition { driver->classifier->enumType(); }
	| interface_definition { driver->classifier->interfaceType(); }
	;

enum_definition
	: ENUM IDENTIFIER '{' '}' { driver->classifier->setName($2); }
	| ENUM IDENTIFIER '{' enum_items '}' { driver->classifier->setName($2); }
	| ENUM IDENTIFIER '{' enum_items ',' '}' { driver->classifier->setName($2); }
	;

enum_items
	: enum_item
	| enum_items ',' enum_item
	;

enum_item
	: IDENTIFIER  { driver->classifier->addEnum($1); }
	;

interface_definition
	: INTERFACE IDENTIFIER '{' '}'  { driver->classifier->setName($2); }
	| INTERFACE IDENTIFIER '{' interface_items '}'  { driver->classifier->setName($2); }
	| INTERFACE IDENTIFIER EXTENDS data_type '{' '}'  { driver->classifier->setName($2); driver->classifier->setExtends($4); }
	| INTERFACE IDENTIFIER EXTENDS data_type '{' interface_items '}'  { driver->classifier->setName($2);driver->classifier->setExtends($4); }
	;

interface_items
	: interface_item
	| interface_items interface_item
	;

interface_item
	: function_declaration;

class_definition
	: CLASS IDENTIFIER '{' '}'  { driver->classifier->setName($2); }
	| CLASS IDENTIFIER '{' class_items '}'  { driver->classifier->setName($2); }
	| CLASS IDENTIFIER IMPLEMENTS data_types '{' '}'  { driver->classifier->setName($2); driver->classifier->setImplements($4); }
	| CLASS IDENTIFIER IMPLEMENTS data_types '{' class_items '}'  { driver->classifier->setName($2); driver->classifier->setImplements($4); }
	| CLASS IDENTIFIER EXTENDS data_type '{' '}'  { driver->classifier->setName($2); driver->classifier->setExtends($4); }
	| CLASS IDENTIFIER EXTENDS data_type '{' class_items '}'  { driver->classifier->setName($2); driver->classifier->setExtends($4); }
	| CLASS IDENTIFIER EXTENDS data_type IMPLEMENTS data_types '{' '}'  { driver->classifier->setName($2); driver->classifier->setExtends($4); driver->classifier->setImplements($6); }
	| CLASS IDENTIFIER EXTENDS data_type IMPLEMENTS data_types '{' class_items '}'  { driver->classifier->setName($2); driver->classifier->setExtends($4); driver->classifier->setImplements($6); }
	;

class_items
	: class_item
	| class_items class_item 
	;

class_item
	: property { driver->classifier->addProperties($1); }
	| class_item_modifiers property {  $2->setModifiers($1); driver->classifier->addProperties($2); }
	| function_definition { driver->classifier->addFunction($1); }
	| class_item_modifiers function_definition { $2->getHeader()->setModifiers($1); driver->classifier->addFunction($2); }
	| function_declaration
	| class_item_modifiers function_declaration
	| constructor { driver->classifier->addConstructor($1); }
	| class_item_modifiers constructor { $2->setModifiers($1); driver->classifier->addConstructor($2); }
	| static_initializer
	| class_item_modifiers static_initializer
	| classifier
	| class_item_modifiers classifier
	;


constructor
	: IDENTIFIER '(' ')' compound_statement {  $$ =  new mate::ast::classifier::Constructor($1, $4);  }
	| IDENTIFIER '(' function_params ')' compound_statement {  $$ =  new mate::ast::classifier::Constructor($1, *$3, $5);  }
	;

static_initializer
	: STATIC compound_statement
	;

function_declaration
	: function_header ';'
	;

property
	: internal_declaration { $$ =  new mate::ast::classifier::Property($1); }
	;

class_item_modifiers
	: class_item_modifier { $$ =  new std::list<mate::ast::classifier::Modifier>(); $$->push_front($1); }
	| class_item_modifiers class_item_modifier { $$->push_back($2); }
	;

class_item_modifier
	: PUBLIC { $$ = mate::ast::classifier::Modifier::PUBLIC; }
	| PRIVATE { $$ = mate::ast::classifier::Modifier::PRIVATE; }
	| PROTECTED { $$ = mate::ast::classifier::Modifier::PROTECTED; }
	| DEFAULT { $$ = mate::ast::classifier::Modifier::DEFAULT; }
	| STATIC { $$ = mate::ast::classifier::Modifier::STATIC; }
	| FINAL { $$ = mate::ast::classifier::Modifier::FINAL; }
	| ABSTRACT { $$ = mate::ast::classifier::Modifier::ABSTRACT; }
	;

declaration
	: internal_declaration { $$ = $2; }
	;

internal_declaration
	: internal_declaration_exp ';'
	;

internal_declaration_exp
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
	| namespace '<' data_types '>' { $$ = mate::ast::expression::DataTypeExpression::ofTemplate($1->get(), $3); }
	| namespace '['  ']' { $$ = mate::ast::expression::DataTypeExpression::ofArray($1->get()); }
	;

data_types
	: data_type { $$ = new std::list<mate::ast::expression::DataTypeExpression*>(); $$->push_back($1); }
	| data_types ',' data_type { $$->push_back($3); }
	;


function_definition
	: function_header compound_statement { $$ =  new mate::ast::classifier::Function($1, $2); }
	;

function_header
	: data_type IDENTIFIER '(' ')' { $$ =  new mate::ast::classifier::FunctionHeader($1, $2); }
	| data_type IDENTIFIER '(' function_params ')' { $$ =  new mate::ast::classifier::FunctionHeader($1, $2); $$->setArgs(*$4); }
	| VOID IDENTIFIER '(' ')' { $$ =  new mate::ast::classifier::FunctionHeader(NULL, $2); }
	| VOID IDENTIFIER '(' function_params ')' { $$ =  new mate::ast::classifier::FunctionHeader(NULL, $2); $$->setArgs(*$4); }
	| data_type IDENTIFIER '(' ')' THROW data_types { $$ =  new mate::ast::classifier::FunctionHeader($1, $2); }
	| data_type IDENTIFIER '(' function_params ')' THROW data_types { $$ =  new mate::ast::classifier::FunctionHeader($1, $2); $$->setArgs(*$4); }
	| VOID IDENTIFIER '(' ')' THROW data_types { $$ =  new mate::ast::classifier::FunctionHeader(NULL, $2); }
	| VOID IDENTIFIER '(' function_params ')' THROW data_types { $$ =  new mate::ast::classifier::FunctionHeader(NULL, $2); $$->setArgs(*$4); }
	;

function_params
	: data_type IDENTIFIER { $$ =  new mate::util::list::IndexedList<mate::ast::expression::DataTypeExpression*, std::string>(); $$->put($1, $2); }
	| function_params ',' data_type IDENTIFIER { $$->put($3, $4); }
	;

%%


void langerror(LANGLTYPE* yylloc, yyscan_t scanner, mate::parser::lang::LangDriver* driver, const char* msg)
{
   std::cerr << "Error: " << msg << " at (line :" << yylloc->first_line <<  ", col :" << yylloc->first_column <<")\n";
}
