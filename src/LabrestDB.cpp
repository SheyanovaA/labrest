#include "LabrestDB.h"


int LabrestAPI::LabrestDB::adc_pwd_check(const char * login, const char * password) {
    char cmd[256];
    int status;

    snprintf(cmd, 255, "smbclient -L adc.tecom.nnov.ru -U%s%%%s >/dev/null 2>&1", login, password);

    status = system(cmd);

    return status;
}



int LabrestAPI::LabrestDB::connect() 
{
//    ::std::cout << "LabrestDB::connect() called" << ::std::endl;
    
    int rc = sqlite3_open("labrest.db", &db);

    if(rc)
    {
        std::cout << "Can't open database\n";
    } 
    else 
    {
        std::cout << "Open database successfully\n";

        ::std::string sql[6];

        sql[0] = "create table if not exists user(username text primary key, "
                "authdata text, admin_group boolean);";

        sql[1] = "create table if not exists "
                "resource_type(id integer primary key autoincrement, "
                "name text, description, parent integer);";

        sql[2] = "create table if not exists "
                "resource(id integer primary key autoincrement,"
                " name text, description text, lock_status integer, "
                "type_id integer, parent integer);";

       sql[3] = "create table if not exists "
                "using_resource(id integer primary key autoincrement, "
                "username text, resource_id integer, start_time datetime, "
                "duration integer, end_time datetime, unlock_comment text);";

        //add test user 'us' with password '1':
        sql[4] = "insert or replace into user values('admin','admin','1');";
        sql[5] = "insert or replace into user values('guest','guest','0');";

         sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
        for (int i = 0; i < 6; i++)
        {
//            ::std::cout << sql[i] << ::std::endl;
                
            if (sqlite3_exec(db, sql[i].c_str(), 0, 0, &szErrMsg))
            {
                ::std::cout <<  "Ошибка SQL: " << &szErrMsg << ::std::endl;
                
                sqlite3_free(szErrMsg);
	    }
        }  
         sqlite3_exec(db, "COMMIT", 0, 0, 0);
    }
    return rc;
}

int LabrestAPI::LabrestDB::disconnect()
{
//    ::std::cout << "LabrestDB::disconnect() called" << ::std::endl;

    if(db)
    {

        std::cout << "Close database\n";

        sqlite3_close(db);
    }

    return 0;
}

LabrestAPI::LabrestDB::~LabrestDB() 
{
//    ::std::cout << "LabrestDB::~LabrestDB()  called" << ::std::endl;

    this->disconnect();

}

LabrestAPI::LabrestDB::LabrestDB() 
{
//    ::std::cout << "LabrestDB::LabrestDB()  called" << ::std::endl;
    
    this->connect();
}

bool 
LabrestAPI::LabrestDB::authUser(::std::string username, ::std::string authdate)
{
//    ::std::cout << "LabrestDB::authUser()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"select username from user where (username = ? ) "
            "and (authdata = ?);",-1,&ppStmt,0);

    sqlite3_bind_text(ppStmt, 1, username.c_str(), username.length(),NULL);

    sqlite3_bind_text(ppStmt, 2, authdate.c_str(), authdate.length(),NULL);

    if (sqlite3_step(ppStmt) == SQLITE_ROW) 
    {
        status = true;
    }
    else
    {
        status = false;
    };

    sqlite3_finalize(ppStmt);

    return status;
}


bool 
LabrestAPI::LabrestDB::existsUser(::std::string username)
{
//    ::std::cout << "LabrestDB::authUser()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"select username from user where (username = ? ) ",-1,&ppStmt,0);

    sqlite3_bind_text(ppStmt, 1, username.c_str(), username.length(),NULL);

    if (sqlite3_step(ppStmt) == SQLITE_ROW) 
    {
        status = true;
    }
    else
    {
        status = false;
    };

    sqlite3_finalize(ppStmt);

    return status;
}

