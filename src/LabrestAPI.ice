module LabrestAPI {
       interface Session {
		void test();
                // resources (get-all, add, delete)
       };

       interface Entry {
                Session * login(string username, string authdata);
       };

       class Resource {
		bool lockStatus;
		string name;
		string description;
		Resource parent;
		ResourceType type;
		
		string getName();
		string getDescription();
		boot getLockStatus();
		Resource getParent();
		ResourceType getType();
		bool setLockStatus(bool status);
		
       // get/set name/description .... ?? permissions for user ??
       // get/set lock status
       // get/set parent
       // get/set type
}
       class ResourceType {
		string name;
		ResourceType parent;

};
