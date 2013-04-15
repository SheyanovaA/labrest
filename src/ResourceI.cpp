#include "ResourceI.h"

::Ice::Int
LabrestAPI::ResourceI::getId(const Ice::Current& current)
{
    return 0;
}

::std::string
LabrestAPI::ResourceI::getName(const Ice::Current& current)
{
    return ::std::string();
}

::std::string
LabrestAPI::ResourceI::getDescription(const Ice::Current& current)
{
    return ::std::string();
}

bool
LabrestAPI::ResourceI::getLockStatus(const Ice::Current& current)
{
    return false;
}

::LabrestAPI::ResourcePtr
LabrestAPI::ResourceI::getParent(const Ice::Current& current)
{
    return 0;
}

::LabrestAPI::ResourceTypePtr
LabrestAPI::ResourceI::getType(const Ice::Current& current)
{
    return 0;
}

