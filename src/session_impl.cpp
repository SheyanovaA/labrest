#include <iostream>

#include "session_impl.h"

void
session_impl::test(const ::Ice::Current&) {
    ::std::cout<<":)"<<::std::endl;
}
