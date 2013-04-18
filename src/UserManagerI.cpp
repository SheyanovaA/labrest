#include "UserManagerI.h"
#include <sqlite3.h>


bool
LabrestAPI::UserManagerI::addUser(const ::std::string& username,
                                  const ::std::string& authdata,
                                  const Ice::Current& current)
{


    sqlite3 *db;
    char *szErrMsg = 0;
// open database
    int rc = sqlite3_open("labrest.db", &db);

    if(rc)
    {
      std::cout << "Can't open database\n";
    } else {
      std::cout << "Open database successfully\n";
    }

    if(db)
    {
      std::cout << "Close database\n";
        sqlite3_close(db);
    }
      std::cout << "UserManagerI::addUser() called \n";
    return true;
}

::std::string
LabrestAPI::UserManagerI::getAllUsers(const Ice::Current& current)
{
char ** temp;
    sqlite3 *db;
    char *szErrMsg = 0;
// open database
    int rc = sqlite3_open("labrest.db", &db);

    if(rc)
    {
      std::cout << "Can't open database\n";
    } else {
      
	std::cout << "Open database successfully\n";
	if (sqlite3_get_table(db, "Select username from user;", &temp, 0,0, &szErrMsg))
	{
		::std::cout <<  "Ошибка SQL: " << &szErrMsg << ::std::endl;
	sqlite3_free(szErrMsg);
} else {
	::std::cout << temp[1] << ::std::endl;
}
    }

    if(db)
    {
      std::cout << "Close database\n";
        sqlite3_close(db);
    }
    ::std::cout << "UserManagerI::getAllUsers() called" << ::std::endl;
    return temp[1] ;
}
