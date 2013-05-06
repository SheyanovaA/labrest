#include "UserI.h"

::std::string
LabrestAPI::UserI::getUserName(const Ice::Current& current)
{
    ::std::cout << "UserI::getUserName()\n";
    
    return this->name;
}



/*void 
LabrestAPI::UserI::setName(::std::string username)
{
    this->name = username;
}
    
void 
LabrestAPI::UserI::setAuth(::std::string authdata)
{
    this->auth = authdata;
}*/