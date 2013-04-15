#ifndef __ResourceTypeI_H__
#define __ResourceTypeI_H__

#include "LabrestAPI.h"

namespace LabrestAPI 
{

class ResourceTypeI : virtual public ResourceType 
{
public:

    virtual ::Ice::Int getId(const Ice::Current&);

    virtual ::std::string getName(const Ice::Current&);

    virtual ::std::string getDescription(const Ice::Current&);

    virtual ::LabrestAPI::ResourceTypePtr getParent(const Ice::Current&);
};

};
#endif /* __ResourceTypeI_H__ */
