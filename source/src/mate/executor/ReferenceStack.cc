#include "ReferenceStack.hh"


mate::executor::ReferenceStack::ReferenceStack(){
    this->_parent = NULL;
    this->parentLookup = false;
}

mate::executor::ReferenceStack::ReferenceStack(mate::executor::ReferenceStack* parent, bool parentLookup){
    this->_parent = parent;
    this->parentLookup = parentLookup;
}

mate::executor::ReferenceStack::~ReferenceStack(){}


void mate::executor::ReferenceStack::put(std::string identifier, std::string ref){
    _references.insert(std::pair<std::string, std::string>(identifier, ref));
}

std::string mate::executor::ReferenceStack::get(std::string identifier){
    std::map<std::string, std::string>::iterator it = _references.find(identifier);
    if(it != _references.end()){
        return it->second;
    }
    return "";
}

bool mate::executor::ReferenceStack::hasIdentifier(std::string identifier){
    std::map<std::string, std::string>::iterator it = _references.find(identifier);
    return it != _references.end();
}

mate::executor::ReferenceStack* mate::executor::ReferenceStack::parent(){
    return this->_parent;
}