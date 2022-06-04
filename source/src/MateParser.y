%defines "MateParser.y.hh"
%output "MateParser.y.cc"
%verbose
%define api.pure full
%locations
%define parse.error verbose
%param {yyscan_t  scanner}

%code requires{

	#include <iostream>
	#include "mate.hh"
}


%code provides
{
	extern int yylex(YYSTYPE * yylval_param, YYLTYPE * yylloc_param , yyscan_t yyscanner);
	extern void yyerror(YYLTYPE* yylloc, yyscan_t scanner, const char* msg);
}


%token CLASS IDENTIFIER

%start entry_point

%%

entry_point
	: CLASS IDENTIFIER '{' '}'
	;

%%


void yyerror(YYLTYPE* yylloc, yyscan_t scanner, const char* msg)
{
   std::cerr << "Error: " << msg << " at line: " << yylloc->last_line << ", column: " << yylloc->first_column  <<")\n";
}
