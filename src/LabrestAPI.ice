module LabrestAPI {
       class Session {
		void test();
       };

       interface Entry {
                Session * login(string username, string authdata);
       };
};
