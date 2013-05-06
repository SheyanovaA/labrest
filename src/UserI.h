#ifndef __UserI_H__
#define __UserI_H__

#include "LabrestAPI.h"

namespace LabrestAPI 
{

class UserI : virtual public User
{
public:    ::std::string name;

    ::std::string auth;
    
     virtual ::std::string getUserName(const Ice::Current&);
    
 //   void setName(::std::string username);
    
 //   void setAuth(::std::string authdata);
};

};

#endif /* __UserI_H__ */
