#ifndef EntryI_H
#define EntryI_H

#include <iostream>
#include <string>
#include <Ice/Ice.h>

#include "SessionI.h"
#include "LabrestAPI.h"
#include "ReapTask.h"

namespace LabrestAPI 
{

class EntryI : public Entry
{
public:

    EntryI(const ReapTaskPtr&);

    virtual ::LabrestAPI::SessionPrx login(const ::std::string&, const ::std::string&, const ::Ice::Current&);

private:
    
    int adc_pwd_check(const char * login, const char * password);

    int index;
    
    const ReapTaskPtr _reaper;
};

};
#endif /* EntryI_H */
