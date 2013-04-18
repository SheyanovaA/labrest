#ifndef __UserManagerI_H__
#define __UserManagerI_H__

#include "LabrestAPI.h"

namespace LabrestAPI
{

class UserManagerI : virtual public UserManager
{
public:

    virtual bool addUser(const ::std::string&,
                         const ::std::string&,
                         const Ice::Current&);
    virtual ::std::string getAllUsers(const Ice::Current&);
};

};
#endif /* __UserManagerI_H__ */
