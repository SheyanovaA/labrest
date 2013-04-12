module LabrestAPI {
       interface Session {
		void test();
                // resources (get-all, add, delete)
       };

       interface Entry {
                Session * login(string username, string authdata);
       };

       // interface resource
       // get/set name/description .... ?? permissions for user ??
       // get/set lock status
       // get/set parent
       // get/set type

       // interface resourcetype ??
};
