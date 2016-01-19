#include "ResourceManagerI.h"

::LabrestAPI::IntList
LabrestAPI::ResourceManagerI::getAllResourceIds(const Ice::Current& current) 
{
    ::std::cout << "ResourceManagerI::getAllResourceIds() called" << ::std::endl;
    
    return ::LabrestAPI::IntList();
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
                                          const ::LabrestAPI::ResourceType& type,
                                          const Ice::Current& current)
{
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    
    ::std::cout << "ResourceManagerI::addResource() called" << ::std::endl;

    int new_resource_id;
    
    new_resource_id = dbPtr->addResourse(name,description, type.id, parentId);
    
    Event ev;
    
    ev.TypeEvent = CB_ADD_RES;
    ev.id = EvQueuePtr->next_id;
    ev.resourceId = new_resource_id;
    ev.userDest = "";
    ev.userSrc = User.name;
    
    EvQueuePtr->push_back(ev);
    
    return new_resource_id;
}

bool
LabrestAPI::ResourceManagerI::deleteResource(::Ice::Int resourceId,
                                             const Ice::Current& current)
{       
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    
    bool status;
    
    ::std::cout << "ResourceManagerI::deleteResource() called" << ::std::endl;
    
    status = dbPtr->deleteResource(resourceId);
    
    Event ev;
    
    ev.TypeEvent = CB_DEL_RES;
    ev.id = EvQueuePtr->next_id;
    ev.resourceId = resourceId;
    ev.userDest = "";
    ev.userSrc = User.name;
    
    EvQueuePtr->push_back(ev);
    
    return status;
}

bool
LabrestAPI::ResourceManagerI::modifyResource(::Ice::Int resourceId,
                                             const ::std::string& name,
                                             const ::std::string& description,
                                             ::Ice::Int parentId,
                                             const ::LabrestAPI::ResourceType& type,
                                             const Ice::Current& current)
{
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    
    bool status;
    
    ::std::cout << "ResourceManagerI::modifyResource() called" << ::std::endl;
    
    status = dbPtr->modifyResource(resourceId, name, description, type.id, parentId);
    
    Event ev;
    
    ev.TypeEvent = CB_CH_RES;
    ev.id = EvQueuePtr->next_id;
    ev.resourceId = resourceId;
    ev.userDest = "";
    ev.userSrc = User.name;
    
    EvQueuePtr->push_back(ev);
    
    return status;
}

bool
LabrestAPI::ResourceManagerI::lockResource(::Ice::Int resourceId,
                                           ::Ice::Int duration,
                                           const Ice::Current& current)
{   
    bool status;
    
    ::std::cout << "ResourceManagerI::lockResource() called" << ::std::endl;
    
    status = dbPtr->lockResource(resourceId, User.name, duration);
     
    return status;
}

void
LabrestAPI::ResourceManagerI::unlockResource(::Ice::Int resourceId,
                                             const Ice::Current& current)
{
    ::std::cout << "ResourceManagerI::unlockResource() called" << ::std::endl;
    
    dbPtr->unlockResource(resourceId, User.name);
}

::LabrestAPI::IntList
LabrestAPI::ResourceManagerI::getAllResourceTypeIds(const Ice::Current& current)
{
    ::std::cout << "ResourceManagerI::getAllResourceTypeIds() called" << ::std::endl;
    
    return ::LabrestAPI::IntList();
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
                                              ::Ice::Int writeLimit,
                                              ::Ice::Int parentId,
                                              const Ice::Current& current)
{
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    int new_resource_type_id;
    
    ::std::cout << "ResourceManagerI::addResourceType() called" << ::std::endl;
    
    new_resource_type_id =   dbPtr->addResourceType(name, description, writeLimit, parentId);
    
    return new_resource_type_id;
}

bool
LabrestAPI::ResourceManagerI::deleteResourceType(::Ice::Int resourceTypeId,
                                                 const Ice::Current& current)
{
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    bool status;
    
    ::std::cout << "ResourceManagerI::deleteResourceType() called" << ::std::endl;
    
    status = dbPtr->deleteResourceType(resourceTypeId);
    
    return status;
}

