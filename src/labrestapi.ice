module labrestapi {
       class session {
		string getName();
		void setName(string name);
                void test();
		void close();
       };

       interface entry {
                session * login(string username, string authdata);
       };
};