bool LabrestAPI::LabrestDB::addUser(::std::string username, ::std::string authdate, int group)
{
//    ::std::cout << "LabrestDB::addUser()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"insert into user values(?,?,?);",-1,&ppStmt,0);

    sqlite3_bind_text(ppStmt, 1, username.c_str(), username.length(),NULL);

    sqlite3_bind_text(ppStmt, 2, authdate.c_str(), authdate.length(),NULL);
    
    sqlite3_bind_int(ppStmt, 3, group);

    if (sqlite3_step(ppStmt) == SQLITE_DONE)
    {
	status = true;
    }
    else
    {
	status = false;
    }
    sqlite3_finalize(ppStmt);

    return status;
}

bool LabrestAPI::LabrestDB::deleteUser(::std::string username)
{
//    ::std::cout << "LabrestDB::deleteUser()  called" << ::std::endl;
    
    bool status;
    int s;

    sqlite3_stmt *ppStmt;

    s = sqlite3_prepare(db,"delete from user where username = ?;",-1,&ppStmt,0);
    
    sqlite3_bind_text(ppStmt, 1, username.c_str(), username.length(),NULL);

    if (sqlite3_step(ppStmt) == SQLITE_DONE)
    {
	status = true;
    }
    else
    {
	status = false;
    }
    sqlite3_finalize(ppStmt);

    return status;
}

bool LabrestAPI::LabrestDB::modifyUser(::std::string username, ::std::string authdata, int group)
{
//    ::std::cout << "LabrestDB::modifyUser()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"update user set authdata = ?, admin_group=? "
            " where username = ?;",-1,&ppStmt,0);
    
    sqlite3_bind_text(ppStmt, 3, username.c_str(), username.length(),NULL);

    sqlite3_bind_text(ppStmt, 1, authdata.c_str(), authdata.length(),NULL);
    
    sqlite3_bind_int(ppStmt, 2, group);

    if (sqlite3_step(ppStmt) == SQLITE_DONE)
    {
	status = true;
    }
    else
    {
	status = false;
    }
    sqlite3_finalize(ppStmt);

    return status;
}


int  LabrestAPI::LabrestDB::addResourse(::std::string name, ::std::string description, int typeId, int parentId)
{
//    ::std::cout << "LabrestDB::addResourse()  called" << ::std::endl;
    
    bool status, stat2;
    
    int id;

    sqlite3_stmt *ppStmt;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    if (parentId != -1) 
    {
        status = ExistsResource(parentId);
    }
    stat2 = ExistsResourceType(typeId);
    
    if (status && stat2)
    { 
        sqlite3_prepare(db,"insert into resource(name, description, type_id, "
            "lock_status, parent) values(?, ?, ?, ?, ?);",-1,&ppStmt,0);

        sqlite3_bind_text(ppStmt, 1, name.c_str(), name.length(),NULL);

        sqlite3_bind_text(ppStmt, 2, description.c_str(), description.length(),NULL);

        sqlite3_bind_int(ppStmt, 3, typeId);
    
        sqlite3_bind_null(ppStmt, 4);
    
        if (parentId == -1) sqlite3_bind_null(ppStmt, 5);
        else  sqlite3_bind_int(ppStmt, 5, parentId);

        if (sqlite3_step(ppStmt) == SQLITE_DONE)
        {
            status = true;
        }
        else
        {
            status = false;
        }
        sqlite3_finalize(ppStmt);
        
        if (status)
        {
             sqlite3_prepare(db,"select max(id) from resource;",-1,&ppStmt,0);

        if (sqlite3_step(ppStmt) == SQLITE_ROW)
        {       
            id = sqlite3_column_int(ppStmt,0);
            
            status = true;
        }
        else
        {
            status = false;
        }
        sqlite3_finalize(ppStmt);
        }
      
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
    }
    else 
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::InvalidValue iv;
        
        iv.ice_throw();
    }
    return id;
}

