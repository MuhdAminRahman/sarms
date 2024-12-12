#ifndef SARMSDB_H
#define SARMSDB_H

class sarmsdb
{
private:
    
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *result;
    MYSQL_FIELD *fields;//for table column name
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

public:
    sarmsdb();
    ~sarmsdb();
    void connectdb();
    void closedb();
    void queryDB(string &query);

    bool verifyLogin(string &username, string &password, string &role);
    bool checkUsername(string &username);

    //AdminUserManagement
    void addUser(string username, string password, string role, string name, string phoneno, string dob, string address, string designation);

    void retrieveAllUser();
    void retrieveAdmin();
    void retrieveTeacher();
    void retrieveParent();
    void retrieveStudent();
    void retrieveUserID(string &username,string &UserID);

    void deleteUser(string username);

    void updateUser(string UserID);

    //AdminSubjectManagement
    void addSubject(string name, string description);
    void retrieveSubject();
    void retrieveSubjectID(string name,string &SubjectID);
    void deleteSubject(string subjectID);
    void updateSubject();

    //AdminTuitionManagement
    void addTuitionDetails(string name,string fee);
    void retrieveTuitionDetails();
    void retrieveTuitionDetailsID();
    void deleteTuitionDetails();
    void updateTuitionDetails();
    //AdminClassManagement
        //Class Management
    void addClass(string name,string StaffID);
    void retrieveClass();
    void retrieveClassID();
    void deleteClass();
    void updateClass();

        //Schedule Management
    void addSchedule(string name,string date);
    void retrieveSchedule();
    void retrieveScheduleID();
    void deleteSchedule();
    void updateSchedule();
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
    string query = "SELECT role FROM useraccounts WHERE Username = '" + username + "' AND Password = '" + password + "'";
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
        else{
            mysql_free_result(result);
        }
        
    }
    return false;
}

bool sarmsdb::checkUsername(string &username){
    string query = "SELECT Username FROM useraccounts WHERE Username = '" + username + "'";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result)
    {
        if (mysql_num_rows(result) > 0)
        {
            mysql_free_result(result);
            return true;
        }
        else
        {
            mysql_free_result(result);
            return false;
        }  
    }
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
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrieveAdmin(){
    string query = "SELECT * FROM useraccounts JOIN staff using (UserID) where Role = 'Admin'";
    queryDB(query);
    result = mysql_store_result(conn);
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
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveTeacher(){
    string query = "SELECT * FROM useraccounts JOIN staff using (UserID) where Role = 'Teacher'";
    queryDB(query);
    result = mysql_store_result(conn);
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
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveParent(){
    string query = "SELECT * FROM useraccounts JOIN parent using (UserID) where Role = 'Parent'";
    queryDB(query);
    result = mysql_store_result(conn);
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
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveStudent(){
    string query = "SELECT * FROM useraccounts JOIN student using (UserID) where Role = 'Student'";
    queryDB(query);
    result = mysql_store_result(conn);
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
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveUserID(string &username,string &UserID){
    string query = "select UserID from useraccounts where Username = '" + username +"'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        UserID = row[0];
        mysql_free_result(result);
    }
}


void sarmsdb::deleteUser(string UserID){
    string query = "DELETE FROM useraccounts WHERE UserID = '" + UserID + "'";
    queryDB(query);

}

//Subject Management
void sarmsdb::addSubject(string name,string description){
    string query = "INSERT INTO subject(Name,Description) VALUES ('" + name + "','"+ description+"')";
    queryDB(query);
}
void sarmsdb::retrieveSubject(){
    string query = "SELECT * FROM subject";
    queryDB(query);
    result=mysql_store_result(conn);
    if(result)
    {
        numfields = mysql_num_fields(result);
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
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::deleteSubject(string subjectID){
    string query = "DELETE FROM subject WHERE SubjectID = '" + subjectID + "'";
    queryDB(query);
}

//Tuition Management
void sarmsdb::addTuitionDetails(string name,string fee){
    string query = "INSERT INTO tuitiondetails(Name,Fee) VALUES ('" + name + "','"+ fee+"')";
    queryDB(query);
}

//Class Management