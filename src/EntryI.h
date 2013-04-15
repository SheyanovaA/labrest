#ifndef __ENTRYI_H__
#define __ENTRYI_H__

#include "LabrestAPI.h"

namespace LabrestAPI 
{

class EntryI : public Entry
{
public:

    EntryI();

    virtual ::LabrestAPI::SessionPrx login(const ::std::string&, const ::std::string&, const ::Ice::Current&);

private:

    int index;
};

};
#endif /* __ENTRYI_H__ */
