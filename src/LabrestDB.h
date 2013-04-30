#ifndef __LabrestDB_H__
#define __LabrestDB_H__

#include <iostream>
#include <sqlite3.h>

namespace LabrestAPI 
{

class LabrestDB 
{

	sqlite3 *db;

	char * szErrMsg;

public:

	LabrestDB();

	~LabrestDB();

	int connect();

	int disconnect();

        bool existsUser(::std::string username, ::std::string authdate);

	bool addUser(::std::string username, ::std::string authdate);

	bool deleteUser(::std::string username);

	bool changeUser(::std::string username, ::std::string field, ::std::string value);

	int  addResourse(::std::string name, ::std::string description, int typeId, int parentId);

	bool deleteResource(int id);

	bool changeResource(int id, ::std::string field, ::std::string value);

	bool changeResource(int id, ::std::string field, int value);

	int  addResourceType(::std::string name, ::std::string description, int parentId);

	bool deleteResourceType(int id);

	bool changeResourceType(int id, ::std::string field, ::std::string value);

	bool changeResourceType(int id, ::std::string field, int value);

	bool lockResourse(int resourceId, ::std::string username);

	bool unlockResource(int resourceId);
};

};

extern LabrestAPI::LabrestDB * dbPtr;


#endif /* __LabrestDB_H__ */

