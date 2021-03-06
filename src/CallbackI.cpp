#include "CallbackI.h"
#include "EventsQueue.h"

void
LabrestAPI::CallbackI::doCallback(const ::LabrestAPI::Event& ev,
                                  const Ice::Current& current)
{
    std::cout << "CallbackI::doCallback() called" << std::endl; 
    switch(ev.TypeEvent)
    {
        case CB_ADD_RES: ::std::cout << "Added new resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_DEL_RES: ::std::cout << "Deleted resourse with id = " << ev.resourceId << ::std::endl; break;
        case CB_CH_RES: ::std::cout << "Changed resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_LOCK: ::std::cout << "Locked resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_UNLOCK: ::std::cout << "Unlocked resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_TIMEOUT: ::std::cout <<"Less than 5 minutes remaining lock resource with id = " << ev.resourceId << ::std::endl; break;
        case CB_ADD_CON: ::std::cout <<"Added connection between resources with ids: " << ev.resourceId << " and " << ev.resourceIdExt << ::std::endl; break;
        case CB_DEL_CON: ::std::cout <<"Deleted connection between resources with ids: " << ev.resourceId << " and " << ev.resourceIdExt << ::std::endl; break;
    }
}
