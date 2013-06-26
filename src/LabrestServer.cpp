#include <iostream>
#include <Ice/Ice.h>

#include "LabrestDB.h"
#include "LabrestAPI.h"
#include "SessionI.h"
#include "EntryI.h"
#include "EventsQueue.h"

LabrestAPI::LabrestDB * dbPtr;
LabrestAPI::EventsQueue * EvQueuePtr;

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

    Ice::ObjectPtr object = new ::LabrestAPI::EntryI;

    adapter->add(object, communicator()->stringToIdentity("SimpleEntry"));

    adapter->activate();

    ::LabrestAPI::LabrestDB db;

    dbPtr = &db;
    
    ::LabrestAPI::EventsQueue queue;
    
    EvQueuePtr = &queue;

    communicator()->waitForShutdown();

    db.disconnect();
    
    return status;
}
