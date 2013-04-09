#ifndef __ENTRY_IMPL_H__
#define __ENTRY_IMPL_H__

#include "labrestapi.h"

class entry_impl : public ::labrestapi::entry
{
public:

    entry_impl();

    virtual ::labrestapi::sessionPrx login(const ::std::string&, const ::std::string&, const ::Ice::Current&);

private:

    int index;
};

#endif /* __ENTRY_IMPL_H__ */