bool LabrestAPI::LabrestDB::deleteResource(int id)
{
//    ::std::cout << "LabrestDB::deleteResource()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    sqlite3_prepare(db,"update resource set parent = ? where parent = ?;",-1,&ppStmt,0);
    
    sqlite3_bind_null(ppStmt,1);

    sqlite3_bind_int(ppStmt, 2, id);

    if (sqlite3_step(ppStmt) == SQLITE_DONE)
    {
	status = true;
    }
    else
    {
	status = false;
    }
    sqlite3_finalize(ppStmt);

    sqlite3_prepare(db,"delete from resource where id = ?;",-1,&ppStmt,0);

    sqlite3_bind_int(ppStmt, 1, id);

    if (sqlite3_step(ppStmt) == SQLITE_DONE)
    {
	status = true;
    }
    else
    {
	status = false;
    }
    sqlite3_finalize(ppStmt);
    
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    return status;

}

bool LabrestAPI::LabrestDB::modifyResource(int id, ::std::string name, ::std::string description, int typeId, int parentId)
{
//    ::std::cout << "LabrestDB::modifyResource()  called" << ::std::endl;
   
    bool status, stat2;

    sqlite3_stmt *ppStmt;
    
    if (parentId != -1) 
    {
        status = ExistsResource(parentId);
    }
    stat2 = ExistsResourceType(typeId);

    if (status && stat2)
    { 
        sqlite3_prepare(db,"update resource set name = ?, description = ?, "
            "type_id = ?, parent = ?   where id = ?;",-1,&ppStmt,0);

        sqlite3_bind_text(ppStmt, 1, name.c_str(), name.length(),NULL);

        sqlite3_bind_text(ppStmt, 2, description.c_str(), description.length(),NULL);
    
        sqlite3_bind_int(ppStmt,3,typeId);
    
        sqlite3_bind_int(ppStmt, 4, parentId);
    
        sqlite3_bind_int(ppStmt, 5, id);

        if (sqlite3_step(ppStmt) == SQLITE_DONE)
        {
            status = true;
        }
        else
        {
            status = false;
        }
        sqlite3_finalize(ppStmt);
        
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
    }
    else 
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::InvalidValue iv;
        
        iv.ice_throw();
    }
}


int  LabrestAPI::LabrestDB::addResourceType(::std::string name, ::std::string description, int parentId)
{
//    ::std::cout << "LabrestDB::addResourceType()  called" << ::std::endl;
    
    bool status = true;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    if (parentId != -1) 
    {
        status = ExistsResourceType(parentId);
    }
    if (status)
    { 
        sqlite3_stmt *ppStmt;

        sqlite3_prepare(db,"insert into resource_type(name, description, parent) "
            "values(?,?,?);",-1,&ppStmt,0);

        sqlite3_bind_text(ppStmt, 1, name.c_str(), name.length(),NULL);

        sqlite3_bind_text(ppStmt, 2, description.c_str(), description.length(),NULL);
    
        if (parentId == -1) sqlite3_bind_null(ppStmt,3);
        else    sqlite3_bind_int(ppStmt, 3, parentId);

        if (sqlite3_step(ppStmt) == SQLITE_DONE)
        {
            status = true;
        }
        else
        {
            status = false;
        }
        sqlite3_finalize(ppStmt);
        
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
    }
    else 
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::InvalidValue iv;
        
        iv.ice_throw();
    }
    return status;

}

