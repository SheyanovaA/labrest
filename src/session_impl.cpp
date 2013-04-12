#include <iostream>

#include "session_impl.h"

Session_I::~Session_I() {
    ::std::cout<<"session_impl::~session_impl() called"<<::std::endl;
}

void
Session_I::Test(const ::Ice::Current&) {
    ::std::cout<<"session_impl::test() called"<<::std::endl;
}
