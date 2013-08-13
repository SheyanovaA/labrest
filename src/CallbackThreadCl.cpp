#include "CallbackThreadCl.h"

LabrestAPI::CallbackThreadCl::CallbackThreadCl(Ice::CommunicatorPtr ic) : IC(ic)
{
    ::std::cout << "CallbackThreadCl::CallbackThreadCl() called" << ::std::endl;
}

void 
LabrestAPI::CallbackThreadCl::run()
{
    std::cout << "CallbackThreadCl::run() called" << std::endl;
    
    IC->waitForShutdown();
}