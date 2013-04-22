#include <Ice/Ice.h>

#include "LabrestAPI.h"

int
main(int argc, char* argv[])
{
    int status = 0;

    Ice::CommunicatorPtr ic;

    try
    {
        ic = Ice::initialize(argc, argv);

        Ice::ObjectPrx base = ic->stringToProxy("SimpleEntry:default -p 10000");

        ::LabrestAPI::EntryPrx Entry = ::LabrestAPI::EntryPrx::checkedCast(base);

        if (!Entry)
            throw "Invalid proxy";

	::std::cout << "Пользователь: " << argv[1] << "\n Пароль: " << argv[2] << ::std::endl;

        ::LabrestAPI::SessionPrx Session;

        try
        {
            Session = Entry->login(argv[1], argv[2]);
        }
        catch(LabrestAPI::LoginException & ex)
        {
            ::std::cerr<<"Login error"<<::std::endl;
            return 1;
        }

::LabrestAPI::ResourceManagerPrx ResourceManager = Session->getResourceManager();

ResourceManager->getAllResourceIds();

::LabrestAPI::UserManagerPrx UserManager = Session->getUserManager();

UserManager->addUser("user6", "password");

} catch (const LabrestAPI::LoginException &logex) {
}
    
    catch (const Ice::Exception& ex)
    {
        ::std::cerr << ex << ::std::endl;

        status = 1;
    }
    catch (const char* msg)
    {
        ::std::cerr << msg << ::std::endl;

        status = 1;
    }
    if (ic)

        ic->destroy();

    return status;
}

