#include "CallbackThreadSrv.h"



LabrestAPI::CallbackThreadSrv::CallbackThreadSrv() : IceUtil::Thread() {
    ::std::cout << "CallbackThreadSrv::CallbackThreadSrv() called" << ::std::endl;
}

void
LabrestAPI::CallbackThreadSrv::run() {
    ::std::cout << "CallbackThreadSrv::run() called" << ::std::endl;
    while(!EvQueuePtr->empty()) {
        notifyAll();
        sleep(10);
    }
}
    
void
LabrestAPI::CallbackThreadSrv::addCallback(CallbackPrx & callback, std::string username) 
{
    ::std::cout << "CallbackThreadSrv::addCallback() called" << ::std::endl;
    this->lock.lock();
   /* CB temp;
    temp.callback = callback;
    temp.username = username;  
    this->callbacks.insert(temp); **/
/**/    this->callbacks.insert(callback);
    this->lock.unlock();
}

void
LabrestAPI::CallbackThreadSrv::removeCallback(CallbackPrx & callback) {
    ::std::cout << "CallbackThreadSrv::removeCallback() called" << ::std::endl;
    this->lock.lock();
    /*for(std::set<CB>::iterator it = this->callbacks.begin(); it != this->callbacks.end(); it++) 
    {
        if (it->callback == callback) 
        {
            this->callbacks.erase(it);
            break;
        }
    }**/
/**/  this->callbacks.erase(callback);
    this->lock.unlock();
}

void
LabrestAPI::CallbackThreadSrv::notifyAll() {
    this->lock.lock();
    if(!callbacks.empty())
    {
        ::std::cout << "CallbackThreadSrv::notifyAll() called" << ::std::endl;
        while (!EvQueuePtr->empty())
        {
            
            CB_Event temp_ev = EvQueuePtr->pop();
            Event ev;
            ev.TypeEvent = temp_ev.TypeEvent;
            ev.id = temp_ev.id;
            ev.resourceId = temp_ev.resourceId;
//            for(std::set<CB>::iterator it = this->callbacks.begin(); it != this->callbacks.end(); it++) {
              for(std::set<CallbackPrx>::iterator it = this->callbacks.begin(); it != this->callbacks.end(); it++) {
                try
                {
                   // it->callback->doCallback(ev);
                    
                   /**/
                    CallbackPrx cb = *it;
                    cb->doCallback(ev);
                }
                catch (const Ice::Exception& ex)
                {
                    std::cerr << ex << std::endl;
                    this->callbacks.erase(it);
                }
            }
        }
    }
    this->lock.unlock();
}