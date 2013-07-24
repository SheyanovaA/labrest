#include <Ice/Identity.ice>

module LabrestAPI 
{
	struct User 
        {
		string name;
		string auth;
                int group;
	};

	struct ResourceType 
        {
		int id;
		string name;
		string description;
		int parentId;
	};

        struct LockStatus 
        {
		int id;
		string username;
                int resourceId;
		int startTime;
                int duration; 
		int endTime;
                string unlockComment;
	};

        struct Resource 
        {
		int id;
		string name;
		string description;
		LockStatus resLockStatus; 
                int parentId;
		ResourceType type;
	};

        struct Event
        {
                int id;
                int TypeEvent;
                int resourceId;
                
        };

        interface ResourceManager;
	interface UserManager;
        interface CallbackManager;
        interface Callback;

	sequence<int> ResourceIdList;
	sequence<Resource> ResourceList;
	sequence<int> ResourceTypeIdList;
	sequence<ResourceType> ResourceTypeList;
	sequence<User> UserList;
        sequence<LockStatus> History;
	
	exception LoginException {};
        exception ADCLoginTrue {};
        exception AccessDenied {};
        exception InvalidValue {};
        exception ResourceIsLock {};

	interface Session 
        {
		ResourceManager * getResourceManager();

		UserManager * getUserManager();

                CallbackManager * getCallbackManager();

                idempotent void Refresh();

                void destroy();
	};

	interface Entry 
        {
		Session * login(string username, string authdata)
			throws LoginException, ADCLoginTrue;
	};

        interface ResourceManager 
        {
		ResourceIdList getAllResourceIds();

		ResourceList getAllResources();

		Resource getResource(int resourceId);

		int addResource(string name,
                            string description,
                            int parentId,
                            ResourceType type)
                        throws AccessDenied, InvalidValue;

		bool deleteResource(int resourceId)
                        throws AccessDenied, InvalidValue;

		bool modifyResource(int resourceId,
                            string name,
                            string description,
                            int parentId,
                            ResourceType type)
                        throws AccessDenied, InvalidValue;
		
		bool lockResource(int resourceId, int duration)
                        throws InvalidValue, ResourceIsLock;

		void unlockResource(int resourceId)
                        throws InvalidValue;

                History getLockHistory()
                        throws AccessDenied;
		
		ResourceTypeIdList getAllResourceTypeIds();

		ResourceTypeList getAllResourceTypes();

		ResourceType getResourceType(int resourceTypeId);

		int addResourceType(string name,
                            string description,
                            int parentId)
                        throws AccessDenied, InvalidValue;

		bool deleteResourceType(int resourceTypeId)
                        throws AccessDenied, InvalidValue;

		bool modifyResourceType(int resourceTypeId,
                            string name,
                            string description,
                            int parentId)
                        throws AccessDenied, InvalidValue;
	};

	interface UserManager 
        {
		bool addUser(string username, string authdata, int group)
                        throws AccessDenied;

		bool deleteUser(string username)
                        throws AccessDenied;

		UserList getAllUsers();

                User getUser(string username);

		bool modifyUser(string username, string authdata, int group)
                        throws AccessDenied;
	};

        interface CallbackManager 
        {
                bool registerCallback(Ice::Identity ident);

                bool unregisterCallback(Ice::Identity ident);
        };

        interface Callback 
        {
                void doCallback(Event ev);
        };
	
};
