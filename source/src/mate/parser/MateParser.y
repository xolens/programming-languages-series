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
	#include "../ast/statement/CompoundStatement.hh"
	#include "../ast/statement/Statement.hh"
	#include "../ast/statement/PrintStatement.hh"
	#include "../ast/statement/ExpressionStatement.hh"
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

}


%code provides
{
	extern int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param , yyscan_t yyscanner);
	extern void yyerror(YYLTYPE* yylloc, yyscan_t scanner, mate::ast::classifier::Classifier* _class, const char* msg);
}

%union {
	long long _Int;
	long double _Double;
	char _String[1000];
	mate::ast::statement::Statement* _Statement;
	mate::ast::statement::CompoundStatement* _CompoundStatement;
	mate::ast::classifier::FunctionHeader* _FunctionHeader;
	mate::ast::classifier::Function* _Function;
	mate::ast::expression::ObjectType* _ObjectType;
	mate::ast::expression::Data* _Data;
	mate::ast::expression::Expression* _Expression;
	mate::ast::expression::Operator _Operator;
	std::list<mate::ast::statement::Statement*>* _StatementList;
}

%type  <_FunctionHeader> function_header
%type  <_CompoundStatement> compound_statement
%type  <_Function> function
%type  <_StatementList> statements
%type  <_Statement> statement print_statement exp_statement
%type  <_ObjectType> data_type
%type  <_Data> primitive
%type  <_Expression> primary_expression expression assignment_expression
%type  <_Expression> additive_expression unary_expression multiplicative_expression
%type  <_Operator> assignment_operator unary_operator

%token <_String> IDENTIFIER STRING_LITERAL
%token <_Int> INTEGER
%token <_Double> DOUBLE

%token ADD_EQ SUB_EQ MUL_EQ DIV_EQ MOD_EQ INC DEC

%token CLASS 
%token PUBLIC STATIC
%token PRINT

%start entry_point

%%

entry_point
	: CLASS IDENTIFIER '{' '}' { _class->setName($2); }
	| CLASS IDENTIFIER '{' function '}' { _class->setName($2); _class->setFunction($4); }
	;

function
	: function_header compound_statement { $$ = new mate::ast::classifier::Function($1, $2);  }
	;

function_header
	: PUBLIC STATIC data_type IDENTIFIER '(' data_type IDENTIFIER ')' { $$ = new mate::ast::classifier::FunctionHeader(); }
	;

data_type
	: IDENTIFIER { $$ = new mate::ast::expression::ObjectType($1); }
	| IDENTIFIER '['  ']' { $$ = new mate::ast::expression::ArrayType($1); }
	;

compound_statement
	: '{' '}' { $$ = new mate::ast::statement::CompoundStatement(); }
	| '{' statements '}' { $$ = new mate::ast::statement::CompoundStatement(); $$->addStatement($2); }
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
	: PRINT expression ';' { $$ = new mate::ast::statement::PrintStatement($2); }
	;

exp_statement
	: expression ';' { $$ = new mate::ast::statement::ExpressionStatement($1); }
	;

expression
	: assignment_expression { $$ = $1; }
	;

assignment_expression
	: additive_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { $$ = new mate::ast::expression::AssignmentExpression($1, $2, $3); }
	;

assignment_operator
	: '=' { $$ = mate::ast::expression::Operator::EQ; }
	| ADD_EQ { $$ = mate::ast::expression::Operator::ADD_EQ; }
	| SUB_EQ { $$ = mate::ast::expression::Operator::SUB_EQ; }
	| MUL_EQ { $$ = mate::ast::expression::Operator::MUL_EQ; }
	| DIV_EQ { $$ = mate::ast::expression::Operator::DIV_EQ; }
	| MOD_EQ { $$ = mate::ast::expression::Operator::MOD_EQ; }
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
	: primary_expression { $$ = $1; }
	| unary_operator unary_expression { $$ = new mate::ast::expression::UnaryExpression($1, $2); }
	;

unary_operator
	: '+' { $$ = mate::ast::expression::Operator::ADD; }
	| '-' { $$ = mate::ast::expression::Operator::SUB; }
	| INC { $$ = mate::ast::expression::Operator::INC; }
	| DEC { $$ = mate::ast::expression::Operator::DEC; }
	;

primary_expression
	: primitive { $$ = new mate::ast::expression::PrimaryExpression($1); }
	| '(' expression ')' { $$ = $2; }
	| IDENTIFIER { $$ = new mate::ast::expression::IdentifierExpression($1); }
	;

primitive
	: INTEGER { $$ = mate::ast::expression::Data::ofInt($1); }
	| DOUBLE { $$ = mate::ast::expression::Data::ofDouble($1); }
	| STRING_LITERAL { $$ = mate::ast::expression::Data::ofString($1); }
	;
%%


void yyerror(YYLTYPE* yylloc, yyscan_t scanner, mate::ast::classifier::Classifier* _class, const char* msg)
{
   std::cerr << "Error: " << msg << " at line: " << yylloc->last_line << ", column: " << yylloc->first_column  <<")\n";
}
