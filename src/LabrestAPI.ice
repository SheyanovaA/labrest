module LabrestAPI {

	interface Resource;
	interface ResourceType;
	interface ResourceManager;
	interface UserManager;
	interface User;

	sequence<int> ResourceIdList;
	sequence<Resource> ResourceList;
	sequence<int> ResourceTypeIdList;
	sequence<Resource> ResourceTypeList;
	sequence<User> UserList;
	sequence<string> UserNameList;
	
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

	interface Resource {
		int getId();
		string getName();
		string getDescription();
		bool getLockStatus();
		Resource getParent();
		ResourceType getType();
	// ?? permissions for user ??
	};

	interface ResourceType {
		int getId();
		string getName();
		string getDescription();
		ResourceType getParent();
	};

	interface UserManager {
		bool addUser(string username, string authdata);
		UserList getAllUsers();
//		bool modifyUser(string username, string authdata);
//		UserNameList getAllUserName();
		// TODO
	};
	
	interface User {
		string getUserName();
	};
};
