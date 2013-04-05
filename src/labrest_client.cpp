#include <Ice/Ice.h>

#include "labrestapi.h"

int
main(int argc, char* argv[])
{
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectPrx base = ic->stringToProxy("SimpleEntry:default -p 10000");
        ::labrestapi::entryPrx entry = ::labrestapi::entryPrx::checkedCast(base);
        if (!entry)
            throw "Invalid proxy";

        ::labrestapi::sessionPrx session = entry->login("user", "password");
        session->test();
    } catch (const Ice::Exception& ex) {
        ::std::cerr << ex << ::std::endl;
        status = 1;
    } catch (const char* msg) {
        ::std::cerr << msg << ::std::endl;
        status = 1;
    }
    if (ic)
        ic->destroy();
    return status;
}
