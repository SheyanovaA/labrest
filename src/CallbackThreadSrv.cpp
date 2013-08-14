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
    
    std::cout << "CallbackThreadSrv::notifyAll() called" << std::endl;
    this->lock.lock();
   
//    ::std::cout << "CallbackThreadSrv::notifyAll() called" << ::std::endl;
    while (!EvQueuePtr->empty())
    {
        Event ev = EvQueuePtr->pop();

        for(std::map<CallbackPrx, std::string>::iterator it = this->callbacks.begin(); it != this->callbacks.end(); it++) 
        {
            try
            {
                if ((ev.username == "") ||(ev.username == (*it).second))
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
