#include "UserCommand.h"


void base_command::rightParameters(::std::vector<std::string> &parameters, int count)
{
    while (parameters.size()<count) 
    {
        parameters.erase(parameters.begin()+1,parameters.end());
        
        if (count != 1) 
        {
            ::std::cout << "Wrong number of parameters to this action! Please write parameters again:  \n" ;
            
            for (::std::vector<std::string>::iterator it = parameters.begin(); it != parameters.end();++it)
            {
                ::std::cout << (*it) << " " ;
            }
            ::std::string temp;
            
            getline(::std::cin, temp);
            
            ::std::stringstream ss(temp);
            
            while (ss.good())
            {
                ss >> temp;
                
                parameters.push_back(temp);
            }
        }
    }
        
}

bool
add_user_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    
    rightParameters(parameters,4);  
    
    ::std::stringstream s(parameters[3]);
    
    int group;
    
    s >> group;
    
    session->getUserManager()->addUser(parameters[1],parameters[2],group);
        
    return true;
}

bool
delete_user_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{  
    rightParameters(parameters,2);
    
   session->getUserManager()->deleteUser(parameters[1]);
   
   return true;
}

bool
all_users_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,1);
    
    ::LabrestAPI::UserList users;
         
    users = session->getUserManager()->getAllUsers();
        
    for (::LabrestAPI::UserList::iterator it = users.begin(); it != users.end(); it++)
    {
        ::LabrestAPI::User temp;
           
        temp = *it;
            
        ::std::cout <<  temp.name << " | " << temp.group << ::std::endl;
    };
    
    return true;
}

bool 
exit_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    return false;
}

bool 
help_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::std::cout<<" 1. help\n"
            " 2. exit\n"
            " 3. add_user <username> <password> <admin(1)/user(0)>\n"
            " 4. add_res <name> <description> <parent id> <type id>\n"
            " 5. add_restype <name> <description> <parent id>\n"
            " 6. delete_user <username>\n"
            " 7. delete_res <resource id>\n"
            " 8. delete_restype <resource type id>\n"
            " 9. change_user <username> password/group <new value>\n"
            "10. change_res <resource id> name/descr/type_id/parent_id <new value>\n"
            "11. change_restype <resource type id> name/descr/parent_id <new value>\n"
            "12. all_users\n"
            "13. all_res\n"
            "14. all_restypes\n"
            "15. lock_history\n"
            "16. lock_res <resource id> [<duration>]\n"
            "17. unlock_res <resource id>\n"
            "18. reg"
            "19. unreg";
    return true;
}


bool 
change_user_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{  
    rightParameters(parameters,4);
    
    ::std::map<std::string, base_change_user_command*>  func;
         
    func["password"] = new change_us_password();
    func["group"] = new change_us_group();
    
    base_change_user_command * f = func[parameters[2]];
    if(f != NULL) 
    {
        f->run(parameters, session);
    }
    
    for (::std::map<std::string, base_change_user_command*>::iterator it = func.begin(); it!=func.end(); ++it)
        {   
           delete[] (*it).second;
        }
        
    return true;
}


void change_us_password::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::User user;
         
    user = session->getUserManager()->getUser(parameters[1]);
    
    session->getUserManager()->modifyUser(user.name, parameters[3], user.group);
}

void change_us_group::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::User user;
         
    user = session->getUserManager()->getUser(parameters[1]);
    
    ::std::stringstream s(parameters[3]);
    
    int group;
    
    s >> group;
    
    session->getUserManager()->modifyUser(user.name, user.auth, group);
}


bool change_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,4);
    
    ::std::map<std::string, base_change_resource_command*>  func;
         
    func["name"] = new change_res_name();
    func["descr"] = new change_res_descr();
    func["type_id"] = new change_res_typeId();
    func["parent_id"] = new change_res_parentId();
    
    base_change_resource_command * f = func[parameters[2]];
    if(f != NULL) 
    {
        f->run(parameters, session);
    }
    
    for (::std::map<std::string, base_change_resource_command*>::iterator it = func.begin(); it!=func.end(); ++it)
    {   
        delete[] (*it).second;
    }
    
    return true;
}


void change_res_name::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{   
    ::LabrestAPI::Resource resource;
    
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
         
    resource = session->getResourceManager()->getResource(res_id);
    
    session->getResourceManager()->modifyResource(resource.id,parameters[3],resource.description,resource.parentId,resource.type);
}


void change_res_descr::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
     ::LabrestAPI::Resource resource;
    
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
         
    resource = session->getResourceManager()->getResource(res_id);
    
    session->getResourceManager()->modifyResource(resource.id,resource.name, parameters[3],resource.parentId,resource.type);
}


void change_res_typeId::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::Resource resource;
    
    ::std::stringstream s1(parameters[1]), s2(parameters[3]);
    
    int res_id, new_type_id;
    
    s1 >> res_id;
         
    resource = session->getResourceManager()->getResource(res_id);
    
    s2 >> new_type_id;
    
    session->getResourceManager()->modifyResource(resource.id,resource.name, resource.description,resource.parentId,session->getResourceManager()->getResourceType(new_type_id));
}


void change_res_parentId::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::Resource resource;
    
    ::std::stringstream s1(parameters[1]), s2(parameters[3]);
    
    int res_id, new_parent_id;
    
    s1 >> res_id;
         
    resource = session->getResourceManager()->getResource(res_id);
    
    s2 >> new_parent_id;
        
    session->getResourceManager()->modifyResource(resource.id,resource.name,resource.description,new_parent_id,resource.type);
}

