#include <iostream>
#include <Ice/Ice.h>

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

    ::std::cout<<"SessionI::getResourceManager() called"<<::std::endl;

    Ice::ObjectPtr object = new ::LabrestAPI::ResourceManagerI;

    ::LabrestAPI::ResourceManagerPrx ResManagerProxy = ::LabrestAPI::ResourceManagerPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity("1")));

    return ResManagerProxy;

    return 0;
}

::LabrestAPI::UserManagerPrx
LabrestAPI::SessionI::getUserManager(const Ice::Current& current)
{
    return 0;
}
