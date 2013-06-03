module LabrestAPI {

	struct User {
		string name;
		string auth;
                int group;
	};

	struct ResourceType {
		int id;
		string name;
		string description;
		int parentId;
	};

        struct LockStatus {
		int id;
		string username;
                int resourceId;
		string starTime;
                int duration; 
		string endTime;
	};

        struct Resource {
		int id;
		string name;
		string description;
		LockStatus resLockStatus; 
                int parentId;
		int typeId;
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

	interface Session {
		ResourceManager * getResourceManager();
		UserManager * getUserManager();
                CallbackManager * getCallbackManager();
	};

	interface Entry {
		Session * login(string username, string authdata)
			throws LoginException;
	};

        interface ResourceManager {
		ResourceIdList getAllResourceIds();
		ResourceList getAllResources();
		Resource getResource(int resourceId);
		int addResource(string name,
			string description,
			int parentId,
			int typeId);
		bool deleteResource(int resourceId);
		bool modifyResource(int resourceId,
			string name,
			string description,
			int parentId,
			int typeId);
		
		bool lockResource(int resourceId, int duration);
		void unlockResource(int resourceId);

                History getLockHistory();
		
		ResourceTypeIdList getAllResourceTypeIds();
		ResourceTypeList getAllResourceTypes();
		ResourceType getResourceType(int resourceTypeId);
		int addResourceType(string name,
			string description,
			int parentId);
		bool deleteResourceType(int resourceTypeId);
		bool modifyResourceType(int resourceTypeId,
			string name,
			string description,
			int parentId);
	};

	interface UserManager {
		bool addUser(string username, string authdata, int group);
		bool deleteUser(string username);
		UserList getAllUsers();
                User getUser(string username);
		bool modifyUser(string username, string authdata, int group);
	};

        interface CallbackManager {
                bool registerCallback(Callback * cb);
                bool unregisterCallback(Callback * cb);
        };

        interface Callback {
                void doCallback();
        };
	
};
