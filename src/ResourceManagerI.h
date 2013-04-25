#ifndef __ResourceManagerI_H__
#define __ResourceManagerI_H__

#include <string.h>

#include "LabrestAPI.h"
#include "ResourceI.h"
#include "ResourceTypeI.h"
#include "LabrestDB.h"

namespace LabrestAPI
{

class ResourceManagerI : virtual public ResourceManager
{
public:

    virtual ::LabrestAPI::ResourceIdList getAllResourceIds(const Ice::Current&);

    virtual ::LabrestAPI::ResourceList getAllResources(const Ice::Current&);

    virtual ::LabrestAPI::ResourcePtr getResource(::Ice::Int,
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

    virtual ::LabrestAPI::ResourceTypePtr getResourceType(::Ice::Int,
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
};

};

#endif /* __ResourceManagerI_H__ */