bool add_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,5);
    
    ::std::stringstream s1(parameters[3]), s2(parameters[4]);
    
    int type_id, parent_id;
        
    s1 >> parent_id;
    
    s2 >> type_id; 

    session->getResourceManager()->addResource(parameters[1],parameters[2],parent_id, session->getResourceManager()->getResourceType(type_id));
    
    return true;
}


bool delete_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{    
    rightParameters(parameters,2);
    
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
    
   session->getResourceManager()->deleteResource(res_id);
   
   return true;
}


bool lock_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{       
    rightParameters(parameters,2);
    
    ::std::stringstream s1(parameters[1]); 
            
    int res_id, duration;
    
    s1 >> res_id;
    
    if (parameters.size() > 2)
    {
        ::std::stringstream s2(parameters[2]);
        
        s2 >> duration;
    }    
    else
    {
        duration = -1;
    }
    
    session->getResourceManager()->lockResource(res_id, duration);
    
    return true;
}

bool unlock_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,2);
    
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
    
   session->getResourceManager()->unlockResource(res_id);
   
   return true;
   
}

bool all_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,1);

    ::LabrestAPI::ResourceList resources;
         
    resources = session->getResourceManager()->getAllResources();
        
    for (::LabrestAPI::ResourceList::iterator it = resources.begin(); it != resources.end(); ++it)
    {
        ::LabrestAPI::Resource temp;
           
        temp = *it;
            
        time_t start = temp.resLockStatus.startTime;
        
        ::std::cout <<  temp.id << " | " << temp.name << " | " << temp.description
                << " || " << temp.resLockStatus.username << " | " ;
        if (temp.resLockStatus.startTime == -1) 
            ::std::cout << "" ; 
        else ::std::cout << ctime(&start) ;
        ::std::cout   << " || " << temp.type.id << " | " << temp.parentId << ::std::endl;
    };
    
    return true;
}

bool add_restype_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters, 4);
    
    ::std::stringstream s1(parameters[3]);
    
    int parent_id;   
        
    s1 >> parent_id;
    
    session->getResourceManager()->addResourceType(parameters[1],parameters[2],parent_id);
    
    return true;
}

bool delete_restype_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,2);
    
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
    
   session->getResourceManager()->deleteResourceType(res_id);
   
   return true;
}

bool change_restype_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,4);
    
    ::std::map<std::string, base_change_restype_command*>  func;
         
    func["name"] = new change_restype_name();
    func["descr"] = new change_restype_descr();
    func["parent_id"] = new change_restype_parentId();
    
    base_change_restype_command * f = func[parameters[2]];
    if(f != NULL) 
    {
        f->run(parameters, session);
    }
    
    for (::std::map<std::string, base_change_restype_command*>::iterator it = func.begin(); it!=func.end(); ++it)
    {   
        delete[] (*it).second;
    }
             
    return true;
}

void change_restype_name::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::ResourceType res_type;
    
    ::std::stringstream s(parameters[1]);
    
    int rest_id;
    
    s >> rest_id;
         
    res_type = session->getResourceManager()->getResourceType(rest_id);
    
    session->getResourceManager()->modifyResourceType(res_type.id,parameters[3],res_type.description,res_type.parentId);
}

void change_restype_descr::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
     ::LabrestAPI::ResourceType res_type;
    
    ::std::stringstream s(parameters[1]);
    
    int rest_id;
    
    s >> rest_id;
         
    res_type = session->getResourceManager()->getResourceType(rest_id);
    
    session->getResourceManager()->modifyResourceType(res_type.id,res_type.name, parameters[3],res_type.parentId);
}

void change_restype_parentId::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::ResourceType res_type;
    
    ::std::stringstream s1(parameters[1]), s2(parameters[3]);
    
    int rest_id, new_parent_id;
    
    s1 >> rest_id;
         
    res_type = session->getResourceManager()->getResourceType(rest_id);
    
    s2 >> new_parent_id;
        
    session->getResourceManager()->modifyResourceType(res_type.id,res_type.name,res_type.description,new_parent_id);
}

bool all_restype_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,1);

    ::LabrestAPI::ResourceTypeList restypes;
         
    restypes = session->getResourceManager()->getAllResourceTypes();
        
    for (::LabrestAPI::ResourceTypeList::iterator it = restypes.begin(); it != restypes.end(); ++it)
    {
        ::LabrestAPI::ResourceType temp;
           
        temp = *it;
            
        ::std::cout <<  temp.id << " | " << temp.name << " | " << temp.description << " | " << temp.parentId << ::std::endl;
    };
    
    return true;
}

bool lock_history_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    rightParameters(parameters,1);
    
    ::LabrestAPI::History history;
         
    history = session->getResourceManager()->getLockHistory();
        
    for (::LabrestAPI::History::iterator it = history.begin(); it != history.end(); ++it)
    {
        ::LabrestAPI::LockStatus temp;
           
        temp = *it;
        
        time_t start, end;
        
        start = temp.startTime;
        
        end = temp.endTime;
            
        ::std::cout <<  temp.id << " | " << temp.username << " | " << temp.resourceId 
                << " | " << ctime(&start) << " | " << temp.duration << " | " ;
        if (temp.endTime ==-1) ::std::cout << "";
        else ::std::cout << ctime(&end) ;
        ::std::cout<< " | " << temp.unlockComment << ::std::endl;
    };
    
    return true;
}
//
//bool reg_callback_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
//{    
//    Ice::Identity ident;
//    
//    ident.category="";
//    
//    ident.name=parameters[1];
//    
//    session->getCallbackManager()->registerCallback(ident);
//};
//
//bool unreg_callback_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
//{
//     Ice::Identity ident;
//    
//    ident.category="";
//    
//    ident.name=parameters[1];
//    
//    session->getCallbackManager()->unregisterCallback(ident);
//};
