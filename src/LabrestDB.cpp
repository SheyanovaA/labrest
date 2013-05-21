#include "LabrestDB.h"

int LabrestAPI::LabrestDB::connect() 
{
    ::std::cout << "LabrestDB::connect() called" << ::std::endl;
    
    int rc = sqlite3_open("labrest.db", &db);

    if(rc)
    {
        std::cout << "Can't open database\n";
    } 
    else 
    {
        std::cout << "Open database successfully\n";

        ::std::string sql[5];

        sql[0] = "create table if not exists user(username text primary key, "
                "authdata text);";

        sql[1] = "create table if not exists "
                "resource_type(id integer primary key autoincrement, "
                "name text, description, parent integer);";

        sql[2] = "create table if not exists "
                "resource(id integer primary key autoincrement,"
                " name text, description text, lock_status boolean, type_id integer, parent integer);";

       sql[3] = "create table if not exists "
                "using_resource(id integer primary key autoincrement, "
                "username text, resource_id integer, start_time datetime, "
                "end_time datetime);";

        //add test user 'us' with password '1':
        sql[4] = "insert or replace into user values('us','1');";

    
        for (int i = 0; i < 5; i++)
        {
            if (sqlite3_exec(db, sql[i].c_str(), 0, 0, &szErrMsg))
            {
                ::std::cout <<  "Ошибка SQL: " << &szErrMsg << ::std::endl;

                sqlite3_free(szErrMsg);
	    }
        }  
    }
    return rc;
}

int LabrestAPI::LabrestDB::disconnect()
{
    ::std::cout << "LabrestDB::disconnect() called" << ::std::endl;

    if(db)
    {

        std::cout << "Close database\n";

        sqlite3_close(db);
    }

    return 0;
}

LabrestAPI::LabrestDB::~LabrestDB() 
{
    ::std::cout << "LabrestDB::~LabrestDB()  called" << ::std::endl;

    this->disconnect();

}

LabrestAPI::LabrestDB::LabrestDB() 
{
    ::std::cout << "LabrestDB::LabrestDB()  called" << ::std::endl;
    
    this->connect();
}

bool LabrestAPI::LabrestDB::existsUser(::std::string username, ::std::string authdate)
{
    ::std::cout << "LabrestDB::existsUser()  called" << ::std::endl;
    
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

bool LabrestAPI::LabrestDB::addUser(::std::string username, ::std::string authdate)
{
    ::std::cout << "LabrestDB::addUser()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"insert into user values(?,?);",-1,&ppStmt,0);

    sqlite3_bind_text(ppStmt, 1, username.c_str(), username.length(),NULL);

    sqlite3_bind_text(ppStmt, 2, authdate.c_str(), authdate.length(),NULL);

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
    ::std::cout << "LabrestDB::deleteUser()  called" << ::std::endl;
    
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

bool LabrestAPI::LabrestDB::modifyUser(::std::string username, ::std::string authdata)
{
    ::std::cout << "LabrestDB::modifyUser()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"update user set authdata = ? where username = ?;",-1,&ppStmt,0);
    
    

    sqlite3_bind_text(ppStmt, 2, username.c_str(), username.length(),NULL);

    sqlite3_bind_text(ppStmt, 1, authdata.c_str(), authdata.length(),NULL);

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
    ::std::cout << "LabrestDB::addResourse()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

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

    return status;
}

bool LabrestAPI::LabrestDB::deleteResource(int id)
{
    ::std::cout << "LabrestDB::deleteResource()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

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

    return status;

}

bool LabrestAPI::LabrestDB::modifyResource(int id, ::std::string name, ::std::string description, int typeId, int parentId)
{
    ::std::cout << "LabrestDB::modifyResource()  called" << ::std::endl;
   
    bool status;

    sqlite3_stmt *ppStmt;

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
}


int  LabrestAPI::LabrestDB::addResourceType(::std::string name, ::std::string description, int parentId)
{
    ::std::cout << "LabrestDB::addResourceType()  called" << ::std::endl;
    
    bool status;

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

    return status;

}

bool LabrestAPI::LabrestDB::deleteResourceType(int id)
{
    ::std::cout << "LabrestDB::deleteResourceType()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

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

    return status;

}

bool LabrestAPI::LabrestDB::modifyResourceType(int id, ::std::string name, ::std::string description, int parentId)
{
    ::std::cout << "LabrestDB::modifyResourceType()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

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

    return status;
    
}

bool LabrestAPI::LabrestDB::ResourceIsLock(int resourceId)
{
    ::std::cout << "LabrestDB::ResourceIsLock()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;
    
    sqlite3_prepare(db,"select * from using_resource where resource_id = ? "
            "and end_time isnull;",-1,&ppStmt,0);

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
    
    return status;
}

bool LabrestAPI::LabrestDB::lockResourse(int resourceId, ::std::string username)
{
    ::std::cout << "LabrestDB::lockResourse()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;
    
    if (!ResourceIsLock(resourceId))
    {
        sqlite3_prepare(db,"update resource set lock_status = ? "
            "where id = ?;",-1,&ppStmt,0);
        
        sqlite3_bind_int(ppStmt,  1, 1);
        
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
            sqlite3_prepare(db,"insert into using_resource(username,resource_id, "
                "start_time, end_time) values(?,?,datetime(), ?);" ,-1,&ppStmt,0);
    
            sqlite3_bind_text(ppStmt,1,username.c_str(),username.length(),NULL);
            
            sqlite3_bind_int(ppStmt, 2, resourceId);
            
            sqlite3_bind_null(ppStmt, 3);
            
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
    }
    
    return status;
}

bool LabrestAPI::LabrestDB::unlockResource(int resourceId)
{
    ::std::cout << "LabrestDB::unlockResource()  called" << ::std::endl;
    
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"update resource set lock_status = ? "
            " where id = ?;",-1,&ppStmt,0);
        
    sqlite3_bind_int(ppStmt,  1, 0);

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
        sqlite3_prepare(db,"update using_resource set end_time = datetime()"
            " where (resource_id = ?) and end_time isnull ;",-1,&ppStmt,0);
        
        sqlite3_bind_int(ppStmt, 1, resourceId);
    
        sqlite3_bind_null(ppStmt, 2);
    
        if (sqlite3_step(ppStmt) == SQLITE_DONE)
        {
                status = true;
        }
        else
        {
                status = false;
        }
        sqlite3_finalize(ppStmt);
    };

    return status;
}

