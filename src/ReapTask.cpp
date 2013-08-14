#include "ReapTask.h"

using namespace std;

LabrestAPI::ReapTask::ReapTask() :
    _timeout(IceUtil::Time::seconds(60))
{
//    std::cout << "ReapTask::ReapTask() called" << std::endl;
}

void
LabrestAPI::ReapTask::runTimerTask()
{
  //  std::cout << "ReapTask::runTimerTask() called" << std::endl;
    Lock sync(*this);

    list<SessionProxyPair>::iterator p = _sessions.begin();
    while(p != _sessions.end())
    {
        try
        {
            //
            // Session destruction may take time in a
            // real-world example. Therefore the current time
            // is computed for each iteration.
            //
            if((IceUtil::Time::now(IceUtil::Time::Monotonic) - p->session->timestamp()) > _timeout)
            {
                p->proxy->destroy();
                p = _sessions.erase(p);
            }
            else
            {
                ++p;
            }
        }
        catch(const Ice::ObjectNotExistException&)
        {
            p = _sessions.erase(p);
        }
    }
}

void
LabrestAPI::ReapTask::add(const SessionPrx& proxy, const SessionIPtr& session)
{
//    std::cout << "ReapTask::add() called" << std::endl;
    Lock sync(*this);
    _sessions.push_back(SessionProxyPair(proxy, session));
}