bool LabrestAPI::LabrestDB::deleteResourceType(int id)
{
//    ::std::cout << "LabrestDB::deleteResourceType()  called" << ::std::endl;
    
    bool status;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    sqlite3_stmt *ppStmt;
    
    sqlite3_prepare(db,"update resource set type_id = ? where type_id = ?;",-1,&ppStmt,0);

    sqlite3_bind_null(ppStmt,1);
    
    sqlite3_bind_int(ppStmt, 2, id);
    
//    sqlite3_prepare(db,"delete from resource where type_id = ?;",-1,&ppStmt,0);
//    
//    sqlite3_bind_int(ppStmt, 1, id);

    if (sqlite3_step(ppStmt) == SQLITE_DONE)
    {
	status = true;
    }
    else
    {
	status = false;
    }
    sqlite3_finalize(ppStmt);
    
    sqlite3_prepare(db,"update resource_type set parent = ? where parent = ?;",-1,&ppStmt,0);

    sqlite3_bind_null(ppStmt,1);
    
    sqlite3_bind_int(ppStmt, 2, id);

    if (sqlite3_step(ppStmt) == SQLITE_DONE)
    {
	status = true;
    }
    else
    {
	status = false;
    }
    sqlite3_finalize(ppStmt);

    if (status)
    {
        sqlite3_prepare(db,"delete from resource_type "
            "where id = ?;",-1,&ppStmt,0);
        
        sqlite3_bind_int(ppStmt, 1, id);

        if (sqlite3_step(ppStmt) == SQLITE_DONE)
        {
            status = true;
        }
        else
        {
            status = false;
        }
        sqlite3_finalize(ppStmt);
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    
    return status;

}

bool LabrestAPI::LabrestDB::modifyResourceType(int id, ::std::string name, ::std::string description, int parentId)
{
//    ::std::cout << "LabrestDB::modifyResourceType()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;
        
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    if (parentId != -1) 
    {
        status = ExistsResourceType(parentId);
    }
    if (status)
    {            
    sqlite3_prepare(db,"update resource_type set name = ?, "
            "description = ?, parent = ? where id = ?;",-1,&ppStmt,0);
        
    sqlite3_bind_text(ppStmt, 1, name.c_str(), name.length(),NULL);

    sqlite3_bind_text(ppStmt, 2, description.c_str(), description.length(),NULL);

    sqlite3_bind_int(ppStmt, 3, parentId);

    sqlite3_bind_int(ppStmt, 4, id);

    if (sqlite3_step(ppStmt) == SQLITE_DONE)
    {
	status = true;
    }
    else
    {
	status = false;
    }
    sqlite3_finalize(ppStmt);
        
    sqlite3_exec(db, "COMMIT", 0, 0, 0);
    }
    else
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::InvalidValue iv;
        
        iv.ice_throw();
    }
    sqlite3_finalize(ppStmt);
    
    return status;
    
}

bool LabrestAPI::LabrestDB::ResourceIsNotLock(int resourceId)
{
//    ::std::cout << "LabrestDB::ResourceIsLock()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;
    
    sqlite3_prepare(db,"select * from resource where id = ? and "
            "lock_status isnull;",-1,&ppStmt,0);

    sqlite3_bind_int(ppStmt, 1, resourceId);

    if (sqlite3_step(ppStmt) == SQLITE_ROW)
    {
	status = true;
    }
    else
    {
	status = false;
        
    }
    sqlite3_finalize(ppStmt);
    
    if (status) 
    {
                sqlite3_prepare(db,"select id from resource where parent = ?;" ,-1,&ppStmt,0);
                                
                sqlite3_bind_int(ppStmt, 1, resourceId);
                
                while (sqlite3_step(ppStmt) == SQLITE_ROW)
                {
                    status = ResourceIsNotLock(sqlite3_column_int(ppStmt,0));
                                        
                    if (!status) break;
                }
                sqlite3_finalize(ppStmt);
    }
       
    return status;
}

