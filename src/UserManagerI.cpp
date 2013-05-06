#include "UserManagerI.h"

bool
LabrestAPI::UserManagerI::addUser(const ::std::string& username,
                                  const ::std::string& authdata,
                                  const Ice::Current& current)
{
    bool status = true;

    std::cout << "UserManagerI::addUser() called \n";

    status = dbPtr->addUser(username,authdata);

    return status;
}

::LabrestAPI::UserList
LabrestAPI::UserManagerI::getAllUsers(const Ice::Current& current)
{

    ::LabrestAPI::UserList list;

    ::std::cout << "UserManagerI::getAllUsers() called" << ::std::endl;
    
    dbPtr->getAllUsers();

    return list;
}

bool
LabrestAPI::UserManagerI::modifyUser(const ::std::string& username,
                                     const ::std::string& authdata,
                                     const Ice::Current& current)
{
    return false;
}


bool
LabrestAPI::UserManagerI::deleteUser(const ::std::string& username,
                                     const Ice::Current& current)
{
    bool status = true;

    std::cout << "UserManagerI::deleteUser() called \n";

    status = dbPtr->deleteUser(username);

    return status;
}
