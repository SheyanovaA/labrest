#ifndef SessionI_H
#define SessionI_H

#include <iostream>
#include <Ice/Ice.h>
#include <IceUtil/Mutex.h>

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
    
    virtual void Refresh(const Ice::Current&);

    virtual void destroy(const Ice::Current&);
    
    IceUtil::Time timestamp() const;

private:

    ::std::string sessionId;
    
    ::LabrestAPI::User current_user;

    ::LabrestAPI::ResourceManagerPrx rsMgrPrx;

    bool hasRsMgrPrx;

    ::LabrestAPI::UserManagerPrx usMgrPrx;

    bool hasUsMgrPrx;
    
    ::LabrestAPI::CallbackManagerPrx cbMgrPrx;

    bool hasCbMgrPrx;
    
    IceUtil::Mutex lock; 

    IceUtil::Time _timestamp; // The last time the session was refreshed.
   
    bool _destroy;
};

typedef IceUtil::Handle<SessionI> SessionIPtr;

};

#endif /* SessionI_H */
