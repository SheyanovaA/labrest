#include "CallbackManagerI.h"

bool
LabrestAPI::CallbackManagerI::registerCallback(const ::Ice::Identity& ident,
                                               const Ice::Current& current)
{
    ::std::cout << "CallbackManagerI::registerCallback() called" << ::std::endl;
    
    LabrestAPI::CallbackPrx client = LabrestAPI::CallbackPrx::uncheckedCast(current.con->createProxy(ident));
   
    std::string username = User.name;
    
    CbThreadPtr->addCallback(client, username);
    
    return true;
}

bool
LabrestAPI::CallbackManagerI::unregisterCallback(const ::Ice::Identity& ident,
                                                 const Ice::Current& current)
{
    ::std::cout << "CallbackManagerI::unregisterCallback() called" << ::std::endl;
    
    LabrestAPI::CallbackPrx client = LabrestAPI::CallbackPrx::uncheckedCast(current.con->createProxy(ident));  
    
    CbThreadPtr->removeCallback(client);
    
    return true;
}

LabrestAPI::CallbackManagerI::CallbackManagerI(LabrestAPI::User user)
{
    ::std::cout << "CallbackManagerI::CallbackManagerI() called" << ::std::endl;
    
    User = user;
}