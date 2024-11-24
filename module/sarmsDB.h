#ifndef SARMSDB_H
#define SARMSDB_H

class sarmsdb
{
    private:
        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* result;
        int qstate;
        bool checkflag;


    public:
        sarmsdb();
        ~sarmsdb();
        void connectdb();
        void closedb();
        void queryDB(string query);
        bool verifyLogin(string username,string password,string &role);
        void addUser(string username,string password,string role);
        void addAdmin(string name,string phoneno, string address);
        void printQuery();
};
#endif

sarmsdb::sarmsdb(){
    connectdb();
}
sarmsdb::~sarmsdb(){}

void sarmsdb::connectdb()
{
    try
    {
        conn = mysql_init(0);
        cout << "connected successfully" << endl;
        conn = mysql_real_connect(conn,"localhost","root", "Kuwa20cura!","SARMS",3306,NULL,0);
        cout << "database connected to mysql" << endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        cout <<"Failed to connect" << endl;
    }
}
void sarmsdb::closedb(){
    try
    {
        mysql_free_result(result);
        mysql_close(conn);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
}

void sarmsdb::queryDB(string query)
{
    try
    {
        if(mysql_query(conn,query.c_str())){
            cerr << "MySQLQuery error: "<< mysql_error(conn) << endl;
            mysql_close(conn);
        }
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
}
bool sarmsdb::verifyLogin(string username,string password,string &role){
    string query = "SELECT role FROM USERACCOUNTS WHERE name = '" + username + "' AND password = '" + password + "'" ;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        if(mysql_num_rows(result)>0){
            row = mysql_fetch_row(result);
            role = row[0];
            return true;
        }
    }
    return false;
}

void sarmsdb::addUser(string username,string password, string role){
    string query = "INSERT INTO USERACCOUNTS(name,password,role) VALUES ('"+username+"','"+password+"','"+role+"')";
    queryDB(query);
    closedb();
}

void sarmsdb::printQuery(){
    result = mysql_store_result(conn);
    while(row = mysql_fetch_row(result)){
        cout << row[0] << row[1] << row[2] << row[3] << row[4];
    }
}