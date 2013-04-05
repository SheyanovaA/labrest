#ifndef __ENTRY_IMPL_H__
#define __ENTRY_IMPL_H__

#include "labrestapi.h"

class entry_impl : public ::labrestapi::entry
{
public:

    virtual ::labrestapi::sessionPtr login(const ::std::string&, const ::std::string&, const ::Ice::Current&);
};

#endif /* __ENTRY_IMPL_H__ */
