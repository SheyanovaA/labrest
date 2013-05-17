
#include <map>

#include "UserCommand.h"
#include "LabrestAPI.h"

bool
add_user_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    if (!session->getUserManager()->addUser(parameters[1],parameters[2]))
    ::std::cout << "this user has not been added!\nUser with the name \"" << parameters[1] << "\" already exists!\n";
    
    return true;
}

bool
delete_user_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
   if (!session->getUserManager()->deleteUser(parameters[1]))

   ::std::cout << "this user has not been deleted!\nUser with the name \"" << parameters[1] << "\" does not exists!\n";
   
   return true;
}

bool
all_users_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::UserList users;
         
    users = session->getUserManager()->getAllUsers();
        
    for (::LabrestAPI::UserList::iterator it = users.begin(); it != users.end(); it++)
    {
        ::LabrestAPI::User temp;
           
        temp = *it;
            
        ::std::cout <<  temp.name << ::std::endl;
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
    ::std::cout<<":)"<<std::endl;
    return true;
}


bool 
change_user_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{  
    ::std::map<std::string, base_change_user_command*>  func;
         
    func["password"] = new change_us_password();
    
    base_change_user_command * f = func[parameters[2]];
    if(f != NULL) 
    {
        f->run(parameters, session);
    }
    
//    delete[] (func["password"]);
        
    return true;
}


void change_us_password::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::User user;
         
    user = session->getUserManager()->getUser(parameters[1]);
    
    ::std::cout << "old: " << user.name << ", " << user.auth << ::std::endl;
    
    session->getUserManager()->modifyUser(user.name, parameters[3]);
    
    user = session->getUserManager()->getUser(parameters[1]);
    
    ::std::cout << "new: " << user.name << ", " << user.auth << ::std::endl;
}

bool change_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::std::map<std::string, base_change_resource_command*>  func;
         
    func["name"] = new change_res_name();
    func["description"] = new change_res_descr();
    func["typeId"] = new change_res_typeId();
    func["parentId"] = new change_res_parentId();
    
    base_change_resource_command * f = func[parameters[2]];
    if(f != NULL) 
    {
        f->run(parameters, session);
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
    
    ::std::cout << "old: " << resource.id << ", " << resource.name << "change on: " << parameters[3] << ::std::endl;
    
    session->getResourceManager()->modifyResource(resource.id,parameters[3],resource.description,resource.parentId,resource.typeId);
    
    resource = session->getResourceManager()->getResource(res_id);
    
    ::std::cout << "new: " << resource.id << ", " << resource.name << ::std::endl;
}


void change_res_descr::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
     ::LabrestAPI::Resource resource;
    
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
         
    resource = session->getResourceManager()->getResource(res_id);
    
    ::std::cout << "old: " << resource.id << ", " << resource.name << ::std::endl;
    
    session->getResourceManager()->modifyResource(resource.id,resource.name, parameters[3],resource.parentId,resource.typeId);
    
    resource = session->getResourceManager()->getResource(res_id);
    
    ::std::cout << "new: " << resource.name << ", " << resource.name << ::std::endl;
}


void change_res_typeId::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::Resource resource;
    
    ::std::stringstream s(parameters[1]);
    
    int res_id, new_type_id;
    
    s >> res_id;
         
    resource = session->getResourceManager()->getResource(res_id);
    
    s.str(parameters[3]);
    
    s >> new_type_id;
    
    ::std::cout << "old: " << resource.id << ", " << resource.name << ::std::endl;
    
    session->getResourceManager()->modifyResource(resource.id,resource.name, resource.description,resource.parentId,new_type_id);
    
    resource = session->getResourceManager()->getResource(res_id);
    
    ::std::cout << "new: " << resource.name << ", " << resource.name << ::std::endl;
}


void change_res_parentId::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::Resource resource;
    
    ::std::stringstream s(parameters[1]);
    
    int res_id, new_parent_id;
    
    s >> res_id;
         
    resource = session->getResourceManager()->getResource(res_id);
    
    ::std::cout << "old: " << resource.id << ", " << resource.name << ::std::endl;
    
    s.str(parameters[3]);
    
    s >> new_parent_id;
        
    session->getResourceManager()->modifyResource(resource.id,resource.name,resource.description,new_parent_id,resource.typeId);
    
    resource = session->getResourceManager()->getResource(res_id);
    
    ::std::cout << "new: " << resource.name << ", " << resource.name << ::std::endl;
}

