#ifndef __UserManagerI_H__
#define __UserManagerI_H__

#include "LabrestAPI.h"
#include "LabrestDB.h"

namespace LabrestAPI
{

class UserManagerI : virtual public UserManager
{
public:

    virtual bool addUser(const ::std::string&,
                         const ::std::string&,
                         const Ice::Current&);

    virtual bool deleteUser(const ::std::string&,
                            const Ice::Current&);

    virtual ::LabrestAPI::UserList getAllUsers(const Ice::Current&);

    virtual bool modifyUser(const ::std::string&,
                            const ::std::string&,
                            const Ice::Current&);
};

};

#endif /* __UserManagerI_H__ */
