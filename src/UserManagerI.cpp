#include "UserManagerI.h"

bool
LabrestAPI::UserManagerI::addUser(const ::std::string& username,
                                  const ::std::string& authdata,
                                  const Ice::Current& current)
{
    dbPtr->exec("insert into user values('"+username+"','"+authdata+"');");

    std::cout << "UserManagerI::addUser() called \n";

    return true;
}

::LabrestAPI::UserList
LabrestAPI::UserManagerI::getAllUsers(const Ice::Current& current)
{

    ::LabrestAPI::UserList list;

    ::std::cout << "UserManagerI::getAllUsers() called" << ::std::endl;

    return list;
}
