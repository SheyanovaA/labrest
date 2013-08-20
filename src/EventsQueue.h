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

class EventsQueue 
{
    std::deque<Event> ev_queue;
    
    IceUtil::Mutex lock;
    
public:
    EventsQueue();
   
    void push_back(Event ev);
    
    Event back();
    
    bool empty();
    
    Event front();
    
    Event pop();
    
    int size();

    int next_id;
};

};

extern LabrestAPI::EventsQueue * EvQueuePtr;

#endif	/* EventsQueue_H */

