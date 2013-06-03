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
        commands["add_res"] = new add_resource_command();
        commands["add_restype"] = new add_restype_command();
        commands["delete_user"] = new delete_user_command();
        commands["delete_res"] = new delete_resource_command();
        commands["delete_restype"] = new delete_restype_command();
        commands["change_user"] = new change_user_command();
        commands["change_res"] = new change_resource_command();
        commands["change_restype"] = new change_restype_command();
        commands["all_users"] = new all_users_command();
        commands["all_res"] = new all_resource_command();
        commands["all_restypes"] = new all_restype_command();
        commands["lock_history"] = new lock_history_command();
        commands["lock_res"] = new lock_resource_command();
        commands["unlock_res"] = new unlock_resource_command();
        
        while (true) 
	{
            ::std::cout << "Labrest :  ";     
            getline(::std::cin, full_command);
            if(::std::cin.eof()) 
            {
                break;
            }
            
            std::vector<std::string> vector_command;
            std::string s = full_command;
            int i = 0;
            while (i < s.length())
            { 
                if(s[i] == ' ') s = s.erase(0,1);
                std::string t = "";
                if(s[i] == '\"')
                {
                    int start_str = i + 1, end_str = s.find_first_of('\"',i + 1) - 1;
                    t = s.substr(start_str,end_str - start_str + 1);
                    i = end_str+2;
                    vector_command.push_back(t); 
                }
                else 
                {
                    std::stringstream stream1(s.substr(i,s.length()-i));
                    stream1 >> t ;
                    i=i+t.length()+1;
                    vector_command.push_back(t);
                }
            }
                      
            base_command * cmd = commands[vector_command[0]];
            if(cmd != NULL) 
            {
                bool shouldContinue;
                
                try
                {
                    shouldContinue = cmd->run(vector_command, Session);
                }
                catch (LabrestAPI::AccessDenied & ex)
                {
                    ::std::cerr << "Access denied" << ::std::endl;
                    
                    shouldContinue = true;
                }
                catch (LabrestAPI::InvalidValue & ex)
                {
                    ::std::cerr << "Invalid Value" << ::std::endl;
                    
                    shouldContinue = true;
                }
                if(!shouldContinue) 
                {
                    break;
                }
            }
            else
            {
                commands["help"]->run(vector_command, Session);
            }
	}
        for (::std::map<std::string, base_command*>::iterator it = commands.begin(); it!=commands.end(); ++it)
        {   
           delete[] (*it).second;
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
