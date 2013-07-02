#include "EventsQueue.h"

LabrestAPI::CB_Event
LabrestAPI::EventsQueue::back()
{
    while (!this->lock.tryLock()) {};
    
//    ::std::cout << "EventsQueue::back() called" << ::std::endl;
    
    LabrestAPI::CB_Event event = this->ev_queue.back();
    
    this->lock.unlock();
    
    return event;
}

bool
LabrestAPI::EventsQueue::empty()
{
    while (!this->lock.tryLock()) {};
    
//    ::std::cout << "EventsQueue::empty() called" << ::std::endl;
    
    bool emp = this->ev_queue.empty();
    
    this->lock.unlock();
    
    return emp;
}

LabrestAPI::CB_Event
LabrestAPI::EventsQueue::front()
{
    while (!this->lock.tryLock()) {};
    
//    ::std::cout << "EventsQueue::front() called" << ::std::endl;
    
    LabrestAPI::CB_Event event = this->ev_queue.front();
    
    this->lock.unlock();
    
    return event;
}

int
LabrestAPI::EventsQueue::size()
{
    while (!this->lock.tryLock()) {};
    
//    ::std::cout << "EventsQueue::size() called" << ::std::endl;
    
    int size = this->ev_queue.size();
    
    this->lock.unlock();
    
    return size;
}

void
LabrestAPI::EventsQueue::push_back(CB_Event ev)
{
    while (!this->lock.tryLock()) {};
    
    ::std::cout << "EventsQueue::push_back() called" << ::std::endl;
    
    this->ev_queue.push_back(ev);
    
    this->lock.unlock();
}

LabrestAPI::CB_Event
LabrestAPI::EventsQueue::pop()
{
    while (!this->lock.tryLock()) {};
    
    ::std::cout << "EventsQueue::pop() called" << ::std::endl;
    
    LabrestAPI::CB_Event temp = this->ev_queue.front();
    
    this->ev_queue.pop_front();
   
    this->lock.unlock();
    
    return temp;
}