bool LabrestAPI::LabrestDB::lockResourse(int resourceId, ::std::string username, int duration)
{
//    ::std::cout << "LabrestDB::lockResourse()  called" << ::std::endl;
    
    bool status;
    
    int lock_st_id; 

    sqlite3_stmt *ppStmt;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    if (ExistsResource(resourceId))
    {    
    if (ResourceIsNotLock(resourceId))
    {
        sqlite3_prepare(db,"insert into using_resource(username,resource_id, "
                "start_time, duration, end_time) "
               "values(?,?,datetime(), ?, ?);" ,-1,&ppStmt,0);
       
        sqlite3_bind_text(ppStmt,1,username.c_str(),username.length(),NULL);

        sqlite3_bind_int(ppStmt, 2, resourceId);
        
        if (duration == -1) sqlite3_bind_null(ppStmt,3);
            else sqlite3_bind_int(ppStmt, 3, duration);
        
        sqlite3_bind_null(ppStmt,4);
        
        if (sqlite3_step(ppStmt) == SQLITE_DONE)
        {
            status = true;
        }
        else
        {
            status = false;
        }
        sqlite3_finalize(ppStmt);
    
        if (status)
         
            {
                sqlite3_prepare(db,"update resource set lock_status = "
                        "(select id from using_resource where "
                     "resource_id = ? and end_time isnull)"
                        " where id = ?;" ,-1,&ppStmt,0);
                
                sqlite3_bind_int(ppStmt, 1, resourceId);
                
                sqlite3_bind_int(ppStmt, 2, resourceId);
                
                if (sqlite3_step(ppStmt) == SQLITE_DONE)
                {
                    status = true;
                }
                else
                {
                    status = false;
                }
                sqlite3_finalize(ppStmt);
                
                sqlite3_prepare(db,"select id from resource where parent = ?;" ,-1,&ppStmt,0);
                                
                sqlite3_bind_int(ppStmt, 1, resourceId);
                
                while (sqlite3_step(ppStmt) == SQLITE_ROW)
                {
                    lockResourse(sqlite3_column_int(ppStmt,0), username, duration);
                }
                sqlite3_finalize(ppStmt);          
        }
        
        CB_Event ev;
    
        ev.TypeEvent = CB_LOCK;
        ev.id = (EvQueuePtr->empty())? 1 : EvQueuePtr->back().id+1;
        ev.resourceId = resourceId;
        ev.username = "";
    
        EvQueuePtr->push_back(ev);
        
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
    }
    else
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::ResourceIsLock rl;
        
        rl.ice_throw();
    }
    }
    else
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::InvalidValue iv;
        
        iv.ice_throw();
    }
    
    return status;
}

bool LabrestAPI::LabrestDB::unlockResource(int resourceId, ::std::string username)
{
//    ::std::cout << "LabrestDB::unlockResource()  called" << ::std::endl;
        
    bool status;
    
    sqlite3_stmt *ppStmt;

    sqlite3_exec(db, "BEGIN", 0, 0, 0);
    
    if (ExistsResource(resourceId))
    {  
        if (ResourceIsLockByUser(resourceId, username))
        {
            sqlite3_prepare(db,"update using_resource set end_time = datetime(), "
                    "unlock_comment = ?"
                    " where id = (select lock_status from resource "
                    " where id = ?);",-1,&ppStmt,0);
        
            ::std::string tuser = ((dbPtr->getUser(username).group == 1)&&(dbPtr->getResource(resourceId).resLockStatus.username!= username)) ?  username + " as admin" :    username;        
            ::std::string unlock_comment = (username == "system") ? "Timeout expired" : tuser;
            
            
    ::std::cout << unlock_comment << ::std::endl;
            
            sqlite3_bind_text(ppStmt, 1, unlock_comment.c_str(),unlock_comment.length(),NULL);
            
            sqlite3_bind_int(ppStmt, 2, resourceId);
    
            if (sqlite3_step(ppStmt) == SQLITE_DONE)
            {
                status = true;
            }
            else
            {
                status = false;
            }
            sqlite3_finalize(ppStmt);
      
            sqlite3_prepare(db,"update resource set lock_status = ? "
            " where id = ?;",-1,&ppStmt,0);
    
            sqlite3_bind_null(ppStmt,  1);

            sqlite3_bind_int(ppStmt, 2, resourceId);

            if (sqlite3_step(ppStmt) == SQLITE_DONE)
            {
                status = true;
            }
            else
            {
                status = false;
            }
            sqlite3_finalize(ppStmt);
    
            if (status)
            {
               sqlite3_prepare(db,"select id from resource where parent = ?;" ,-1,&ppStmt,0);
                                
                sqlite3_bind_int(ppStmt, 1, resourceId);
                
                while (sqlite3_step(ppStmt) == SQLITE_ROW)
                {
                    unlockResource(sqlite3_column_int(ppStmt,0), username);
                }
                sqlite3_finalize(ppStmt);  
            };
        }
        CB_Event ev;
    
        ev.TypeEvent = CB_UNLOCK;
        ev.id = (EvQueuePtr->empty())? 1 : EvQueuePtr->back().id+1;
        ev.resourceId = resourceId;
        ev.username = "";
    
        EvQueuePtr->push_back(ev);
        
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
    }                   
    else
    {
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        ::LabrestAPI::InvalidValue iv;
        
        iv.ice_throw();
    }
    return status;
}

