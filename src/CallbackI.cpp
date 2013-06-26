#include "CallbackI.h"
#include "EventsQueue.h"

void
LabrestAPI::CallbackI::doCallback(const ::LabrestAPI::Event& ev,
                                  const Ice::Current& current)
{
    switch(ev.TypeEvent)
    {
        case CB_ADD_RES: ::std::cout << "Add new resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_DEL_RES: ::std::cout << "Delete reaourse with id = " << ev.resourceId << ::std::endl; break;
        case CB_CH_RES: ::std::cout << "Change resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_LOCK: ::std::cout << "Lock resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_UNLOCK: ::std::cout << "Unlock resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_TIMEOUT: ::std::cout <<"Remained 5 minutes of lock resource with id = " << ev.resourceId << ::std::endl; break;
    }
}