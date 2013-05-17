#ifndef __ResourceManagerI_H__
#define __ResourceManagerI_H__

#include <string.h>

#include "LabrestAPI.h"
#include "LabrestDB.h"

namespace LabrestAPI
{

class ResourceManagerI : virtual public ResourceManager
{
    ::std::string User;
public:
    
    ResourceManagerI(::std::string user);

    virtual ::LabrestAPI::ResourceIdList getAllResourceIds(const Ice::Current&);

    virtual ::LabrestAPI::ResourceList getAllResources(const Ice::Current&);

    virtual ::LabrestAPI::Resource getResource(::Ice::Int,
                                                  const Ice::Current&);

    virtual ::Ice::Int addResource(const ::std::string&,
                                   const ::std::string&,
                                   ::Ice::Int,
                                   ::Ice::Int,
                                   const Ice::Current&);

    virtual bool deleteResource(::Ice::Int,
                                const Ice::Current&);

    virtual bool modifyResource(::Ice::Int,
                                const ::std::string&,
                                const ::std::string&,
                                ::Ice::Int,
                                ::Ice::Int,
                                const Ice::Current&);

    virtual bool lockResource(::Ice::Int,
                              const Ice::Current&);

    virtual void unlockResource(::Ice::Int,
                                const Ice::Current&);

    virtual ::LabrestAPI::ResourceTypeIdList getAllResourceTypeIds(const Ice::Current&);

    virtual ::LabrestAPI::ResourceTypeList getAllResourceTypes(const Ice::Current&);

    virtual ::LabrestAPI::ResourceType getResourceType(::Ice::Int,
                                                          const Ice::Current&);

    virtual ::Ice::Int addResourceType(const ::std::string&,
                                       const ::std::string&,
                                       ::Ice::Int,
                                       const Ice::Current&);

    virtual bool deleteResourceType(::Ice::Int,
                                    const Ice::Current&);

    virtual bool modifyResourceType(::Ice::Int,
                                    const ::std::string&,
                                    const ::std::string&,
                                    ::Ice::Int,
                                    const Ice::Current&);
    
    virtual ::LabrestAPI::History getLockHistory(const Ice::Current&);
};

};

#endif /* __ResourceManagerI_H__ */


