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

	::std::cout << "Labrest :  ";

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
        ::std::string command;

        getline(::std::cin, command);

        while (command != "exit") 
	{
	    if (command.find("add user") != ::std::string::npos)
	    {
		command.erase(0,9);

		::std::string usname, auth;

		usname = command.substr(0,command.find(' '));

		auth = command.substr(command.find(' ')+1,command.length());

		Session->getUserManager()->addUser(usname, auth);
            }
            ::std::cout << "Labrest :  ";

            getline(::std::cin, command);
	}

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

