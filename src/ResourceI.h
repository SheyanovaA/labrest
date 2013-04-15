#ifndef __ResourceI_H__
#define __ResourceI_H__

#include "LabrestAPI.h"

namespace LabrestAPI 
{

class ResourceI : virtual public Resource 
{
public:

    virtual ::Ice::Int getId(const Ice::Current&);

    virtual ::std::string getName(const Ice::Current&);

    virtual ::std::string getDescription(const Ice::Current&);

    virtual bool getLockStatus(const Ice::Current&);

    virtual ::LabrestAPI::ResourcePtr getParent(const Ice::Current&);

    virtual ::LabrestAPI::ResourceTypePtr getType(const Ice::Current&);
};

};

#endif /* __ResourceI_H__ */ 