bool
LabrestAPI::ResourceManagerI::modifyResourceType(::Ice::Int resourceTypeId,
                                                 const ::std::string& name,
                                                 const ::std::string& description,
                                                 ::Ice::Int writeLimit,
                                                 ::Ice::Int parentId,
                                                 const Ice::Current& current)
{
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    bool status;
    
    ::std::cout << "ResourceManagerI::modifyResourceType() called" << ::std::endl;
    
    status = dbPtr->modifyResourceType(resourceTypeId, name, description, writeLimit, parentId);
    
    return status;
}

::LabrestAPI::ResourceManagerI::ResourceManagerI(::LabrestAPI::User user)
{
    ::std::cout << "ResourceManagerI::ResourceManagerI() called" << ::std::endl;
    
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


::LabrestAPI::ResourceList
LabrestAPI::ResourceManagerI::findResource(::Ice::Int resourceTypeId,
                                           const Ice::Current& current)
{
	::LabrestAPI::ResourceList resources;

	::std::cout << "ResourceManagerI::findResource() called" << ::std::endl;

	resources = resFinder->findFreeResources(resourceTypeId);

	return resources;
}

::LabrestAPI::Resource
LabrestAPI::ResourceManagerI::findBestResource(::Ice::Int resourceTypeId,
                                               const Ice::Current& current)
{
	::LabrestAPI::Resource resource;

	::std::cout << "ResourceManagerI::findResource() called" << ::std::endl;

	resource = resFinder->findBestFreeResource(resourceTypeId);

	return resource;
}

::LabrestAPI::SequenceVariants
LabrestAPI::ResourceManagerI::findResources(const ::LabrestAPI::IntList& resourceTypeIds,
                                            const Ice::Current& current)
{
	::LabrestAPI::SequenceVariants result;

	::std::cout << "ResourceManagerI::findResources() called" << ::std::endl;

	result = resFinder->findFreeResources(resourceTypeIds);

	return result;
}

::LabrestAPI::ResourceList
LabrestAPI::ResourceManagerI::findBestResources(const ::LabrestAPI::IntList& resourceTypeIds,
                                                const Ice::Current& current)
{
	::LabrestAPI::ResourceList resources;

	::std::cout << "ResourceManagerI::findBestResources() called" << ::std::endl;

	resources = resFinder->findBestFreeResources(resourceTypeIds);

	return resources;
}

void
LabrestAPI::ResourceManagerI::connectResources(::Ice::Int resource1Id,
                                               ::Ice::Int resource2Id,
                                               const Ice::Current& current)
{
	::std::cout << "ResourceManagerI::connectResources() called" << ::std::endl;

	bool status = dbPtr->connectResources(resource1Id,resource2Id);

	if (status)
	{
		Event ev;

		ev.TypeEvent = CB_ADD_CON;
		ev.id = EvQueuePtr->next_id;
		ev.resourceId = resource1Id;
		ev.resourceIdExt = resource1Id;
		ev.userDest = "";
		ev.userSrc = User.name;

		EvQueuePtr->push_back(ev);
	}
}

void
LabrestAPI::ResourceManagerI::disconnectResources(::Ice::Int resource1Id,
                                                  ::Ice::Int resource2Id,
                                                  const Ice::Current& current)
{
	::std::cout << "ResourceManagerI::connectResources() called" << ::std::endl;

	bool status = dbPtr->disconnectResources(resource1Id,resource2Id);

	if (status)
	{
		Event ev;

		ev.TypeEvent = CB_DEL_CON;
		ev.id = EvQueuePtr->next_id;
		ev.resourceId = resource1Id;
		ev.resourceIdExt = resource1Id;
		ev.userDest = "";
		ev.userSrc = User.name;

		EvQueuePtr->push_back(ev);
	}
}

bool
LabrestAPI::ResourceManagerI::isConnectedResources(::Ice::Int resource1Id,
                                                   ::Ice::Int resource2Id,
                                                   const Ice::Current& current)
{
	::std::cout << "ResourceManagerI::isConnectedResources() called" << ::std::endl;



	return true;
}

::LabrestAPI::LinkList
LabrestAPI::ResourceManagerI::getAllConnections(const Ice::Current& current)
{
	::LabrestAPI::LinkList connections;

	::std::cout << "ResourceManagerI::getAllConnections() called" << ::std::endl;

	connections = dbPtr->getAllConnections();

	return connections;
}
