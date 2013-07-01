#ifndef MonitorThread_H
#define	MonitorThread_H

#include <IceUtil/Thread.h>
#include <IceUtil/Time.h>

namespace LabrestAPI
{

class MonitorThread : public IceUtil::Thread
{
public:
    MonitorThread();
    
    virtual void run();
};

};

#endif	/* MonitorThread_H */

