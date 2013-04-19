#include <iostream>
#include <Ice/Ice.h>

#include "LabrestDB.h"
#include "LabrestAPI.h"
#include "SessionI.h"
#include "EntryI.h"

LabrestAPI::LabrestDB * dbPtr;

int
main(int argc, char* argv[])
{

    int status = 0;

    Ice::CommunicatorPtr ic;

    try 
    {
        ic = Ice::initialize(argc, argv);
    
        Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("SimpleEntryAdapter", "default -p 10000");

        Ice::ObjectPtr object = new ::LabrestAPI::EntryI;

        adapter->add(object, ic->stringToIdentity("SimpleEntry"));

        adapter->activate();

	::LabrestAPI::LabrestDB db;

	dbPtr = &db;

        ic->waitForShutdown();

	db.disconnect();
    } 
    catch (const Ice::Exception& e) 
    {
        ::std::cerr << e << ::std::endl;

        status = 1;

    } 
    catch (const char* msg) 
    {
        ::std::cerr << msg << ::std::endl;

        status = 1;
    }

    if (ic) 
    {
        try 
        {
            ic->destroy();
        } 
        catch (const Ice::Exception& e) 
        {
            ::std::cerr << e << ::std::endl;

            status = 1;
        }
    }

    return status;
}
