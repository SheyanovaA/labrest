#ifndef CallbackManager_H
#define	CallbackManager_H

#include <Ice/Connection.h>

#include "LabrestAPI.h"
#include "CallbackThreadSrv.h"

namespace LabrestAPI
{
    
class CallbackManagerI : public CallbackManager
{
public:
    CallbackManagerI(LabrestAPI::User user);

    virtual bool registerCallback(const ::Ice::Identity&,
                                  const Ice::Current&);

    virtual bool unregisterCallback(const ::Ice::Identity&,
                                    const Ice::Current&);
    
private:
    ::LabrestAPI::User User;
    
    CallbackThreadSrv callbackThreadSrv;
};

};


#endif	/* CallbackManager_H */

