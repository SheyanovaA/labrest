#include <iostream>

#include "SessionI.h"

SessionI::~SessionI() {
    ::std::cout<<"SessionI::~SessionI() called"<<::std::endl;
}

void
SessionI::test(const ::Ice::Current&) {
    ::std::cout<<"SessionI::test() called"<<::std::endl;
}
