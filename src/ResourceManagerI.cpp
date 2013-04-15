#include "ResourceManagerI.h"

::LabrestAPI::ResourceIdList
LabrestAPI::ResourceManagerI::getAllResourceIds(const Ice::Current& current) 
{
    return ::LabrestAPI::ResourceIdList();
}

::LabrestAPI::ResourceList
LabrestAPI::ResourceManagerI::getAllResources(const Ice::Current& current) 
{
    return ::LabrestAPI::ResourceList();
}

::LabrestAPI::ResourcePtr
LabrestAPI::ResourceManagerI::getResource(::Ice::Int resourceId,
                                          const Ice::Current& current) 
{
    return 0;
}

::Ice::Int
LabrestAPI::ResourceManagerI::addResource(const ::std::string& name,
                                          const ::std::string& description,
                                          ::Ice::Int parentId,
                                          ::Ice::Int typeId,
                                          const Ice::Current& current)
{
    return 0;
}

bool
LabrestAPI::ResourceManagerI::deleteResource(::Ice::Int resourceId,
                                             const Ice::Current& current)
{
    return false;
}

bool
LabrestAPI::ResourceManagerI::modifyResource(::Ice::Int resourceId,
                                             const ::std::string& name,
                                             const ::std::string& description,
                                             ::Ice::Int parentId,
                                             ::Ice::Int typeId,
                                             const Ice::Current& current)
{
    return false;
}

bool
LabrestAPI::ResourceManagerI::lockResource(::Ice::Int resourceId,
                                           const Ice::Current& current)
{
    return false;
}

void
LabrestAPI::ResourceManagerI::unlockResource(::Ice::Int resourceId,
                                             const Ice::Current& current)
{
}

::LabrestAPI::ResourceTypeIdList
LabrestAPI::ResourceManagerI::getAllResourceTypeIds(const Ice::Current& current)
{
    return ::LabrestAPI::ResourceTypeIdList();
}

::LabrestAPI::ResourceTypeList
LabrestAPI::ResourceManagerI::getAllResourceTypes(const Ice::Current& current)
{
    return ::LabrestAPI::ResourceTypeList();
}

::LabrestAPI::ResourceTypePtr
LabrestAPI::ResourceManagerI::getResourceType(::Ice::Int resourceTypeId,
                                              const Ice::Current& current)
{
    return 0;
}

::Ice::Int
LabrestAPI::ResourceManagerI::addResourceType(const ::std::string& name,
                                              const ::std::string& description,
                                              ::Ice::Int parentId,
                                              const Ice::Current& current)
{
    return 0;
}

bool
LabrestAPI::ResourceManagerI::deleteResourceType(::Ice::Int resourceTypeId,
                                                 const Ice::Current& current)
{
    return false;
}

bool
LabrestAPI::ResourceManagerI::modifyResourceType(::Ice::Int resourceTypeId,
                                                 const ::std::string& name,
                                                 const ::std::string& description,
                                                 ::Ice::Int parentId,
                                                 const Ice::Current& current)
{
    return false;
}
