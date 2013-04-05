#include <iostream>

#include "entry_impl.h"
#include "session_impl.h"

::labrestapi::sessionPrx
entry_impl::login(const ::std::string&, const ::std::string&, const ::Ice::Current&) {

    ::std::cout<<"entry_impl::login() called"<<::std::endl;

      //session_impl s;
      //return &s;
    return 0;

}
