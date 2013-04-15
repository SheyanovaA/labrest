#include <iostream>
#include <Ice/Ice.h>

#include "LabrestAPI.h"
#include "SessionI.h"
#include "EntryI.h"

int
main(int argc, char* argv[])
{
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectAdapterPtr adapter =
            ic->createObjectAdapterWithEndpoints("SimpleEntryAdapter", "default -p 10000");
        Ice::ObjectPtr object = new ::LabrestAPI::EntryI;
        adapter->add(object, ic->stringToIdentity("SimpleEntry"));
        adapter->activate();
        ic->waitForShutdown();
    } catch (const Ice::Exception& e) {
        ::std::cerr << e << ::std::endl;
        status = 1;
    } catch (const char* msg) {
        ::std::cerr << msg << ::std::endl;
        status = 1;
    }
    if (ic) {
        try {
            ic->destroy();
        } catch (const Ice::Exception& e) {
            ::std::cerr << e << ::std::endl;
            status = 1;
        }
    }
    return status;
}
