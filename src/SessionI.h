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

    virtual ~SessionI();

    virtual void test(const Ice::Current&);

    virtual ::LabrestAPI::ResourceManagerPrx getResourceManager(const Ice::Current&);

    virtual ::LabrestAPI::UserManagerPrx getUserManager(const Ice::Current&);
};

};

#endif /* __SessionI_H__ */
