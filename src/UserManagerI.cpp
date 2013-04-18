#include "UserManagerI.h"

bool
LabrestAPI::UserManagerI::addUser(const ::std::string& username,
                                  const ::std::string& authdata,
                                  const Ice::Current& current)
{
    return false;
}

::std::string
LabrestAPI::UserManagerI::getAllUsers(const Ice::Current& current)
{
    return " ";
}
