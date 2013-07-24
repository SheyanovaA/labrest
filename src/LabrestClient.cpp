#include <Ice/Ice.h>
#include <Ice/ObjectFactory.h>
#include <sstream>

#include "LabrestAPI.h"
#include "EntryI.h"
#include "UserCommand.h"
#include "CallbackThreadCl.h"

class RefreshTask : public IceUtil::TimerTask
{
public:

    RefreshTask(const Ice::LoggerPtr& logger, const LabrestAPI::SessionPrx& session) :
        _logger(logger),
        _session(session)
    {
    }

    virtual void
    runTimerTask()
    {
        try
        {
            _session->Refresh();
        }
        catch(const Ice::Exception& ex)
        {
            Ice::Warning warn(_logger);
            warn << "RefreshTask: " << ex;
        }
    }

private:

    const Ice::LoggerPtr _logger;
    const LabrestAPI::SessionPrx _session;
};


class LabrestClientApp : public Ice::Application 
{
public:        
    virtual int run(int argc, char* argv[]);
    
private:
    IceUtil::Mutex _mutex;
    IceUtil::TimerPtr _timer;
    LabrestAPI::SessionPrx _session;
};


int
main(int argc, char* argv[])
{
    LabrestClientApp labrest_client;
    
    return labrest_client.main(argc,argv,"config.client");
};


int
LabrestClientApp::run(int argc, char* argv[])
{
    int status = 0;

        Ice::ObjectPrx base = communicator()->propertyToProxy("LabrestClient.Proxy");

        ::LabrestAPI::EntryPrx Entry = ::LabrestAPI::EntryPrx::checkedCast(base);

        if (!Entry)
            throw "Invalid proxy";

        ::LabrestAPI::SessionPrx _session;
                
        Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("");
   
        Ice::Identity ident;
   
        ident.name = IceUtil::generateUUID();
   
        ident.category = "";
   
        LabrestAPI::CallbackPtr cb = new LabrestAPI::CallbackI;
   
        adapter->add(cb, ident);
    
        adapter->activate();
   
        try
        {
            ::std::string name, auth;

	    if (argc == 3) 
            {
                name = argv[1];
 		
                auth = argv[2];
            }
            else
            {
                return 1;
            }
            {
                IceUtil::Mutex::Lock sync(_mutex);
        
                _session = Entry->login(name, auth);
            
                _timer = new IceUtil::Timer();
        
                _timer->scheduleRepeated(new RefreshTask(communicator()->getLogger(), _session), IceUtil::Time::seconds(5));
            }
        }
        catch(LabrestAPI::LoginException & ex)
        {
            ::std::cerr << "Login error" << ::std::endl;
           return 1;
        }
        catch(LabrestAPI::ADCLoginTrue & ex)
        {
            ::std::cerr << "ADC Login" << ::std::endl;
           return 1;
        }
        IceUtil::Mutex::Lock sync(_mutex);
        
        
        
        _timer = new IceUtil::Timer();
        
        _timer->scheduleRepeated(new RefreshTask(communicator()->getLogger(), _session), IceUtil::Time::seconds(5));
    
        _session->ice_getConnection()->setAdapter(adapter);
        
        LabrestAPI::CallbackThreadCl cb_thread(communicator());
        
        cb_thread.start();
        
        ::LabrestAPI::CallbackManagerPrx CallBackMgr = _session->getCallbackManager();
        
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
            
//            if ((vector_command[0]=="reg")|| (vector_command[0] == "unreg")) 
//            vector_command.push_back(ident.name);   
               
            base_command * cmd = commands[vector_command[0]];
            if(cmd != NULL) 
            {
                bool shouldContinue;
                
                try
                {
                    shouldContinue = cmd->run(vector_command, _session);
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
                catch (LabrestAPI::ResourceIsLock & ex)
                {
                    ::std::cerr << "Resource already is locked!" << ::std::endl;
                    
                    shouldContinue = true;
                }
                if(!shouldContinue) 
                {
                    break;
                }
            }
            else
            {         
                if (vector_command[0]=="reg") CallBackMgr->registerCallback(ident);
                else 
                    if (vector_command[0]=="unreg") CallBackMgr->unregisterCallback(ident);
                    else
                        commands["help"]->run(vector_command, _session);
            }
	}
        for (::std::map<std::string, base_command*>::iterator it = commands.begin(); it!=commands.end(); ++it)
        {   
           delete[] (*it).second;
        }
                
    return status;
}
