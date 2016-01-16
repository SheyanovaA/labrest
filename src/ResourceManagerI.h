#ifndef ResourceManagerI_H
#define ResourceManagerI_H

#include <string.h>

#include "LabrestAPI.h"
#include "LabrestDB.h"
#include "EventsQueue.h"
#include "ResourceFinder.h"

namespace LabrestAPI
{

class ResourceManagerI : virtual public ResourceManager
{
    ::LabrestAPI::User User;
public:
    
    ResourceManagerI(::LabrestAPI::User user);

    virtual ::LabrestAPI::IntList getAllResourceIds(const Ice::Current&);

    virtual ::LabrestAPI::ResourceList getAllResources(const Ice::Current&);

    virtual ::LabrestAPI::Resource getResource(::Ice::Int,
                                                  const Ice::Current&);

     virtual ::Ice::Int addResource(const ::std::string&,
                                   const ::std::string&,
                                   ::Ice::Int,
                                   const ::LabrestAPI::ResourceType&,
                                   const Ice::Current&);

    virtual bool deleteResource(::Ice::Int,
                                const Ice::Current&);

    virtual bool modifyResource(::Ice::Int,
                                const ::std::string&,
                                const ::std::string&,
                                ::Ice::Int,
                                const ::LabrestAPI::ResourceType&,
                                const Ice::Current&);

    virtual bool lockResource(::Ice::Int,
                              ::Ice::Int,
                              const Ice::Current&);

    virtual void connectResources(::Ice::Int,
                                     ::Ice::Int,
                                     const Ice::Current&);

    virtual void disconnectResources(::Ice::Int,
                                        ::Ice::Int,
                                        const Ice::Current&);

    virtual bool isConnectedResources(::Ice::Int,
                                         ::Ice::Int,
                                         const Ice::Current&);

    virtual ::LabrestAPI::LinkList getAllConnections(const Ice::Current&);


    virtual ::LabrestAPI::ResourceList findResource(::Ice::Int,
                                                        const Ice::Current&);

    virtual ::LabrestAPI::Resource findBestResource(::Ice::Int,
                                                        const Ice::Current&);

    virtual ::LabrestAPI::SequenceVariants findResources(const ::LabrestAPI::IntList&,
                                                             const Ice::Current&);

    virtual ::LabrestAPI::ResourceList findBestResources(const ::LabrestAPI::IntList&,
                                                             const Ice::Current&);

    virtual void unlockResource(::Ice::Int,
                                const Ice::Current&);

    virtual ::LabrestAPI::IntList getAllResourceTypeIds(const Ice::Current&);

    virtual ::LabrestAPI::ResourceTypeList getAllResourceTypes(const Ice::Current&);

    virtual ::LabrestAPI::ResourceType getResourceType(::Ice::Int,
                                                          const Ice::Current&);

    virtual ::Ice::Int addResourceType(const ::std::string&,
                                       const ::std::string&,
                                       ::Ice::Int,
                                       ::Ice::Int,
                                       const Ice::Current&);

    virtual bool deleteResourceType(::Ice::Int,
                                    const Ice::Current&);

    virtual bool modifyResourceType(::Ice::Int,
                                    const ::std::string&,
                                    const ::std::string&,
                                    ::Ice::Int,
                                    ::Ice::Int,
                                    const Ice::Current&);
    
    virtual ::LabrestAPI::History getLockHistory(const Ice::Current&);
};

};

#endif /* ResourceManagerI_H */


