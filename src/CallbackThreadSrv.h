#ifndef CallbackThreadSrv_H
#define	CallbackThreadSrv_H

//#include <streambuf>
#include <IceUtil/Thread.h>
#include <IceUtil/Mutex.h>
#include <set>
#include "LabrestAPI.h"
#include "EventsQueue.h"


namespace LabrestAPI
{
 
class CallbackThreadSrv : public IceUtil::Thread 
{
public:

    CallbackThreadSrv();

    virtual void run();
    
    void addCallback(CallbackPrx & callback, std::string username);
    
    void removeCallback(CallbackPrx & callback);

private:

    void notifyAll();
    
    IceUtil::Mutex lock;
    
    std::set<CallbackPrx> callbacks;
};

};

#endif	/* CallbackThreadSrv_H */

