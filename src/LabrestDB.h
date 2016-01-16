#ifndef LabrestDB_H
#define LabrestDB_H

#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include <sqlite3.h>

#include "LabrestAPI.h"
#include "EventsQueue.h"

namespace LabrestAPI 
{
    
    
class LabrestDB 
{

	sqlite3 *db;

	char * szErrMsg;
        
        const unsigned char * sqlite3_column_text_or_null(sqlite3_stmt * stmt, int iCol, const char * default_value = "");
        
        int sqlite3_column_int_or_null(sqlite3_stmt * stmt, int iCol, int default_value = -1);
        
        bool ExistsResourceType(int resTypeId);
        
        bool ExistsResource(int resourceId);
        
        ::IceUtil::Mutex lock;

public:

	LabrestDB();

	~LabrestDB();

	int connect();

	int disconnect();
        
    bool authUser(::std::string username, ::std::string authdate);
        
    bool existsUser(::std::string username);
        
	::LabrestAPI::UserList getAllUsers();
        
    ::LabrestAPI::User getUser(::std::string username);

	bool addUser(::std::string username, ::std::string authdate, int group);

	bool deleteUser(::std::string username);

	bool modifyUser(::std::string username, ::std::string authdata, int group);
        
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
                             int writeLimit,
                             int parentId);

	bool deleteResourceType(int id);

	bool modifyResourceType(int id, 
                                ::std::string name, 
                                ::std::string description, 
                                int writeLimit,
                                int parentId);

	bool lockResource(int resourceId, ::std::string username, int duration);

	bool unlockResource(int resourceId, ::std::string username = "system");
        
    bool ResourceIsLockByUser(int resourceId, ::std::string username);

    bool ResourceIsNotLock(int resourceId);
        
    ::LabrestAPI::LockStatus getLockStatus(int Id);
        
    ::LabrestAPI::History getLockHistry();

    bool connectResources(int resourceId1, int resourceId2);

    bool isConnectedResources(int resourceId1, int resourceId2);

    bool disconnectResources(int resourceId1, int resourceId2);

    ::LabrestAPI::LinkList getAllConnections();

    ::LabrestAPI::ResourceList getResources(int resourceTypeId);
        
    ::LabrestAPI::IntList getResourceIdsCennectedWith(int resourceId);

    int getUsingCount(int resourceId);

    //TODO connectionMatrix

    void TimeOutCallbacks();
};

};

extern LabrestAPI::LabrestDB * dbPtr;


#endif /* LabrestDB_H */

