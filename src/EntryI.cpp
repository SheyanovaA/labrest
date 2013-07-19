#include "EntryI.h"


::LabrestAPI::EntryI::EntryI(const ReapTaskPtr& reapTask) :
    _reaper(reapTask), 
    index(0)
{
}

::LabrestAPI::SessionPrx
LabrestAPI::EntryI::login(const ::std::string& username, const ::std::string& auth, const ::Ice::Current& current) 
{
    if (!dbPtr->authUser(username, auth))
    {
        LoginException le;
        le.ice_throw();
    }
    
    ::std::string sessionId = "SimpleSession" + index++;

    ::std::cout<<"EntryI::login() called"<<::std::endl;

    ::LabrestAPI::SessionIPtr object = new ::LabrestAPI::SessionI(sessionId, username);

    ::LabrestAPI::SessionPrx SessionProxy = ::LabrestAPI::SessionPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId)));

    _reaper->add(SessionProxy, object);
    
    return SessionProxy;
}
