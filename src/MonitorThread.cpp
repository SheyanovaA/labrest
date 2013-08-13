#include "MonitorThread.h"

::LabrestAPI::MonitorThread::MonitorThread()
{
    ::std::cout << "MonitorThread::MonitorThread() called" << ::std::endl;
}


void
::LabrestAPI::MonitorThread::run()
{       
    std::cout << "MonitorThread::run() called" << std::endl;
    while (true)
    {
    ::LabrestAPI::ResourceList temp_res_list = dbPtr->getAllResources();
    for (::LabrestAPI::ResourceList::iterator it = temp_res_list.begin(); it != temp_res_list.end(); ++it)
    {
        if (it->resLockStatus.endTime == -1 && it->resLockStatus.duration != -1)
        {
            
            time_t start = it->resLockStatus.startTime,*t;
            if (difftime(time(t),start) >= it->resLockStatus.duration)
            {
                dbPtr->unlockResource(it->id, "system");
            }
            else
            if (difftime(time(t),start) >= it->resLockStatus.duration - 30)
            {
                CB_Event ev;
    
                ev.TypeEvent = CB_TIMEOUT;
                ev.id = (EvQueuePtr->empty())? 1 : EvQueuePtr->back().id+1;
                ev.resourceId = it->id;
                ev.username = it->resLockStatus.username;
    
                EvQueuePtr->push_back(ev);
            }
        }
    }
    sleep(10);
    }
}
