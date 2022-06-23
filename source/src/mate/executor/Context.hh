#pragma once
#include <string>
#include <map>
#include <iterator>
#include "ReferenceStack.hh"
#include "./../ast/expression/Data.hh"
#include "./../util/uuid/UUID.hh"

namespace mate::executor {

class Context{

private:
    mate::executor::ReferenceStack* _refStack;
    std::map<std::string, mate::ast::expression::Data*> _refObjectMap;

public:
	Context();
	~Context();


    std::string putData(mate::executor::ReferenceStack* refStack, std::string identifier, mate::ast::expression::Data* val);
    std::string putData(std::string identifier, mate::ast::expression::Data* val);
    bool updateByRef(std::string identifier, mate::ast::expression::Data* val);
    void putByRef(std::string identifier, mate::ast::expression::Data* val);
    mate::ast::expression::Data* getDataByIdentifier(std::string identifier);
    mate::ast::expression::Data* getDataByRef(std::string ref);
    mate::executor::ReferenceStack* stack();
    mate::executor::ReferenceStack* createStack(bool parentLookup);
    void updateStack(mate::executor::ReferenceStack* refStack);
    mate::executor::ReferenceStack* popStack();
    bool hasIdentifier(std::string identifier);
    std::string getIdentifierRef(std::string identifier);

};

} /* end namespace mate::executor::package */
