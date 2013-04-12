#include <iostream>
#include <string>
#include <Ice/Ice.h>

#include "LabrestAPI.h"
#include "EntryI.h"
#include "SessionI.h"

EntryI::EntryI() {
    index = 0;
}

::LabrestAPI::SessionPrx
EntryI::login(const ::std::string& username, const ::std::string& auth, const ::Ice::Current& current) {

    ::std::string SessionId = "SimpleSession" + index++;

    ::std::cout<<"EntryI::login() called"<<::std::endl;

    Ice::ObjectPtr object = new SessionI;

    ::LabrestAPI::SessionPrx SessionProxy = ::LabrestAPI::SessionPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(SessionId)));

    return SessionProxy;
}