::LabrestAPI::UserList
LabrestAPI::LabrestDB::getAllUsers()
{
//    ::std::cout << "LabrestDB::getAllUsers()  called" << ::std::endl;
    
    int s;
    
    ::LabrestAPI::UserList users;
    
    sqlite3_stmt * ppStmt;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);

    sqlite3_prepare(db,"select username from user;",-1,&ppStmt,0);

    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        ::LabrestAPI::User temp_user =  getUser(reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 0)));
       
        users.push_back(temp_user);

        s = sqlite3_step(ppStmt);
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    return users;
}

::LabrestAPI::User
LabrestAPI::LabrestDB::getUser(::std::string username)
{    
//    ::std::cout << "LabrestDB::getUser() called" << ::std::endl;
    
    int s;
    
    ::LabrestAPI::User user;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from user where username = ?;",-1,&ppStmt,0);
    
    sqlite3_bind_text(ppStmt, 1, username.c_str(), username.length(), NULL);
    s = sqlite3_step(ppStmt);
    
    if (s == SQLITE_ROW)
    {
        user.name = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 0)));
        
        user.auth = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        
        user.group = sqlite3_column_int(ppStmt,2);
    }

    return user;
}

::LabrestAPI::ResourceList
LabrestAPI::LabrestDB::getAllResources()
{
//    ::std::cout << "LabrestDB::getAllResources() called" << ::std::endl;
   
    int s;
    
    ::LabrestAPI::ResourceList resources; 
    sqlite3_stmt * ppStmt;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);

    sqlite3_prepare(db,"select id from resource;",-1,&ppStmt,0);

    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        ::LabrestAPI::Resource temp_resource = getResource(sqlite3_column_int(ppStmt, 0));
        
        resources.push_back(temp_resource);

        s = sqlite3_step(ppStmt);
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    return resources;
}
        

::LabrestAPI::Resource 
LabrestAPI::LabrestDB::getResource(int id)
{
    int s;
    
    ::LabrestAPI::Resource resource;
    
//    ::std::cout << "LabrestDB::getResource() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from resource where id = ? ;",-1,&ppStmt,0);
    
    sqlite3_bind_int(ppStmt, 1, id);

    s = sqlite3_step(ppStmt);
    
    if  (s == SQLITE_ROW)
    {
        resource.id = sqlite3_column_int(ppStmt, 0);
        
        resource.name = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        
        resource.description = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 2)));
        
        resource.resLockStatus = getLockStatus(sqlite3_column_int(ppStmt, 3));
        
        resource.type = getResourceType(sqlite3_column_int_or_null(ppStmt, 4));
        
        resource.parentId = sqlite3_column_int_or_null(ppStmt, 5);    
  
    }

    return resource;
}

::LabrestAPI::ResourceTypeList
LabrestAPI::LabrestDB::getAllResourceTypes()
{ 
    int s;
    
    ::LabrestAPI::ResourceTypeList resource_types;
    
//    ::std::cout << "LabrestDB::getAllResourceTypes() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);

    sqlite3_prepare(db,"select id from resource_type;",-1,&ppStmt,0);

    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        ::LabrestAPI::ResourceType temp_resource_type = getResourceType(sqlite3_column_int(ppStmt, 0));
        
        resource_types.push_back(temp_resource_type);

        s = sqlite3_step(ppStmt);
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    return resource_types;
    
}
        
        
::LabrestAPI::ResourceType 
LabrestAPI::LabrestDB::getResourceType(int id)
{
    int s;
    
    ::LabrestAPI::ResourceType resource_type;
    
//    ::std::cout << "LabrestDB::getResourceType() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from resource_type where id = ? ;",-1,&ppStmt,0);
    
    sqlite3_bind_int(ppStmt, 1, id);

    s = sqlite3_step(ppStmt);
    
    if  (s == SQLITE_ROW)
    {
        resource_type.id = sqlite3_column_int(ppStmt, 0);
        
        resource_type.name = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        
        resource_type.description = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 2)));
        
        resource_type.parentId = sqlite3_column_int_or_null(ppStmt, 3);      
    }

    return resource_type;
}

