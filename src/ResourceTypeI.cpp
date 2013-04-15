#include "ResourceTypeI.h"

::Ice::Int
LabrestAPI::ResourceTypeI::getId(const Ice::Current& current)
{
    return 0;
}

::std::string
LabrestAPI::ResourceTypeI::getName(const Ice::Current& current)
{
    return ::std::string();
}

::std::string
LabrestAPI::ResourceTypeI::getDescription(const Ice::Current& current)
{
    return ::std::string();
}

::LabrestAPI::ResourceTypePtr
LabrestAPI::ResourceTypeI::getParent(const Ice::Current& current)
{
    return 0;
}
