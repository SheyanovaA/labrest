module LabrestAPI {
       class Session {
		void Test();
       };

       interface Entry {
                Session * Login(string username, string authdata);
       };
};
