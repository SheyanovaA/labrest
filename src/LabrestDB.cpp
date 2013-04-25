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

    this->exec("create table if not exists user(username text primary key, authdate text);");

    this->exec("create table if not exists resource_type(id integer primary key autoincrement, name text, description, parent integer);");

    this->exec("create table if not exists resource(id integer primary key autoincrement, name text, description text, lock_status boolean, type_id integer, parent integer);");

    this->exec("create table if not exists using_resource(id integer primary key autoincrement, username text, resource_id integer, start_data datetime, timeout integer, status boolean);");

}

int LabrestAPI::LabrestDB::exec(::std::string SQL) 
{

    char ** temp;

    if (sqlite3_exec(db, SQL.c_str(), 0, 0, &szErrMsg))
    {

        ::std::cout <<  "Ошибка SQL: " << &szErrMsg << ::std::endl;

        sqlite3_free(szErrMsg);

    }  
}

bool LabrestAPI::LabrestDB::existsUser(::std::string username, ::std::string authdate)
{
    bool status;

    int str;

    char ** result;

    ::std::string SQL;

    SQL = "select username from user where (username = '"+username+"') and (authdate = '"+authdate+"');";

    sqlite3_get_table(db,SQL.c_str(),&result,&str,0,&szErrMsg);

    sqlite3_free_table(result);

    if (str > 0) 
    {
        status = true;
    }
    else
    {
        status = false;
    };
    return status;
}


bool  LabrestAPI::LabrestDB::addQuery(::std::string SQL) 
{

    char ** temp;

    bool status = true;

    if (sqlite3_exec(db, SQL.c_str(), 0, 0, &szErrMsg))
    {
	status = false;

        ::std::cout <<  "Ошибка SQL: " << &szErrMsg << ::std::endl;

        sqlite3_free(szErrMsg);

    } 
    return status; 
}
