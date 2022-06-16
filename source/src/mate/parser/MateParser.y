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
	#include "../ast/classifier/Classifier.hh"
	#include "../ast/statement/CompoundStatement.hh"
	#include "../ast/statement/Statement.hh"
	#include "../ast/statement/PrintStatement.hh"
	#include "../ast/classifier/FunctionHeader.hh"
	#include "../mate.hh"
	#include "../ast/classifier/Function.hh"
	#include "../ast/expression/DataType.hh"
	#include "../ast/expression/ArrayType.hh"

}


%code provides
{
	extern int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param , yyscan_t yyscanner);
	extern void yyerror(YYLTYPE* yylloc, yyscan_t scanner, mate::ast::classifier::Classifier* _class, const char* msg);
}

%union {
	char _String[1000];
	mate::ast::statement::Statement* _Statement;
	mate::ast::statement::CompoundStatement* _CompoundStatement;
	mate::ast::classifier::FunctionHeader* _FunctionHeader;
	mate::ast::classifier::Function* _Function;
	mate::ast::expression::DataType* _DataType;

}

%token <_String> IDENTIFIER STRING_LITERAL

%type  <_FunctionHeader> function_header
%type  <_CompoundStatement> compound_statement
%type  <_Function> function
%type  <_Statement> statement
%type  <_DataType> data_type

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
	: IDENTIFIER { $$ = new mate::ast::expression::DataType($1); }
	| IDENTIFIER '['  ']' { $$ = new mate::ast::expression::ArrayType($1); }
	;

compound_statement
	: '{' statement '}' { $$ = new mate::ast::statement::CompoundStatement(); $$->addStatement($2); }
	;

statement
	: PRINT STRING_LITERAL ';' { $$ = new mate::ast::statement::PrintStatement($2) ; }
	;

%%


void yyerror(YYLTYPE* yylloc, yyscan_t scanner, mate::ast::classifier::Classifier* _class, const char* msg)
{
   std::cerr << "Error: " << msg << " at line: " << yylloc->last_line << ", column: " << yylloc->first_column  <<")\n";
}
