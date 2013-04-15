module LabrestAPI {

	sequence<Resource> ResourceList;       
	
	interface Session {
		void test();
		ResourceList getAllResources();
		void addResource(Resource new_resource);
		void delete() //????
	};

	interface Entry {
                Session * login(string username, string authdata);
	};

	interface Resource {		
		string getName();
		string getDescription();
		boot getLockStatus();
		Resource getParent();
		ResourceType getType();
		bool setLockStatus(bool status);
		void setName(string name);
		void setDescription(string description);
		void setParent(Resource parent);
		void setType(ResourceType type);
	// ?? permissions for user ??
	};

	interface ResourceType {
		string getName();
		string getDescription();
		ResourceType getParent();
		void setName(string name);
		void setDescription(string description);
		void setParent(ResourceType parent);
	};
};
