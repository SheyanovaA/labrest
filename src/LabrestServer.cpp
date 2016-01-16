#include <iostream>
#include <Ice/Ice.h>

#include "LabrestDB.h"
#include "LabrestAPI.h"
#include "SessionI.h"
#include "EntryI.h"
#include "EventsQueue.h"
#include "MonitorThread.h"
#include "ReapTask.h"
#include "ResourceFinder.h"

LabrestAPI::LabrestDB * dbPtr;
LabrestAPI::ResourceFinder * resFinder;
LabrestAPI::EventsQueue * EvQueuePtr;
LabrestAPI::CallbackThreadSrv * CbThreadPtr;

class LabrestServerApp : public Ice::Application 
{
public:
    virtual int run(int argc, char* argv[]);
};


int
main(int argc, char* argv[])
{
    LabrestServerApp labrest_server;
    
    return labrest_server.main(argc,argv,"config.server");
};


int
LabrestServerApp::run(int argc, char* argv[])
{
    if(argc > 1)
    {
        ::std::cerr << appName() << ": too many arguments" << ::std::endl;
        return EXIT_FAILURE;
    }
    
    int status = 0;
    
    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("LabrestServer");

    IceUtil::TimerPtr timer = new IceUtil::Timer();
    
    LabrestAPI::ReapTaskPtr reapTask = new LabrestAPI::ReapTask;
    
    timer->scheduleRepeated(reapTask, IceUtil::Time::seconds(1));

    Ice::ObjectPtr object = new ::LabrestAPI::EntryI(reapTask);

    adapter->add(object, communicator()->stringToIdentity("SimpleEntry"));

    adapter->activate();

    ::LabrestAPI::LabrestDB db;

    dbPtr = &db;
    
    ::LabrestAPI::ResourceFinder resourceFinder;

    resFinder = &resourceFinder;

    ::LabrestAPI::EventsQueue queue;
    
    EvQueuePtr = &queue;
    
    LabrestAPI::CallbackThreadSrv CbThread;
    
    CbThreadPtr = &CbThread;
    
    CbThreadPtr->start();
    
    ::LabrestAPI::MonitorThread monitor;
    
    monitor.start();

    communicator()->waitForShutdown();
    
    return status;
}
