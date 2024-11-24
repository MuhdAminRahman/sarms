#ifndef SARMSUSER_H
#define SARMSUSER_H
class sarmsUser
{
private:
    sarmsdb db;
    struct UserNode
    {
        string username;
        string password;
        string role;
        UserNode *next;
    };
    UserNode *head;
    UserNode *current;
    UserNode *head2;
    bool verifyFlag;
public:
    sarmsUser();
    ~sarmsUser();
    void addUser(string username,string password,string role);
    void deleteUser();
    void updateUser();
    void retrieveUser();
    bool isUser(string name, string password,string &role);
};
#endif

sarmsUser::sarmsUser(){}
sarmsUser::~sarmsUser(){}
void sarmsUser::addUser(string username,string password,string role){
    //UserNode newUser = new UserNode;
}
void sarmsUser::deleteUser(){}
void sarmsUser::retrieveUser(){
    string query = "SELECT FROM USERACCOUNTS(name,password)";
    db.connectdb();
    db.queryDB(query);
    db.closedb();
}

void sarmsUser::updateUser(){}
bool sarmsUser::isUser(string name, string password,string &role){
    db.connectdb();
    verifyFlag = db.verifyLogin(name,password,role);
    db.closedb();
    return verifyFlag;
}