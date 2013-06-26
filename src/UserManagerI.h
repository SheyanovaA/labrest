#ifndef UserManagerI_H
#define UserManagerI_H

#include "LabrestAPI.h"
#include "LabrestDB.h"

namespace LabrestAPI
{

class UserManagerI : virtual public UserManager
{
    ::LabrestAPI::User User;
    
public:
    
    UserManagerI(::LabrestAPI::User user);

    virtual bool addUser(const ::std::string&,
                         const ::std::string&,
                         ::Ice::Int,
                         const Ice::Current&);

    virtual bool deleteUser(const ::std::string&,
                            const Ice::Current&);

    virtual ::LabrestAPI::UserList getAllUsers(const Ice::Current&);
    
    virtual ::LabrestAPI::User getUser(const ::std::string&,
                                           const Ice::Current&);

    virtual bool modifyUser(const ::std::string&,
                            const ::std::string&,
                            ::Ice::Int,
                            const Ice::Current&);
};

};

#endif /* UserManagerI_H */
