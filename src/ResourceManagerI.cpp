#include "ResourceManagerI.h"

::LabrestAPI::ResourceIdList
LabrestAPI::ResourceManagerI::getAllResourceIds(const Ice::Current& current) 
{
    ::std::cout << "ResourceManagerI::getAllResourceIds() called" << ::std::endl;
    
    return ::LabrestAPI::ResourceIdList();
}

::LabrestAPI::ResourceList
LabrestAPI::ResourceManagerI::getAllResources(const Ice::Current& current) 
{
    ::LabrestAPI::ResourceList resources;
    
    ::std::cout << "ResourceManagerI::getAllResources() called" << ::std::endl;
    
    resources = dbPtr->getAllResources();    
    
    return resources;
}

::LabrestAPI::Resource
LabrestAPI::ResourceManagerI::getResource(::Ice::Int resourceId,
                                          const Ice::Current& current) 
{
    ::LabrestAPI::Resource resource;
    
    ::std::cout << "ResourceManagerI::getResource() called" << ::std::endl;
    
    resource = dbPtr->getResource(resourceId);
    
    return resource;
}

::Ice::Int
LabrestAPI::ResourceManagerI::addResource(const ::std::string& name,
                                          const ::std::string& description,
                                          ::Ice::Int parentId,
                                          ::Ice::Int typeId,
                                          const Ice::Current& current)
{
    ::std::cout << "ResourceManagerI::addResource() called" << ::std::endl;

    int new_resource_id;
    
    new_resource_id = dbPtr->addResourse(name,description, typeId, parentId);
    
    return new_resource_id;
}

bool
LabrestAPI::ResourceManagerI::deleteResource(::Ice::Int resourceId,
                                             const Ice::Current& current)
{       
    bool status;
    
    ::std::cout << "ResourceManagerI::deleteResource() called" << ::std::endl;
    
    status = dbPtr->deleteResource(resourceId);
    
    return status;
}

bool
LabrestAPI::ResourceManagerI::modifyResource(::Ice::Int resourceId,
                                             const ::std::string& name,
                                             const ::std::string& description,
                                             ::Ice::Int parentId,
                                             ::Ice::Int typeId,
                                             const Ice::Current& current)
{
    bool status;
    
    ::std::cout << "ResourceManagerI::modifyResource() called" << ::std::endl;
    
    status = dbPtr->modifyResource(resourceId, name, description, typeId, parentId);
    
    return status;
}

bool
LabrestAPI::ResourceManagerI::lockResource(::Ice::Int resourceId,
                                           ::Ice::Int duration,
                                           const Ice::Current& current)
{   
    bool status;
    
    ::std::cout << "ResourceManagerI::lockResource() called" << ::std::endl;
    
    status = dbPtr->lockResourse(resourceId, User, duration);
    
    return status;
}

void
LabrestAPI::ResourceManagerI::unlockResource(::Ice::Int resourceId,
                                             const Ice::Current& current)
{
    ::std::cout << "ResourceManagerI::unlockResource() called" << ::std::endl;
    
    dbPtr->unlockResource(resourceId);
}

::LabrestAPI::ResourceTypeIdList
LabrestAPI::ResourceManagerI::getAllResourceTypeIds(const Ice::Current& current)
{
    ::std::cout << "ResourceManagerI::getAllResourceTypeIds() called" << ::std::endl;
    
    return ::LabrestAPI::ResourceTypeIdList();
}

::LabrestAPI::ResourceTypeList
LabrestAPI::ResourceManagerI::getAllResourceTypes(const Ice::Current& current)
{
     ::LabrestAPI::ResourceTypeList resource_types;
     
     ::std::cout << "ResourceManagerI::getAllResourceTypes() called" << ::std::endl;
    
    resource_types = dbPtr->getAllResourceTypes();
    
    return resource_types;
}

::LabrestAPI::ResourceType
LabrestAPI::ResourceManagerI::getResourceType(::Ice::Int resourceTypeId,
                                              const Ice::Current& current)
{
    ::LabrestAPI::ResourceType resource_type;
    
    ::std::cout << "ResourceManagerI::getResourceType() called" << ::std::endl;
    
    resource_type = dbPtr->getResourceType(resourceTypeId);
    
    return resource_type;
}

::Ice::Int
LabrestAPI::ResourceManagerI::addResourceType(const ::std::string& name,
                                              const ::std::string& description,
                                              ::Ice::Int parentId,
                                              const Ice::Current& current)
{
    int new_resource_type_id;
    
    ::std::cout << "ResourceManagerI::addResourceType() called" << ::std::endl;
    
    new_resource_type_id =   dbPtr->addResourceType(name, description, parentId);
    
    return new_resource_type_id;
}

bool
LabrestAPI::ResourceManagerI::deleteResourceType(::Ice::Int resourceTypeId,
                                                 const Ice::Current& current)
{
    bool status;
    
    ::std::cout << "ResourceManagerI::deleteResourceType() called" << ::std::endl;
    
    status = dbPtr->deleteResourceType(resourceTypeId);
    
    return status;
}

bool
LabrestAPI::ResourceManagerI::modifyResourceType(::Ice::Int resourceTypeId,
                                                 const ::std::string& name,
                                                 const ::std::string& description,
                                                 ::Ice::Int parentId,
                                                 const Ice::Current& current)
{
    bool status;
    
    ::std::cout << "ResourceManagerI::modifyResourceType() called" << ::std::endl;
    
    status = dbPtr->modifyResourceType(resourceTypeId, name, description, parentId);
    
    return status;
}

::LabrestAPI::ResourceManagerI::ResourceManagerI(::std::string user)
{
    User = user;
}

::LabrestAPI::History 
LabrestAPI::ResourceManagerI::getLockHistory(const Ice::Current&)
{
    ::std::cout << "ResourceManagerI::getLockHistory() called" << ::std::endl;
    
    ::LabrestAPI::History history;
    
    history = dbPtr->getLockHistry();
    
    return history;   
}
