#ifndef SessionI_H
#define SessionI_H

#include <iostream>
#include <Ice/Ice.h>

#include "LabrestAPI.h"
#include "UserManagerI.h"
#include "ResourceManagerI.h"
#include "CallbackManagerI.h"

namespace LabrestAPI
{

class SessionI : public Session
{
public:

    SessionI(::std::string sessionId, ::std::string username);

    virtual ~SessionI();

    virtual ::LabrestAPI::ResourceManagerPrx getResourceManager(const Ice::Current&);

    virtual ::LabrestAPI::UserManagerPrx getUserManager(const Ice::Current&);

    virtual ::LabrestAPI::CallbackManagerPrx getCallbackManager(const Ice::Current&);

private:

    ::std::string sessionId;
    
    ::LabrestAPI::User current_user;

    ::LabrestAPI::ResourceManagerPrx rsMgrPrx;

    bool hasRsMgrPrx;

    ::LabrestAPI::UserManagerPrx usMgrPrx;

    bool hasUsMgrPrx;
    
    ::LabrestAPI::CallbackManagerPrx cbMgrPrx;

    bool hasCbMgrPrx;
    
};

};

#endif /* SessionI_H */
