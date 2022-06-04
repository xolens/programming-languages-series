all: 
	flex MateLexer.l
	bison -t -v -d MateParser.y
	g++ -g -o mate mate.cc  MateLexer.l.cc MateParser.y.cc
			
