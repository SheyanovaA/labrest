#include "entry_impl.h"
#include "session_impl.h"

::labrestapi::sessionPtr
entry_impl::login(const ::std::string&, const ::std::string&, const ::Ice::Current&) {

    session_impl s;
    return &s;

}
