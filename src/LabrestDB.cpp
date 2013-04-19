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

}

int LabrestAPI::LabrestDB::exec(::std::string SQL) 
{

    char ** temp;

    int col, str;

    if (sqlite3_exec(db, SQL.c_str(), 0, 0, &szErrMsg))
    {

        ::std::cout <<  "Ошибка SQL: " << &szErrMsg << ::std::endl;

        sqlite3_free(szErrMsg);

    }  
}
