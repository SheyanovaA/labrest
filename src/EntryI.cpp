#include "EntryI.h"


template<class T>
std::string t_to_string(T i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

int LabrestAPI::EntryI::adc_pwd_check(const char * login, const char * password) {
    
    std::cout << "EntryI::adc_pwd_check() called" << std::endl;
    char cmd[256];
    int status;

    snprintf(cmd, 255, "smbclient -L adc.tecom.nnov.ru -U'%s'%%'%s' >/dev/null 2>&1", login, password);

    status = system(cmd);

    return status;
}




::LabrestAPI::EntryI::EntryI(const ReapTaskPtr& reapTask) :
    _reaper(reapTask), 
    index(0)
{
    std::cout << "EntryI::EntryI() called" << std::endl;
}

::LabrestAPI::SessionPrx
LabrestAPI::EntryI::login(const ::std::string& username, const ::std::string& auth, const ::Ice::Current& current) 
{
	::LabrestAPI::SessionPrx SessionProxy;
	::std::string sessionId = "SimpleSession" + username + t_to_string(index++);
	std::cout<<"---"<<sessionId<<std::endl;

    std::cout << "EntryI::login() called" << std::endl;
    if (!dbPtr->authUser(username, auth))
    {
        if (!adc_pwd_check(username.c_str(), auth.c_str()) == 0)
        {
            LoginException le;
            le.ice_throw();
        } 
        else 
        {
            if (!dbPtr->existsUser(username)) 
            {
                dbPtr->addUser(username, "__", 0);
            };
              
        }
    }

	std::cout<<"----"<<sessionId<<std::endl;

    ::std::cout<<"EntryI::login() called"<<::std::endl;

    ::LabrestAPI::SessionIPtr object = new ::LabrestAPI::SessionI(sessionId, username);

    SessionProxy = ::LabrestAPI::SessionPrx::checkedCast(current.adapter->add(object, current.adapter->getCommunicator()->stringToIdentity(sessionId)));

	std::cout<<"-----"<<sessionId<<std::endl;

    _reaper->add(SessionProxy, object);
    
	return SessionProxy;
}
