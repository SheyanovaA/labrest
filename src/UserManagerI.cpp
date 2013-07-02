#include "UserManagerI.h"

::LabrestAPI::UserManagerI::UserManagerI(::LabrestAPI::User user)
{
    User = user;
}

bool
LabrestAPI::UserManagerI::addUser(const ::std::string& username,
                                  const ::std::string& authdata,
                                  ::Ice::Int group,
                                  const Ice::Current& current)
{
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    bool status = true;

//    std::cout << "UserManagerI::addUser() called \n";

    status = dbPtr->addUser(username,authdata,group);

    return status;
}

::LabrestAPI::UserList
LabrestAPI::UserManagerI::getAllUsers(const Ice::Current& current)
{

    ::LabrestAPI::UserList list;

//    ::std::cout << "UserManagerI::getAllUsers() called" << ::std::endl;
    
    list = dbPtr->getAllUsers();
    
    return list;
}

::LabrestAPI::User 
LabrestAPI::UserManagerI::getUser(const ::std::string& username, 
                                  const Ice::Current&)
{
    ::LabrestAPI::User user;

//    ::std::cout << "UserManagerI::getUser() called" << ::std::endl;
    
    user = dbPtr->getUser(username);
    
    return user;
}

bool
LabrestAPI::UserManagerI::modifyUser(const ::std::string& username,
                                     const ::std::string& authdata,
                                     ::Ice::Int group,
                                     const Ice::Current& current)
{   
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    bool status = true;

//    std::cout << "UserManagerI::modifyUser() called \n";

    status = dbPtr->modifyUser(username, authdata,group);
    
    return false;
}


bool
LabrestAPI::UserManagerI::deleteUser(const ::std::string& username,
                                     const Ice::Current& current)
{
    if (User.group == 0)
    {
        AccessDenied ad;
        ad.ice_throw();
    }
    bool status = true;

//    std::cout << "UserManagerI::deleteUser() called \n";

    status = dbPtr->deleteUser(username);

    return status;
}
