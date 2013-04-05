#include <iostream>

#include "session_impl.h"

void
session_impl::test(const ::Ice::Current&) {
    ::std::cout<<"session_impl::test() called"<<::std::endl;
}
