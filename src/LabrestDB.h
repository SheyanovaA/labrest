#ifndef __LabrestDB_H__
#define __LabrestDB_H__

#include <iostream>
#include <sqlite3.h>
#include <LabrestAPI.h>

namespace LabrestAPI 
{

class LabrestDB 
{

	sqlite3 *db;

	char * szErrMsg;
        
        const unsigned char * sqlite3_column_text_or_null(sqlite3_stmt * stmt, int iCol, const char * default_value = "");
        
        int sqlite3_column_int_or_null(sqlite3_stmt * stmt, int iCol, int default_value = -1);

public:

	LabrestDB();

	~LabrestDB();

	int connect();

	int disconnect();

        bool existsUser(::std::string username, ::std::string authdate);

	::LabrestAPI::UserList getAllUsers();
        
        ::LabrestAPI::User getUser(::std::string username);

	bool addUser(::std::string username, ::std::string authdate);

	bool deleteUser(::std::string username);

	bool modifyUser(::std::string username, ::std::string authdata);
        
        ::LabrestAPI::ResourceList getAllResources();
        
        ::LabrestAPI::Resource getResource(int id);

	int  addResourse(::std::string name, 
                         ::std::string description, 
                         int typeId, 
                         int parentId);

	bool deleteResource(int id);

        bool modifyResource(int id, ::std::string name, 
                            ::std::string description,
                            int typeId, 
                            int parentId);
	
        ::LabrestAPI::ResourceTypeList getAllResourceTypes();
        
        ::LabrestAPI::ResourceType getResourceType(int id);
        
        int  addResourceType(::std::string name, 
                             ::std::string description, 
                             int parentId);

	bool deleteResourceType(int id);

	bool modifyResourceType(int id, 
                                ::std::string name, 
                                ::std::string description, 
                                int parentId);

	bool lockResourse(int resourceId, ::std::string username);

	bool unlockResource(int resourceId);
        
        bool ResourceIsLock(int resourceId);
        
        ::LabrestAPI::History getLockHistry();
};

};

extern LabrestAPI::LabrestDB * dbPtr;


#endif /* __LabrestDB_H__ */

