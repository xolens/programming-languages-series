%defines "MateParser.y.hh"
%output "MateParser.y.cc"
%verbose
%define api.pure full
%locations
%define parse.error verbose
%param {yyscan_t  scanner}

%code requires{

	#include <iostream>
	#include "../mate.hh"
}


%code provides
{
	extern int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param , yyscan_t yyscanner);
	extern void yyerror(YYLTYPE* yylloc, yyscan_t scanner, const char* msg);
}


%token CLASS IDENTIFIER
%token PUBLIC STATIC
%token PRINT STRING_LITERAL

%start entry_point

%%

entry_point
	: CLASS IDENTIFIER '{' '}'
	| CLASS IDENTIFIER '{' function '}'
	;

function
	: function_header compound_statement
	;

function_header
	: PUBLIC STATIC data_type IDENTIFIER '(' data_type IDENTIFIER ')'
	;

data_type
	: IDENTIFIER
	| IDENTIFIER '['  ']'
	;

compound_statement
	: '{' statement '}'
	;

statement
	: PRINT STRING_LITERAL ';'
	;

%%


void yyerror(YYLTYPE* yylloc, yyscan_t scanner, const char* msg)
{
   std::cerr << "Error: " << msg << " at line: " << yylloc->last_line << ", column: " << yylloc->first_column  <<")\n";
}
