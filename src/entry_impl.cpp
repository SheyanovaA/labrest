#include <iostream>
#include <Ice/Ice.h>

#include "labrestapi.h"
#include "entry_impl.h"
#include "session_impl.h"

::labrestapi::sessionPrx
entry_impl::login(const ::std::string& username, const ::std::string& auth, const ::Ice::Current& current) {

    ::std::cout<<"entry_impl::login() called"<<::std::endl;

    Ice::ObjectPtr object = new session_impl;

    ::labrestapi::sessionPrx sessionProxy = ::labrestapi::sessionPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity("SimpleSession")));

    return sessionProxy;
}
