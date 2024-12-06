#ifndef SARMSDB_H
#define SARMSDB_H

class sarmsdb
{
private:
    
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *result;
    int numfields;
    string id;

    struct Node
    {
        string username;
        Node* next; 
    };
    Node* head;
    Node* currrent;

    int qstate;
    bool checkflag;

    string id;

public:
    sarmsdb();
    ~sarmsdb();
    void connectdb();
    void closedb();
    void queryDB(string &query);

    bool verifyLogin(string &username, string &password, string &role);
    bool checkUsername(string &username);

    void addUser(string username, string password, string role, string name, string phoneno, string dob, string address, string designation);
    void retrieveAllUser();
    void retrieveUser(string &username);
    void deleteUser();
    void updateUser();

    void setID(string &setid);
    void setParentID();
    void printQuery();
};
#endif

sarmsdb::sarmsdb()
{
}
sarmsdb::~sarmsdb() {
    closedb();
}

void sarmsdb::connectdb()
{
    try
    {
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "root", "Kuwa20cura!", "SARMS", 3306, NULL, 0);
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
        cout << "Failed to connect" << endl;
    }
}
void sarmsdb::closedb()
{
    try
    {
        mysql_close(conn);
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }
}

void sarmsdb::queryDB(string &query)
{
    try
    {
        if(!conn){
            cerr << "Database connection is null!" << endl;
            return;
        }
        if (mysql_query(conn, query.c_str()))
        {
            cerr << "MySQLQuery error: " << mysql_error(conn) << endl;
            mysql_close(conn);
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }
}
bool sarmsdb::verifyLogin(string &username, string &password, string &role)
{
    string query = "SELECT role FROM USERACCOUNTS WHERE Username = '" + username + "' AND Password = '" + password + "'";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result)
    {
        if (mysql_num_rows(result) > 0)
        {
            row = mysql_fetch_row(result);
            role = row[0];
            mysql_free_result(result);
            return true;
        }
        mysql_free_result(result);
    }
    mysql_free_result(result);
    return false;
}

bool sarmsdb::checkUsername(string &username){
    string query = "SELECT Username FROM useraccounts(Username) WHERE Username = '" + username + "'";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result)
    {
        if (mysql_num_rows(result) > 0)
        {
            mysql_free_result(result);
            return true;
        }
        mysql_free_result(result);
    }
    mysql_free_result(result);
    return false;
}

void sarmsdb::addUser(string username, string password, string role, string name, string phoneno, string dob, string address, string designation)
{
    connectdb();
    string query = "INSERT INTO useraccounts(Username,Password,Role) VALUES ('" + username + "','" + password + "','" + role + "')";
    queryDB(query);
    string query2;
    if (role == "Admin" || role == "Teacher")
    {
        query2 = "INSERT INTO staff(Name,PhoneNo,Designation,UserID) VALUES ('" + name + "','" + phoneno + "','" + designation + "',LAST_INSERT_ID())";
        queryDB(query2);
    }
    else if (role == "Parent")
    {
        query2 = "INSERT INTO parent(Name,PhoneNo,UserID) VALUES ('" + name + "','" + phoneno + "',LAST_INSERT_ID())";
        queryDB(query2);
    }
    else if (role == "Student")
    {
        query2 = "INSERT INTO student(Name,PhoneNo,dob,address,UserID) VALUES ('" + name + "','" + phoneno + "','" + dob + "','" + address + "',LAST_INSERT_ID())";
        queryDB(query2);
    }
    
}

void sarmsdb::retrieveAllUser(){
    string query = "SELECT Username FROM useraccounts";
    queryDB(query);
    result=mysql_store_result(conn);
    if(result)
    {
        numfields = mysql_num_fields(result);
        cout << "+-------------------+" << endl;
        cout << "| Username          |" << endl;
        cout << "+-------------------+" << endl;
        while((row = mysql_fetch_row(result))){
            for(int i = 0;i<numfields;i++){
                if(row[i]){
                    cout << "| " << setw(17) << i+1 <<". " << row[i] << " |" << endl;
                }
                else{
                    cout << "| " << setw(17)  << "NULL" << " |" << endl;
                }
            }
        }
        mysql_free_result(result);
        cout << "+-------------------+" << endl;
    }
    else
    {
        mysql_free_result(result);
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrieveUser(string &username){
    string query = "select UserID from useraccounts where Username = '";
}

void sarmsdb::deleteUser(){

}

void sarmsdb::updateUser(){

}

void sarmsdb::setID(string &setid){
    id = setid;
}

void sarmsdb::printQuery()
{
    result = mysql_store_result(conn);
    while (row = mysql_fetch_row(result))
    {
        cout << row[0] << row[1] << row[2] << row[3] << row[4];
    }
    mysql_free_result(result);
}
