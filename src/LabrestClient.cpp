#include <Ice/Ice.h>
#include <Ice/ObjectFactory.h>
#include <sstream>

#include "LabrestAPI.h"
#include "EntryI.h"
#include "UserCommand.h"

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

        ::std::map<std::string, base_command *> commands;
 
        commands["exit"] = new exit_command();
        commands["help"] = new help_command();
        commands["add_user"] = new add_user_command();
        commands["delete_user"] = new delete_user_command();
        commands["all_users"] = new all_users_command();
        
        while (true) 
	{
            ::std::cout << "Labrest :  ";     
            getline(::std::cin, full_command);
            if(::std::cin.eof()) {
                break;
            }
            
            std::stringstream full_command_stream;
            full_command_stream.str(full_command);
            std::vector<std::string> vector_command;
            while(full_command_stream.good()) {
                std::string s;
                full_command_stream>>s;
                vector_command.push_back(s);
            }

            base_command * cmd = commands[vector_command[0]];
            if(cmd != NULL) {
                bool shouldContinue = cmd->run(vector_command, Session);
                if(!shouldContinue) {
                    break;
                }
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
