#include "SessionI.h"

LabrestAPI::SessionI::SessionI(::std::string sessionId, ::std::string username) : Session() 
{
    current_user = dbPtr->getUser(username);
    
    this->sessionId = sessionId;

    this->hasRsMgrPrx = false;

    this->hasUsMgrPrx = false;
    
    this->hasCbMgrPrx = false;
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

    if(!hasRsMgrPrx) 
    {
        Ice::ObjectPtr object = new ::LabrestAPI::ResourceManagerI(current_user);

        rsMgrPrx = ::LabrestAPI::ResourceManagerPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId + "-ResourceManager")));

        hasRsMgrPrx = true;
    }

    return rsMgrPrx;
}

::LabrestAPI::UserManagerPrx
LabrestAPI::SessionI::getUserManager(const Ice::Current& current)
{

    ::std::cout<<"SessionI::getUserManager() called"<<::std::endl;

    if(!hasUsMgrPrx) 
    {
        Ice::ObjectPtr object = new ::LabrestAPI::UserManagerI(current_user);

        usMgrPrx = ::LabrestAPI::UserManagerPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId + "-UserManager")));

        hasUsMgrPrx = true;
    }

    return usMgrPrx;
}

::LabrestAPI::CallbackManagerPrx
LabrestAPI::SessionI::getCallbackManager(const Ice::Current& current)
{
    ::std::cout<<"SessionI::getCallbackManager() called"<<::std::endl;

    if(!hasCbMgrPrx) 
    {
        Ice::ObjectPtr object = new ::LabrestAPI::CallbackManagerI(current_user);
        
        cbMgrPrx = ::LabrestAPI::CallbackManagerPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId + "-CallBackManager")));

        hasCbMgrPrx = true;
    }

    return cbMgrPrx;
}
