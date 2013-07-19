#ifndef ReapTask_H
#define	ReapTask_H

#include <IceUtil/IceUtil.h>
#include <list>

#include "SessionI.h"

namespace LabrestAPI 
{

class ReapTask : public IceUtil::TimerTask, public IceUtil::Monitor<IceUtil::Mutex>
{
public:

    ReapTask();

    virtual void runTimerTask();
    void terminate();
    void add(const SessionPrx&, const SessionIPtr&);

private:

    const IceUtil::Time _timeout;
    struct SessionProxyPair
    {
        SessionProxyPair(const SessionPrx& p, const SessionIPtr& s) :
            proxy(p), session(s) { }
        const SessionPrx proxy;
        const SessionIPtr session;
    };
    std::list<SessionProxyPair> _sessions;
};
typedef IceUtil::Handle<ReapTask> ReapTaskPtr;

}

#endif	/* ReapTask_H */

