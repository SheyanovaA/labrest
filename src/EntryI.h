#ifndef EntryI_H
#define EntryI_H

#include <iostream>
#include <string>
#include <Ice/Ice.h>

#include "SessionI.h"
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
#endif /* EntryI_H */