bool add_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::std::stringstream s1(parameters[3]), s2(parameters[4]);
    
    int type_id, parent_id;
    
    ::std::cout << parameters[4] << ::std::endl;
        
    s1 >> parent_id;
    
    s2 >> type_id;
    
    ::std::cout << type_id << ::std::endl;
    
    session->getResourceManager()->addResource(parameters[1],parameters[2],parent_id, type_id);
    
    return true;
}


bool delete_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
    
   if (!session->getResourceManager()->deleteResource(res_id))

   ::std::cout << "this resource has not been deleted!\nResource with id =" << parameters[1] << " does not exists!\n";
    
    return true;
}


bool lock_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{       
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
    
    if (!session->getResourceManager()->lockResource(res_id))

   ::std::cout << "this resource has not been locked!\n ";
   
   return true;
}

bool unlock_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
    
   session->getResourceManager()->unlockResource(res_id);
   
   return true;
   
}

bool all_resource_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{

    ::LabrestAPI::ResourceList resources;
         
    resources = session->getResourceManager()->getAllResources();
        
    for (::LabrestAPI::ResourceList::iterator it = resources.begin(); it != resources.end(); ++it)
    {
        ::LabrestAPI::Resource temp;
           
        temp = *it;
            
        ::std::cout <<  temp.id << ",   " << temp.name << ",   " << temp.description << ",   " << temp.lockStatus << ",   " << temp.typeId << ",   " << temp.parentId << ::std::endl;
    };
    
    return true;
}

bool add_restype_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::std::stringstream s1(parameters[3]);
    
    int parent_id;   
        
    s1 >> parent_id;
    
    session->getResourceManager()->addResourceType(parameters[1],parameters[2],parent_id);
    
    return true;
}

bool delete_restype_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::std::stringstream s(parameters[1]);
    
    int res_id;
    
    s >> res_id;
    
   if (!session->getResourceManager()->deleteResourceType(res_id))

   ::std::cout << "this resource type has not been deleted!\nResource type with id =" << parameters[1] << " does not exists!\n";
    
    return true;
}

bool change_restype_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::std::map<std::string, base_change_restype_command*>  func;
         
    func["name"] = new change_restype_name();
    func["description"] = new change_restype_descr();
    func["parentId"] = new change_restype_parentId();
    
    base_change_restype_command * f = func[parameters[2]];
    if(f != NULL) 
    {
        f->run(parameters, session);
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
    
    ::std::cout << "old: " << res_type.id << ", " << res_type.name << "change on: " << parameters[3] << ::std::endl;
    
    session->getResourceManager()->modifyResourceType(res_type.id,parameters[3],res_type.description,res_type.parentId);
    
    res_type = session->getResourceManager()->getResourceType(rest_id);
    
    ::std::cout << "new: " << res_type.id << ", " << res_type.name << ::std::endl;

}

void change_restype_descr::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
     ::LabrestAPI::ResourceType res_type;
    
    ::std::stringstream s(parameters[1]);
    
    int rest_id;
    
    s >> rest_id;
         
    res_type = session->getResourceManager()->getResourceType(rest_id);
    
    ::std::cout << "old: " << res_type.id << ", " << res_type.name << ::std::endl;
    
    session->getResourceManager()->modifyResourceType(res_type.id,res_type.name, parameters[3],res_type.parentId);
    
    res_type = session->getResourceManager()->getResourceType(rest_id);
    
    ::std::cout << "new: " << res_type.name << ", " << res_type.name << ::std::endl;

}

void change_restype_parentId::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{
    ::LabrestAPI::ResourceType res_type;
    
    ::std::stringstream s(parameters[1]);
    
    int rest_id, new_parent_id;
    
    s >> rest_id;
         
    res_type = session->getResourceManager()->getResourceType(rest_id);
    
    ::std::cout << "old: " << res_type.id << ", " << res_type.name << ::std::endl;
    
    s.str(parameters[3]);
    
    s >> new_parent_id;
        
    session->getResourceManager()->modifyResourceType(res_type.id,res_type.name,res_type.description,new_parent_id);
    
    res_type = session->getResourceManager()->getResourceType(rest_id);
    
    ::std::cout << "new: " << res_type.name << ", " << res_type.name << ::std::endl;

}

bool all_restype_command::run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session)
{

    ::LabrestAPI::ResourceTypeList restypes;
         
    restypes = session->getResourceManager()->getAllResourceTypes();
        
    for (::LabrestAPI::ResourceTypeList::iterator it = restypes.begin(); it != restypes.end(); ++it)
    {
        ::LabrestAPI::ResourceType temp;
           
        temp = *it;
            
        ::std::cout <<  temp.id << ",   " << temp.name << ",   " << temp.description << ",   " << temp.parentId << ::std::endl;
    };
    
    return true;
}

