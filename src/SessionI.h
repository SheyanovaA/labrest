#ifndef __SessionI_H__
#define __SessionI_H__

#include "LabrestAPI.h"
#include "UserManagerI.h"
#include "ResourceManagerI.h"

namespace LabrestAPI
{

class SessionI : public Session
{
public:

    SessionI(::std::string sessionId, ::std::string username);

    virtual ~SessionI();

    virtual void test(const Ice::Current&);

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
};

};

#endif /* __SessionI_H__ */
