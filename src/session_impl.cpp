#include <iostream>

#include "session_impl.h"

session_impl::~session_impl() {
    ::std::cout<<"session_impl::~session_impl() called"<<::std::endl;
}

void
session_impl::test(const ::Ice::Current&) {
    ::std::cout<<"session_impl::test() called"<<::std::endl;
}
