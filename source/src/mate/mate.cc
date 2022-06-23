#include <iostream>
#include "./mate.hh"
#include "./parser/MateLexer.l.hh"
#include "./ast/classifier/Classifier.hh"
#include "./executor/Context.hh"


int main(int argc, char* argv[]){

    if(argc < 2) {
        std::cout << "Usage: "<< argv[0] << " fileName\n";
        return -1;
    }

    yyscan_t scanner;
    FILE *input = fopen(argv[1], "r");
    mate::ast::classifier::Classifier* _class = new mate::ast::classifier::Classifier();

	yylex_init_extra(_class, &scanner);
	yyset_in(input, scanner);

    yyparse(scanner, _class);
	yylex_destroy(scanner);

    std::cout << "[mate]---\n";
    mate::executor::Context* context = new mate::executor::Context();
    _class->execute(context);
    std::cout << "---------\n";

    return 0;
}