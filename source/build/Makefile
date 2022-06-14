all: build build-parser

build-parser:
	$(MAKE) -C ../src/mate/parser/

build:
	g++ -g -o mate \
		../src/mate/parser/mate.cc  \
		../src/mate/parser/MateLexer.l.cc  \
		../src/mate/parser/MateParser.y.cc
			
