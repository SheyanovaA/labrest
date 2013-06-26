#ifndef EventsQueue_H
#define	EventsQueue_H

#include <deque>
#include <IceUtil/Mutex.h>
#include "LabrestAPI.h"

#define CB_ADD_RES  1
#define CB_DEL_RES  2
#define CB_CH_RES   3
#define CB_LOCK     4
#define CB_UNLOCK   5
#define CB_TIMEOUT  6



namespace LabrestAPI
{

    struct CB_Event : public Event
    {
        std::string username;
    };
    
class EventsQueue 
{
    std::deque<CB_Event> ev_queue;
    
    IceUtil::Mutex lock;
    
public:
   
    void push_back(CB_Event ev);
    
    CB_Event back();
    
    bool empty();
    
    CB_Event front();
    
    CB_Event pop();
    
    int size();
};

};

extern LabrestAPI::EventsQueue * EvQueuePtr;

#endif	/* EventsQueue_H */

