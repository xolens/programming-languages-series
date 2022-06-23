#include "Context.hh"

mate::executor::Context::~Context(){}

mate::executor::Context::Context(){
    this->_refStack = new mate::executor::ReferenceStack();
}

mate::executor::ReferenceStack* mate::executor::Context::stack(){
    return _refStack;
}

std::string mate::executor::Context::putData(std::string identifier, mate::ast::expression::Data* val){
    return putData(_refStack, identifier, val);
}

std::string mate::executor::Context::putData(mate::executor::ReferenceStack* refStack, std::string identifier, mate::ast::expression::Data* val){
    std::string key = mate::util::UUID::generate();
    refStack->put(identifier, key);
    _refObjectMap.insert(std::pair<std::string, mate::ast::expression::Data*>(key, val));
    return key;
}

bool mate::executor::Context::updateByRef(std::string ref, mate::ast::expression::Data* val){
    std::map<std::string, mate::ast::expression::Data*>::iterator itr;
    itr = _refObjectMap.find(ref);

      if (itr != _refObjectMap.end()){
        itr->second = val;
        return true;
      }
    return false;
}

void mate::executor::Context::putByRef(std::string ref, mate::ast::expression::Data* val){
    _refObjectMap.insert(std::pair<std::string, mate::ast::expression::Data*>(ref, val));
}

mate::ast::expression::Data* mate::executor::Context::getDataByIdentifier(std::string identifier){
    // then checking if it is a variable available in the current context
    if(_refStack!= NULL && _refStack->hasIdentifier(identifier)){
        return this->getDataByRef(_refStack->get(identifier));
    }
    return NULL;
}

mate::ast::expression::Data* mate::executor::Context::getDataByRef(std::string ref){
    std::map<std::string, mate::ast::expression::Data*>::iterator it = _refObjectMap.find(ref);
    if(it != _refObjectMap.end()){
        return it->second;
    }
    return NULL;
}

mate::executor::ReferenceStack* mate::executor::Context::createStack(bool parentLookup){
    return new mate::executor::ReferenceStack(this->_refStack, parentLookup);
}

void mate::executor::Context::updateStack(mate::executor::ReferenceStack* refStack){
    this->_refStack = refStack;
}

mate::executor::ReferenceStack* mate::executor::Context::popStack(){
    mate::executor::ReferenceStack* stack = this->_refStack;
    this->_refStack = this->_refStack->parent();
    return stack;
}

bool mate::executor::Context::hasIdentifier(std::string identifier){
    return this->_refStack->hasIdentifier(identifier);
}

std::string mate::executor::Context::getIdentifierRef(std::string identifier){
    return this->_refStack->get(identifier);
}