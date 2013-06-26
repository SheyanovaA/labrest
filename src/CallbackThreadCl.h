#ifndef CallbackThreadCl_H
#define	CallbackThreadCl_H

#include <Ice/Ice.h>
#include <IceUtil/Thread.h>
#include <Ice/Communicator.h>
#include <IceUtil/UUID.h>

#include "LabrestAPI.h"
#include "CallbackI.h"

namespace LabrestAPI
{

class CallbackThreadCl : public IceUtil::Thread 
{
public:
    CallbackThreadCl(Ice::CommunicatorPtr ic);
    
    virtual void run();
private:
    
    Ice::CommunicatorPtr IC;          
};

};

#endif	/* CallbackThreadCl_H */

