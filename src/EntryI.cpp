#include <iostream>
#include <string>
#include <Ice/Ice.h>

#include "LabrestAPI.h"
#include "EntryI.h"
#include "SessionI.h"

::LabrestAPI::EntryI::EntryI()
{
    index = 0;
}

::LabrestAPI::SessionPrx
LabrestAPI::EntryI::login(const ::std::string& username, const ::std::string& auth, const ::Ice::Current& current) 
{
    if (!dbPtr->existsUser(username, auth))
    {
        LoginException le;
        le.ice_throw();
    }

    ::std::string sessionId = "SimpleSession" + index++;

    ::std::cout<<"EntryI::login() called"<<::std::endl;

    Ice::ObjectPtr object = new ::LabrestAPI::SessionI(sessionId, username);

    ::LabrestAPI::SessionPrx SessionProxy = ::LabrestAPI::SessionPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId)));

    return SessionProxy;
}
