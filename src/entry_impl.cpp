#include <iostream>
#include <string>
#include <Ice/Ice.h>

#include "labrestapi.h"
#include "entry_impl.h"
#include "session_impl.h"

Entry_I::Entry_I() {
    index = 0;
}

::LabrestAPI::SessionPrx
Entry_I::Login(const ::std::string& username, const ::std::string& auth, const ::Ice::Current& current) {

    ::std::string SessionId = "SimpleSession" + index++;

    ::std::cout<<"entry_impl::login() called"<<::std::endl;

    Ice::ObjectPtr object = new Session_I;

    ::LabrestAPI::SessionPrx SessionProxy = ::LabrestAPI::SessionPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(SessionId)));

    return SessionProxy;
}
