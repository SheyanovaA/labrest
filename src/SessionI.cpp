#include <iostream>

#include "SessionI.h"

LabrestAPI::SessionI::~SessionI()
{
    ::std::cout<<"SessionI::~SessionI() called"<<::std::endl;
}

void
LabrestAPI::SessionI::test(const ::Ice::Current&)
{
    ::std::cout<<"SessionI::test() called"<<::std::endl;
}

::LabrestAPI::ResourceManagerPrx
LabrestAPI::SessionI::getResourceManager(const Ice::Current& current)
{
    return 0;
}

::LabrestAPI::UserManagerPrx
LabrestAPI::SessionI::getUserManager(const Ice::Current& current)
{
    return 0;
}
