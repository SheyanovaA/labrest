module labrestapi {
       interface session {
                 void test();
       };
       interface entry {
                 session login(string username, string authdata);
       };
};
