#pragma once

#include <map>
#include <string>
#include <iostream>

namespace mate::executor {

class ReferenceStack{

private:
    std::map<std::string, std::string> _references;
    mate::executor::ReferenceStack* _parent;
    bool parentLookup;

public:
   ReferenceStack();
   ReferenceStack(mate::executor::ReferenceStack* parent, bool parentLookup);
   ~ReferenceStack();

    void put(std::string identifier, std::string ref);
    mate::executor::ReferenceStack* parent();
    std::string get(std::string identifier);
    bool hasIdentifier(std::string identifier);

};

} /* end namespace mate::executor */
