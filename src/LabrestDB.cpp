#include "LabrestDB.h"

int LabrestAPI::LabrestDB::connect() 
{
    int rc = sqlite3_open("labrest.db", &db);

    if(rc)
    {
        std::cout << "Can't open database\n";
    } 
    else 
    {
        std::cout << "Open database successfully\n";

        ::std::string sql[5];

        sql[0] = "create table if not exists user(username text primary key, authdate text);";

        sql[1] = "create table if not exists resource_type(id integer primary key autoincrement, name text, description, parent integer);";

        sql[2] = "create table if not exists resource(id integer primary key autoincrement, name text, description text, lock_status boolean, type_id integer, parent integer);";

        sql[3] = "create table if not exists using_resource(id integer primary key autoincrement, username text, resource_id integer, start_data datetime, timeout integer, status boolean);";

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

    if(db)
    {

        std::cout << "Close database\n";

        sqlite3_close(db);
    }

    return 0;
}

LabrestAPI::LabrestDB::~LabrestDB() 
{

    this->disconnect();

}

LabrestAPI::LabrestDB::LabrestDB() 
{
    this->connect();
}

bool LabrestAPI::LabrestDB::existsUser(::std::string username, ::std::string authdate)
{
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"select username from user where (username = ? ) and (authdate = ?);",-1,&ppStmt,0);

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
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"delete from user where username = ?;",1,&ppStmt,0);

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

bool LabrestAPI::LabrestDB::changeUser(::std::string username, ::std::string field, ::std::string value)
{

}

int  LabrestAPI::LabrestDB::addResourse(::std::string name, ::std::string description, int typeId, int parentId)
{
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"insert into resource(name,description,type_id,parent) values(?,?,?,?);",-1,&ppStmt,0);

    sqlite3_bind_text(ppStmt, 1, name.c_str(), name.length(),NULL);

    sqlite3_bind_text(ppStmt, 2, description.c_str(), description.length(),NULL);

    sqlite3_bind_int(ppStmt, 3, typeId);

    sqlite3_bind_null(ppStmt, 4);

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

bool LabrestAPI::LabrestDB::changeResource(int id, ::std::string field, ::std::string value)
{

}

bool LabrestAPI::LabrestDB::changeResource(int id, ::std::string field, int value)
{

}

int  LabrestAPI::LabrestDB::addResourceType(::std::string name, ::std::string description, int parentId)
{
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"insert into resource_type(name, descrption, parent) values(?,?,?);",-1,&ppStmt,0);

    sqlite3_bind_text(ppStmt, 1, name.c_str(), name.length(),NULL);

    sqlite3_bind_text(ppStmt, 2, description.c_str(), description.length(),NULL);

    sqlite3_bind_int(ppStmt, 3, parentId);

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
    bool status;

    sqlite3_stmt *ppStmt;

    sqlite3_prepare(db,"delete from resource_type where id = ?;",-1,&ppStmt,0);

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
	
bool LabrestAPI::LabrestDB::changeResourceType(int id, ::std::string field, ::std::string value)
{

}

bool LabrestAPI::LabrestDB::changeResourceType(int id, ::std::string field, int value)
{

}

bool LabrestAPI::LabrestDB::lockResourse(int resourceId, ::std::string username)
{

}

bool LabrestAPI::LabrestDB::unlockResource(int resourceId)
{

}
