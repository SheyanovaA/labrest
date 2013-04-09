#include <iostream>
#include <string>
#include <Ice/Ice.h>

#include "labrestapi.h"
#include "entry_impl.h"
#include "session_impl.h"

entry_impl::entry_impl() {
    index = 0;
}

::labrestapi::sessionPrx
entry_impl::login(const ::std::string& username, const ::std::string& auth, const ::Ice::Current& current) {

    ::std::string sessionId = "SimpleSession" + index++;

    ::std::cout<<"entry_impl::login() called"<<::std::endl;

    Ice::ObjectPtr object = new session_impl;

    ::labrestapi::sessionPrx sessionProxy = ::labrestapi::sessionPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId)));

    return sessionProxy;
}
