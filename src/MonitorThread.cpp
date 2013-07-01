#include "MonitorThread.h"
#include "LabrestDB.h"

void
::LabrestAPI::MonitorThread::run()
{
    ::LabrestAPI::ResourceList temp_res_list = dbPtr->getAllResources();
    for (::LabrestAPI::ResourceList::iterator it = temp_res_list.begin(); it != temp_res_list.end(); ++it)
    {
        if (it->resLockStatus.endTime.empty())
        {
            it->resLockStatus.starTime;
            it->resLockStatus.duration;
        }
    }
}
