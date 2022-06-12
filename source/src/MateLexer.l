
%option header-file = "MateLexer.l.hh"
%option outfile = "MateLexer.l.cc"
%option reentrant
%option noyywrap
%option stack
%option warn nodefault
%option bison-bridge bison-locations
%option yylineno
%option always-interactive nounistd

%top{

	// for Visual C++ compatibility
	#define YY_NO_UINSTD_H
	#pragma warning(disable: 4005)

	#include "MateParser.y.hh"

	#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

	#define YY_RESET_ERROR_COLUMN_NO yylloc->first_column = yylloc->last_column = 0; 

}

D			[0-9]
L			[a-zA-Z_]

%%

"print"						{ return(PRINT);}

"class"						{ return(CLASS);}

"public"					{ return(PUBLIC);}

"static"					{ return(STATIC);}

"{"							{ return('{'); }

"}"							{ return('}'); }

"["							{ return('['); }

"]"							{ return(']'); }

"("							{ return('('); }

")"							{ return(')'); }

";"							{ return(';'); }

{L}({L}|{D})*				{ return(IDENTIFIER); }

L?\"(\\.|[^\\"\n])*\"		{ return(STRING_LITERAL); }

"//"[^\n]* 					{ /* consume single line comment */ }

[ \t\v\n\f]					{ /* Ignore white spaces */ }

.							{ /* Add code to complain about unmatched characters */ }

%%