::LabrestAPI::History 
LabrestAPI::LabrestDB::getLockHistry()
{
    int s;
    
    ::LabrestAPI::History lock_history;
    
//    ::std::cout << "LabrestDB::getLockHistry() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;
    
    sqlite3_exec(db, "BEGIN", 0, 0, 0);

    sqlite3_prepare(db,"select id from using_resource;",-1,&ppStmt,0);
    
    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        ::LabrestAPI::LockStatus temp_row = getLockStatus(sqlite3_column_int(ppStmt, 0));

        lock_history.push_back(temp_row);

        s = sqlite3_step(ppStmt);
    }
    sqlite3_exec(db, "COMMIT", 0, 0, 0);

    return lock_history;
}

const unsigned char *
LabrestAPI::LabrestDB::sqlite3_column_text_or_null(sqlite3_stmt * stmt, int iCol, const char * default_value /* = "" */) 
{
    if(sqlite3_column_type(stmt, iCol) == SQLITE_NULL) 
    {
        return reinterpret_cast<const unsigned char *>(default_value);
    }
    return sqlite3_column_text(stmt, iCol);
}

        
int 
LabrestAPI::LabrestDB::sqlite3_column_int_or_null(sqlite3_stmt * stmt, int iCol, int default_value /* = -1 */)
{
    if(sqlite3_column_type(stmt, iCol) == SQLITE_NULL) 
    {
        return default_value;
    }
    return sqlite3_column_int(stmt, iCol);
}

::LabrestAPI::LockStatus 
LabrestAPI::LabrestDB::getLockStatus(int Id)
{
    int s;
    
    ::LabrestAPI::LockStatus temp;
    
    temp.startTime = -1;
    
//    ::std::cout << "LabrestDB::getLockStatus() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select id, username, resource_id, strftime('%s',start_time), duration, strftime('%s',end_time), unlock_comment from using_resource where id = ?;",-1,&ppStmt,0);
    
    sqlite3_bind_int(ppStmt, 1, Id);
    
    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        temp.id = sqlite3_column_int(ppStmt, 0);
        
        temp.username = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        
        temp.resourceId = sqlite3_column_int(ppStmt, 2);
        
        temp.startTime = sqlite3_column_int(ppStmt, 3);
         
        temp.duration = sqlite3_column_int_or_null(ppStmt,4);
        
        temp.endTime = sqlite3_column_int_or_null(ppStmt, 5);
        
        temp.unlockComment = (reinterpret_cast<const char *>(sqlite3_column_text_or_null(ppStmt, 6)));

        s = sqlite3_step(ppStmt);
    }

    return temp;
}
        
bool 
::LabrestAPI::LabrestDB::ExistsResourceType(int resTypeId)
{
//    ::std::cout << "LabrestDB::ExistResourceType()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"select * from resource_type where id = ?;",-1,&ppStmt,0);

    sqlite3_bind_int(ppStmt, 1,resTypeId);

    if (sqlite3_step(ppStmt) == SQLITE_ROW) 
    {
        status = true;
    }
    else
    {
        status = false;
    };

    sqlite3_finalize(ppStmt);

    return status;
}
        
        
bool 
::LabrestAPI::LabrestDB::ExistsResource(int resourceId)
{
//    ::std::cout << "LabrestDB::ExistResourceType()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"select * from resource where id = ?;",-1,&ppStmt,0);

    sqlite3_bind_int(ppStmt, 1,resourceId);

    if (sqlite3_step(ppStmt) == SQLITE_ROW) 
    {
        status = true;
    }
    else
    {
        status = false;
    };

    sqlite3_finalize(ppStmt);

    return status;
}

bool 
::LabrestAPI::LabrestDB::ResourceIsLockByUser(int resourceId, ::std::string username)
{    
    return (username == "system") ||
            (dbPtr->getUser(username).group == 1) ||
            (dbPtr->getResource(resourceId).resLockStatus.username == username);
}

