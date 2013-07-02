#include "CallbackThreadSrv.h"

LabrestAPI::CallbackThreadSrv::CallbackThreadSrv() : IceUtil::Thread() {
    ::std::cout << "CallbackThreadSrv::CallbackThreadSrv() called" << ::std::endl;
}

void
LabrestAPI::CallbackThreadSrv::run() {
    ::std::cout << "CallbackThreadSrv::run() called" << ::std::endl;
    while(true) 
    {
        notifyAll();
        sleep(5);
    }
}
    
void
LabrestAPI::CallbackThreadSrv::addCallback(CallbackPrx & callback, std::string username) 
{
    ::std::cout << "CallbackThreadSrv::addCallback() called" << ::std::endl;
    this->lock.lock(); 
    this->callbacks[callback] = username; 
    this->lock.unlock();
}

void
LabrestAPI::CallbackThreadSrv::removeCallback(CallbackPrx & callback) {
    ::std::cout << "CallbackThreadSrv::removeCallback() called" << ::std::endl;
    this->lock.lock();
    this->callbacks.erase(callback);
    this->lock.unlock();
}

void
LabrestAPI::CallbackThreadSrv::notifyAll() {
    this->lock.lock();
   
//    ::std::cout << "CallbackThreadSrv::notifyAll() called" << ::std::endl;
    while (!EvQueuePtr->empty())
    {
        CB_Event temp_ev = EvQueuePtr->pop();
        Event ev;
        ev.TypeEvent = temp_ev.TypeEvent;
        ev.id =  temp_ev.id;
        ev.resourceId = temp_ev.resourceId;
        for(std::map<CallbackPrx, std::string>::iterator it = this->callbacks.begin(); it != this->callbacks.end(); it++) 
        {
            try
            {
                if ((temp_ev.username == "") ||(temp_ev.username == (*it).second))
                    (*it).first->doCallback(ev);
            }
            catch (const Ice::Exception& ex)
            {
                std::cerr << ex << std::endl;
                this->callbacks.erase(it);
            }
        }
    }
    this->lock.unlock();
}