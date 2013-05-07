#include <Ice/Ice.h>
#include <Ice/ObjectFactory.h>
#include <sstream>

#include "LabrestAPI.h"
#include "UserI.h"
#include "EntryI.h"
#include "ObjectFactory.h"

void 
exec_command(::std::string full_comm, 
        ::LabrestAPI::SessionPrx Session);

int
main(int argc, char* argv[])
{
    int status = 0;

    Ice::CommunicatorPtr ic;

    try
    {
        ic = Ice::initialize(argc, argv);

//        ::Ice::ObjectFactoryPtr factory = new ::LabrestAPI::ObjectFactory();
//        ic->addObjectFactory(factory, ::LabrestAPI::User::ice_staticId());
        
        Ice::ObjectPrx base = ic->stringToProxy("SimpleEntry:default -p 10000");

        ::LabrestAPI::EntryPrx Entry = ::LabrestAPI::EntryPrx::checkedCast(base);

        if (!Entry)
            throw "Invalid proxy";

	::std::cout << "Labrest :  ";

        ::LabrestAPI::SessionPrx Session; 

        try
        {
	    ::std::string name, auth;

	    if (argc == 1) 
	    {
		::std::cerr << "Login required! \n";

		::std::cout <<  "Login: "; ::std::cin >> name;
	
		::std::cout <<  "password: "; ::std::cin >> auth;
	    }
	    else
	    {
		if (argc == 2)
		{
		    name = argv[1];

		    ::std::cout <<  "password: "; ::std::cin >> auth;
		} 
		else 
		{
		    if (argc == 3) 
		    {
		        name = argv[1];
 		
  			auth = argv[2];
		    }
		    else
		    {
			name = " "; auth = " ";

			::std::cout << "Wrong number of parameters!\nNeed only 2 parameters!\n";
		    }
		}
	    }
	    Session = Entry->login(name, auth);
        }
        catch(LabrestAPI::LoginException & ex)
        {
            ::std::cerr << "Login error" << ::std::endl;
           return 1;
        }
        ::std::string full_command;

        getline(::std::cin, full_command);

        while (full_command != "exit") 
	{
	    exec_command(full_command, Session);
		
            if(::std::cin.eof()) 
	    {
		full_command = "exit";

		::std::cout << full_command << ::std::endl;

                break;
            } 
	    else
	    {
                ::std::cout << "Labrest :  ";

                getline(::std::cin, full_command);
	    }
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

void exec_command(::std::string full_comm, ::LabrestAPI::SessionPrx session)
{
    ::std::string command;

    ::std::stringstream ss;

    ss.str (full_comm);

    ss >> command;

    if (command == "add_user")
    {
	::std::string usname, auth;

	ss >> usname >> auth;

	if (!session->getUserManager()->addUser(usname, auth))

	    ::std::cout << "this user has not been added!\nUser with the name \"" << usname << "\" already exists!\n";
    };
    if (command == "add_resource")
    {
	::std::string name, descr;

	int  tipe_id, parent_id;

	ss >> name >> descr >> tipe_id >> parent_id;

	session->getResourceManager()->addResource(name,descr,tipe_id,parent_id);
    };
    if (command == "delete_user")
    {
	::std::string usname;

	ss >> usname;

	if (!session->getUserManager()->deleteUser(usname))

	    ::std::cout << "this user has not been deleted!\nUser with the name \"" << usname << "\" does not exists!\n";
    };
    if (command == "all_users")
    {
        ::LabrestAPI::UserList users;
         
	users = session->getUserManager()->getAllUsers();
        
        for (::LabrestAPI::UserList::iterator it = users.begin(); it != users.end(); it++)
        {
           ::LabrestAPI::User temp;
           
           temp = *it;
            
           ::std::cout <<  temp.name << ::std::endl;
        };

    };
    if (command == "help")
    {
	::std::cout << "all_users" << ::std::endl;
        
        ::std::cout << "add_user username authdata" << ::std::endl;
        
        ::std::cout << "delete_user username" << ::std::endl;
        
        ::std::cout << "add_resource name description tipe_id parent_id " << ::std::endl;
        
        ::std::cout << "exit" << ::std::endl;
    };
}
