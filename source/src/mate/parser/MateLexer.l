
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

	#include <cstring>
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

	char* replaceAll(char *orig, const char *rep, const char *with);

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

{L}({L}|{D})*				{ strcpy(yylval->_String, yytext); return(IDENTIFIER); }

\"(\\.|[^\\"\n])*\"		    { 
    yytext[strlen(yytext)-1]=0; 
    char* tmp = replaceAll(yytext, "\\a", "\a"); tmp = replaceAll(tmp, "\\b", "\b");
    tmp = replaceAll(tmp, "\\e", "\e"); tmp = replaceAll(tmp, "\\f", "\f"); 
    tmp = replaceAll(tmp, "\\n", "\n"); tmp = replaceAll(tmp, "\\r", "\r");
    tmp = replaceAll(tmp, "\\t", "\t"); tmp = replaceAll(tmp, "\\v", "\v");
    strcpy(yylval->_String, tmp+1); return(STRING_LITERAL);
}

"//"[^\n]* 					{ /* consume single line comment */ }

[ \t\v\n\f]					{ /* Ignore white spaces */ }

.							{ /* Add code to complain about unmatched characters */ }

%%

char* replaceAll(char *orig, const char *rep, const char *with){
    char *result, *ins, *tmp;
    int len_rep, len_with, len_front, count;

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = (char*) malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // tmp points to the end of the result string
    // ins points to the next occurrence of rep in orig
    // orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}