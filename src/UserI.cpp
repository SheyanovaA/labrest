#include "UserI.h"

::std::string
LabrestAPI::UserI::getUserName(const Ice::Current& current)
{
    return this->name;
}

