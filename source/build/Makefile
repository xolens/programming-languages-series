all: build

build-parser:
	$(MAKE) -C ../src/mate/parser/

build: build-parser
	g++ -g -o mate \
		../src/mate/mate.cc  \
		../src/mate/parser/MateLexer.l.cc  \
		../src/mate/parser/MateParser.y.cc
			
