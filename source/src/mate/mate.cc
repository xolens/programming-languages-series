#include <iostream>
#include "./mate.hh"
#include "./parser/MateLexer.l.hh"


int main(int argc, char* argv[]){

    if(argc < 2) {
        std::cout << "Usage: "<< argv[0] << " fileName\n";
        return -1;
    }

    yyscan_t scanner;
    FILE *input = fopen(argv[1], "r");

	yylex_init(&scanner);
	yyset_in(input, scanner);

    yyparse(scanner);
	yylex_destroy(scanner);
    std::cout << "Done..\n";

    return 0;
}