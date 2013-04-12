#ifndef __ENTRY_IMPL_H__
#define __ENTRY_IMPL_H__

#include "labrestapi.h"

class Entry_I : public ::LabrestAPI::Entry
{
public:

    Entry_I();

    virtual ::LabrestAPI::SessionPrx Login(const ::std::string&, const ::std::string&, const ::Ice::Current&);

private:

    int index;
};

#endif /* __ENTRY_IMPL_H__ */
