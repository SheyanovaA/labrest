module LabrestAPI {

	interface ResourceManager;
	interface UserManager;

        struct User {
		string name;
		string auth;
	};

	struct ResourceType {
		int id;
		string name;
		string description;
		int parentId;
	};

        struct HistoryRow {
		int id;
		string username;
                int resourceId;
		string starTime;
		string endTime;
	};

        struct Resource {
		int id;
		string name;
		string description;
		bool lockStatus; // string currentUser; ?
                int parentId;
		int typeId;
	};


	sequence<int> ResourceIdList;
	sequence<Resource> ResourceList;
	sequence<int> ResourceTypeIdList;
	sequence<ResourceType> ResourceTypeList;
	sequence<User> UserList;
        sequence<HistoryRow> History;
	
	exception LoginException {};

	interface Session {
		ResourceManager * getResourceManager();
		UserManager * getUserManager();
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
		
		bool lockResource(int resourceId);
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
		bool addUser(string username, string authdata);
		bool deleteUser(string username);
		UserList getAllUsers();
                User getUser(string username);
		bool modifyUser(string username, string authdata);
		// TODO
	};
	
};
