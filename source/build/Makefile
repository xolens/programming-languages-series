all: build

build-parser:
	$(MAKE) -C ../src/mate/parser/

build: build-parser
	g++ -g -o mate \
		../src/mate/mate.cc  \
		../src/mate/parser/MateLexer.l.cc  \
		../src/mate/parser/MateParser.y.cc \
		\
		../src/mate/ast/classifier/Executable.cc \
		../src/mate/ast/classifier/Modifiable.cc \
		../src/mate/ast/classifier/Classifier.cc \
		../src/mate/ast/classifier/Function.cc \
		../src/mate/ast/classifier/FunctionHeader.cc \
		../src/mate/ast/classifier/Property.cc \
		\
		../src/mate/executor/Context.cc \
		../src/mate/executor/ReferenceStack.cc \
		\
		../src/mate/ast/expression/Data.cc \
		../src/mate/ast/expression/ObjectType.cc \
		../src/mate/ast/expression/ArrayType.cc \
		../src/mate/ast/expression/Expression.cc \
		../src/mate/ast/expression/IdentifierExpression.cc \
		../src/mate/ast/expression/AssignmentExpression.cc \
		../src/mate/ast/expression/PrimaryExpression.cc \
		../src/mate/ast/expression/BinaryExpression.cc \
		../src/mate/ast/expression/UnaryExpression.cc \
		../src/mate/ast/expression/ConditionnalExpression.cc \
		../src/mate/ast/expression/DataTypeExpression.cc \
		../src/mate/ast/expression/NamespaceExpression.cc \
		../src/mate/ast/expression/InstanciationExpression.cc \
		\
		../src/mate/ast/statement/DeclarationStatement.cc \
		../src/mate/ast/statement/CompoundStatement.cc \
		../src/mate/ast/statement/PrintStatement.cc \
		../src/mate/ast/statement/ExpressionStatement.cc \
		../src/mate/ast/statement/Statement.cc 

 

			