::LabrestAPI::UserList
LabrestAPI::LabrestDB::getAllUsers()
{
    ::std::cout << "LabrestDB::getAllUsers()  called" << ::std::endl;
    
    int s;
    
    ::LabrestAPI::UserList users;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from user;",-1,&ppStmt,0);

    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        ::LabrestAPI::User temp_user;
        
        temp_user.name = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 0)));
        temp_user.auth = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        
        users.push_back(temp_user);

        s = sqlite3_step(ppStmt);
    }

    return users;
}

::LabrestAPI::User
LabrestAPI::LabrestDB::getUser(::std::string username)
{    
    ::std::cout << "LabrestDB::getUser() called" << ::std::endl;
    
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
    }

    return user;
}

::LabrestAPI::ResourceList
LabrestAPI::LabrestDB::getAllResources()
{
    ::std::cout << "LabrestDB::getAllResources() called" << ::std::endl;
   
    int s;
    
    ::LabrestAPI::ResourceList resources; 
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from resource;",-1,&ppStmt,0);

    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        ::LabrestAPI::Resource temp_resource;
        
        temp_resource.id = sqlite3_column_int(ppStmt, 0);
        temp_resource.name = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        temp_resource.description = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 2)));
        temp_resource.lockStatus = sqlite3_column_int(ppStmt, 3);
        temp_resource.typeId = sqlite3_column_int(ppStmt, 4);
        temp_resource.parentId = sqlite3_column_int(ppStmt, 5);
        
        resources.push_back(temp_resource);

        s = sqlite3_step(ppStmt);
    }

    return resources;
}
        

::LabrestAPI::Resource 
LabrestAPI::LabrestDB::getResource(int id)
{
    int s;
    
    ::LabrestAPI::Resource resource;
    
    ::std::cout << "LabrestDB::getResource() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from resource where id = ? ;",-1,&ppStmt,0);
    
    sqlite3_bind_int(ppStmt, 1, id);

    s = sqlite3_step(ppStmt);
    
    if  (s == SQLITE_ROW)
    {
        resource.id = sqlite3_column_int(ppStmt, 0);
        resource.name = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        resource.description = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 2)));
        resource.lockStatus = sqlite3_column_int(ppStmt, 3);
        resource.typeId = sqlite3_column_int(ppStmt, 4);
        resource.parentId = sqlite3_column_int(ppStmt, 5);    
    }

    return resource;
}

::LabrestAPI::ResourceTypeList
LabrestAPI::LabrestDB::getAllResourceTypes()
{ 
    int s;
    
    ::LabrestAPI::ResourceTypeList resource_types;
    
    ::std::cout << "LabrestDB::getAllResourceTypes() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from resource_type;",-1,&ppStmt,0);

    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        ::LabrestAPI::ResourceType temp_resource_type;
        
        temp_resource_type.id = sqlite3_column_int(ppStmt, 0);
        temp_resource_type.name = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        temp_resource_type.description = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 2)));
        temp_resource_type.parentId =sqlite3_column_int(ppStmt, 3);
        
        resource_types.push_back(temp_resource_type);

        s = sqlite3_step(ppStmt);
    }

    return resource_types;
    
}
        
        
::LabrestAPI::ResourceType 
LabrestAPI::LabrestDB::getResourceType(int id)
{
    int s;
    
    ::LabrestAPI::ResourceType resource_type;
    
    ::std::cout << "LabrestDB::getResourceType() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from resource_type where id = ? ;",-1,&ppStmt,0);
    
    sqlite3_bind_int(ppStmt, 1, id);

    s = sqlite3_step(ppStmt);
    
    if  (s == SQLITE_ROW)
    {
        resource_type.id = sqlite3_column_int(ppStmt, 0);
        resource_type.name = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        resource_type.description = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 2)));
        resource_type.parentId = sqlite3_column_int(ppStmt, 3);      
    }

    return resource_type;
}

::LabrestAPI::History 
LabrestAPI::LabrestDB::getLockHistry()
{
    int s;
    
    ::LabrestAPI::History lock_history;
    
    ::std::cout << "LabrestDB::getLockHistry() called" << ::std::endl;
    
    sqlite3_stmt * ppStmt;

    sqlite3_prepare(db,"select * from using_resource;",-1,&ppStmt,0);
    
    s = sqlite3_step(ppStmt);
    
    while (s == SQLITE_ROW)
    {
        ::LabrestAPI::HistoryRow temp_row;
        
        temp_row.id = sqlite3_column_int(ppStmt, 0);
        temp_row.username = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 1)));
        temp_row.resourceId = sqlite3_column_int(ppStmt, 2);
        temp_row.starTime = (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 3)));
        temp_row.endTime = (sqlite3_column_int(ppStmt,4)==0)? "" : (reinterpret_cast<const char *>(sqlite3_column_text(ppStmt, 4)));
        
        lock_history.push_back(temp_row);

        s = sqlite3_step(ppStmt);
    }

    return lock_history;
}