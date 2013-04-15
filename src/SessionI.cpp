#include <iostream>
#include <Ice/Ice.h>

#include "SessionI.h"

LabrestAPI::SessionI::SessionI(::std::string sessionId) : Session() {
    this->sessionId = sessionId;
    this->hasRsMgrPrx = false;
}

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

    if(!hasRsMgrPrx) {
        Ice::ObjectPtr object = new ::LabrestAPI::ResourceManagerI;
        rsMgrPrx = ::LabrestAPI::ResourceManagerPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId + "-ResourceManager")));
        hasRsMgrPrx = true;
    }

    return rsMgrPrx;
}

::LabrestAPI::UserManagerPrx
LabrestAPI::SessionI::getUserManager(const Ice::Current& current)
{
    return 0;
}
