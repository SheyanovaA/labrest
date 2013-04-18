#include <Ice/Ice.h>

#include "LabrestAPI.h"

int
main(int argc, char* argv[])
{
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectPrx base = ic->stringToProxy("SimpleEntry:default -p 10000");
        ::LabrestAPI::EntryPrx Entry = ::LabrestAPI::EntryPrx::checkedCast(base);
        if (!Entry)
            throw "Invalid proxy";
        ::LabrestAPI::SessionPrx Session = Entry->login("user", "password");
	::LabrestAPI::ResourceManagerPrx ResourceManager = Session->getResourceManager();
	ResourceManager->getAllResourceIds();
	::LabrestAPI::UserManagerPrx UserManager = Session->getUserManager();
	::std::cout << UserManager->getAllUsers() << ::std::endl;
	UserManager->addUser("user", "password");
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
