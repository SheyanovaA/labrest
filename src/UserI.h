#ifndef __UserI_H__
#define __UserI_H__

#include "LabrestAPI.h"

namespace LabrestAPI 
{

class UserI : virtual public User
{
public:

    virtual ::std::string getUserName(const Ice::Current&);
};

};

#endif /* __UserI_H__ */
