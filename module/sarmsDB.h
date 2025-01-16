#ifndef SARMSDB_H
#define SARMSDB_H

#include <mysql.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

class sarmsdb
{
private:
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *result;
    MYSQL_FIELD *fields; // for table column name
    int numfields;

    int qstate;
    bool checkflag;

public:
    sarmsdb();
    ~sarmsdb();
    void connectdb();
    void closedb();
    void queryDB(string &query);
    void getLastInsertID(string &lastinsertID);

    // User verification
    bool verifyLogin(string &username, string &password, string &role);//done
    bool checkUsername(string &username);//done
    void retrieveRole(string &username,string &role);//done
    string setRoleID(string &userID,string &role);

    // Admin User Management
    void addUser(string username, string password, string role, string name, string phoneno, string dob, string address, string designation);
    void retrieveAllUser();
    void retrieveAdmin();
    void retrieveTeacher();
    void retrieveParent();
    void retrieveStudent();
    void retrieveStudentByName(string &name);
    void retrieveUserID(string &username, string &UserID);
    void retrieveUserByRole(string &role);
    void retrieveUserByUsername(string &username);
    void retrieveUserByName(string &name);

    void retrieveUser(string & userID,string &role);


    void deleteUser(string username);
    void updateUser(string userID, string newName, string newPhone, string newDob, string newAddress, string newRole, string newDesignation);
    void setParentToStudent(string &parentID,string &studentID);
    void updateUser(string &username,string &role,string &userID, string &newName, string &newPhone, string &newDob, string &newAddress,string &parentid);
    void updateUseraccounts(string &userID,string &newPassword);
    void updateStaff(string &userID,string &newName, string &newPhone);
    void updateParent(string &userID,string &newName,string &newPhone);
    void updateStudent(string &userID,string &newName,string &newPhone, string &newDob, string &newAddress);

    // Admin Subject Management
    void addSubject(string name, string description);
    void retrieveSubject();
    void getSubjectIDFromBridge(string &scheduleID,string *subjectID,string *staffID);
    void retrieveStaffTeachingSubject(string &subjectID);
    void deleteSubject(string subjectID);
    void updateSubject();
    void setSubjectToTeacher(string &subjectID);

    // Admin Tuition Management
    void addTuitionDetails(string name, string fee);
    void retrieveTuitionDetails(string &studentID);
    void retrieveAllTuition();
    void retrieveAllUnpaidTuition();
    void deleteTuitionDetails();
    void updateTuitionDetails();
    bool checkAlreadyPaidTuition(string &tuitionID);
    string getTuitionID(string &studentID);
    float getTotalTuitionAmount(string &tuitionID);
    void setStudentTuition(string &studentID);

    // Admin Class Management
    void addClass(string &name, string &staffID,string &classScheduleID);
    void getClassIDFromBridge(string &classID,string &studentID);
    void addClassSchedule(string &name);
    void retrieveClassList();
    
    void updateClass(string &classID,string &name,string &staffID);
    void updateClassScheduleName(string &scheduleID, string &newName);
    void deleteClassSchedule(string scheduleID);
    void retrieveSubjectSchedule(string &classID);
    void addSubjectToSchedule(string &scheduleID, string &subjectID,string &staffID,string &starttime,string &endtime);
    void getClassScheduleID(string &classID,string &scheduleID);
    bool checkTimeSlotTaken(string &scheduleID,string starttime,string endtime);


    //Staff Functions
    void staffretrieveUserbyName(string &name);
    void staffretrieveUserbyRole(string &role);
    void staffretrieveUserbyUsername(string &username);
    void staffretrieveAllUser();
    // Teacher Assessment Management
    void createAssessment(string &studentID);
    void retrieveAssessments(string &studentID,string &staffID);
    void retrieveStudentForAssessment(string &staffID);
    void updateAssessment(string &studentID, string &staffID, string &subjectID, string &score,string &remarks);
    void deleteAssessment(string assessmentID);

    // Teacher Class Management
    void retrieveTeacherClassList(string &staffID);
    void assignStudentToClass(string classID,string studentID);

    //Parent Functions
    void setChildID(string *childID, string &parentID,int &count);
    void retrievePaymentHistory(string &parentID);
    void makePayment(string &childID,string &tuitionID,float &amount);

    // Student Functions
    void retrieveStudentAssessment(string &studentID);
    void retrieveStudentClassSchedule(string &studentID);

};

#endif

sarmsdb::sarmsdb() {
    connectdb();
}

sarmsdb::~sarmsdb() {
    closedb();
}

void sarmsdb::connectdb() {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "Kuwa20cura!", "SARMS", 3306, NULL, 0);
    if (!conn) {
        cerr << "Failed to connect to database: " << mysql_error(conn) << '\n';
    }
}

void sarmsdb::closedb() {
    mysql_close(conn);
}

void sarmsdb::queryDB(string &query) {
    if (!conn) {
        cerr << "Database connection is null!" << endl;
        return;
    }
    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error: " << mysql_error(conn) << endl;
        cout << query << endl;
        system("PAUSE");
    }
}

void sarmsdb::getLastInsertID(string &lastinsertID){
    lastinsertID = to_string(mysql_insert_id(conn)) ;
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
void sarmsdb::retrieveRole(string &username, string &role){
    string query = "select role from useraccounts where username = '" +username+"'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        if (mysql_num_rows(result)>0)
        {
            row = mysql_fetch_row(result);
            role = row[0];
            mysql_free_result(result);
        }
        else
        {
            mysql_free_result(result);
        }
    }
    else{
        cout << "\n Failed to retrieve user role.";
    }
}

string sarmsdb::setRoleID(string &userID,string &role){
    
    string myid;
    string query;
    if(role == "Admin" || role == "Staff" || role == "Teacher"){
        query = "select StaffID from staff where UserID = '" + userID + "'";
    }
    if(role == "Parent"){
        query = "select ParentID from parent where UserID = '" + userID + "'";
    }
    if(role == "Student"){
        query = "select StudentID from student where UserID = '" + userID + "'";
    }
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        if (mysql_num_rows(result)>0)
        {
            row = mysql_fetch_row(result);
            myid = row[0];
            mysql_free_result(result);
            return myid;
        }
        else
        {
            mysql_free_result(result);
            return "id not found";
        }
    }
    else{
        cout << "\n Failed to retrieve user role.";
        return "id not found";
    }
}

void sarmsdb::addUser(string username, string password, string role, string name, string phoneno, string dob, string address, string designation)
{
    string query = "INSERT INTO useraccounts(Username,Password,Role) VALUES ('" + username + "','" + password + "','" + role + "')";
    queryDB(query);
    string query2;
    if (role == "Admin" || role == "Staff" || role == "Teacher")
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
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
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
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
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
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
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
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
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
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrieveStudentByName(string &name){
    string query = "select * from student join useraccounts using (UserID) where Name like '%" + name + "%'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
    }
}

void sarmsdb::retrieveUser(string &userID,string &role){
    if(role == "Admin" || role == "Teacher" || role == "Staff"){
        string query = "select * from useraccounts join staff where UserID = '" + userID +"'";
    }
    if(role == "Parent"){
        string query = "select * from useraccounts join parent where UserID = '" + userID +"'";
    }
    if(role == "Student"){
        string query = "select * from useraccounts join student where UserID = '" + userID +"'";
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

void sarmsdb::retrieveUserByRole(string &role){
    string query;
    
    if(role == "Admin" || role == "Staff" || role == "Teacher"){
        query = "select * from useraccounts join staff using (UserID) where role = '" + role + "'";
    }
    else{
        query = "select * from useraccounts join " + role + " using (UserID) where role = '" + role + "'";
    }
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
        
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
    
}
void sarmsdb::retrieveUserByUsername(string &username){
    string role;
    string query = "select Role from useraccounts where Username = '" + username + "'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        role = row[0];
        mysql_free_result(result);
    }
    if(role == "Admin" || role =="Staff" || role =="Teacher"){
        query = "select * from useraccounts join staff using (UserID) where Username = '" + username +"'";
        queryDB(query);
        result = mysql_store_result(conn);
        if(result)
        {
            Result res(result);
            Printer printer;
            Resultset_dumper_base dumper(&res, &printer);
            dumper.dump_table();
            mysql_free_result(result);
            cout << "\nEnter anything to continue : ";
            cin.get();
            
        }
    }
    else if(role == "Parent"){
        query = "select * from useraccounts join parent using (UserID) where Username = '" +username +"'";
        queryDB(query);
        result = mysql_store_result(conn);
        if(result)
        {
            Result res(result);
            Printer printer;
            Resultset_dumper_base dumper(&res, &printer);
            dumper.dump_table();
            mysql_free_result(result);
            cout << "\nEnter anything to continue : ";
            cin.get();
            
        }
    }
    else if(role == "Student"){
        query = "select * from useraccounts join student using (UserID) where Username = '" +username +"'";
        queryDB(query);
        result = mysql_store_result(conn);
        if(result)
        {
            Result res(result);
            Printer printer;
            Resultset_dumper_base dumper(&res, &printer);
            dumper.dump_table();
            mysql_free_result(result);
            cout << "\nEnter anything to continue : ";
            cin.get();
            
        }
    }
    
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveUserByName(string &name){
    
    string query = "select * from staff join useraccounts using (UserID) where Name like '%" + name + "%'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
        
    }
    query = "select * from parent join useraccounts using (UserID) where Name like '%" + name + "%'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
        
    }
    query = "select * from student join useraccounts using (UserID) where Name like '%" + name + "%'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
        
    }
}

void sarmsdb::deleteUser(string UserID){
    string query = "DELETE FROM useraccounts WHERE UserID = '" + UserID + "'";
    queryDB(query);

}
void sarmsdb::updateUser(string &username,string &role,string &userID, string &newName, string &newPhone, string &newDob, string &newAddress,string &parentid){
    string query= "select";

}
void sarmsdb::updateUseraccounts(string &userID,string &newPassword){
    string query;
    if (newPassword.length()>0)
    {
        query = "update useraccounts set Password = '" +newPassword+ "' wehere UserID = " +userID;
    }
    
}
void sarmsdb::updateStaff(string &userID,string &newName, string &newPhone){
    string query;
    if(newName.length()>0){
        query = "update staff set Name = '" + newName + "' where UserID = " + userID ;
        queryDB(query);
    }
    if (newPhone.length()>0)
    {
        query = "update staff set PhoneNo = '" + newPhone + "' where UserID = " + userID ;
        queryDB(query);
    }
}
void sarmsdb::updateParent(string &userID,string &newName, string &newPhone){
    string query;
    if(newName.length()>0){
        query = "update parent set Name = '" + newName + "' where UserID = " + userID;
        queryDB(query);
    }
    if(newPhone.length()>0){
        query = "update parent set Phone = '" + newPhone +"' where UserID = " + userID;
        queryDB(query);
    }
}
void sarmsdb::updateStudent(string &userID,string &newName,string &newPhone, string &newDob, string &newAddress){
    string query;
    if (newName.length()>0){
        query = "update student set Name = '" + newName+ "' where UserID = " + userID;
        queryDB(query);
    }
    if (newPhone.length()>0){
        query = "update student set PhoneNo = '" + newPhone + "' where UserID = " + userID ;
        queryDB(query);
    }
    if(newDob.length()>0){
        query = "update student set dob = '" + newDob + "' where UserID = " + userID ;
        queryDB(query);
    }
    if(newAddress.length()>0){
        query = "update student set Address = '" + newAddress + "' where UserID = " + userID ;
        queryDB(query);
    }
}

void sarmsdb::updateUser(string userID, string newName, string newPhone, string newDob, string newAddress, string newRole, string newDesignation){
    string query;
    
    
}

void sarmsdb::setParentToStudent(string &parentID,string &studentID){
    string query = "update student set ParentID = " + parentID + " where StudentID = " + studentID;
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
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::getSubjectIDFromBridge(string &scheduleID,string *subjectID,string *staff){
    string query = "SELECT SubjectID,StaffID FROM subjectschedule where ClassScheduleID = " + scheduleID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        subjectID[0] = row[0];
        staff[0] = row[1];
        row = mysql_fetch_row(result);
        subjectID[1] = row[0];
        staff[1] = row[1];
        row = mysql_fetch_row(result);
        subjectID[2] = row[0];
        staff[2] = row[1];
        row = mysql_fetch_row(result);
        subjectID[3] = row[0];
        staff[3] = row[1];
        row = mysql_fetch_row(result);
        subjectID[4] = row[0];
        staff[4] = row[1];
        row = mysql_fetch_row(result);
        subjectID[5] = row[0];
        staff[5] = row[1];
        mysql_free_result(result);

    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
    
}
void sarmsdb::retrieveStaffTeachingSubject(string &subjectID){
    
    string query = "SELECT staff.StaffID,staff.Name,subject.Name FROM staff join subjectbridge using (StaffID) join subject using (SubjectID) where SubjectID = " + subjectID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

//implement soft delete
void sarmsdb::deleteSubject(string subjectID){
    string query = "DELETE FROM subject WHERE SubjectID = '" + subjectID + "'";
    queryDB(query);
}

void sarmsdb::setSubjectToTeacher(string &subjectID){
    string query = "insert into subjectbridge(staffID,subjectID) values (LAST_INSERT_ID(),"+ subjectID +")";
    queryDB(query);
}

//Tuition Management
void sarmsdb::addTuitionDetails(string name,string fee){
    string query = "INSERT INTO tuitiondetails(Name,Fee) values ('" + name + "','"+ fee+"')";
    queryDB(query);
}

void sarmsdb::retrieveTuitionDetails(string &studentID){
    
    string query = "SELECT student.Name,tuition.Name,tuition.Description,tuitionbridge.PaidFlag,tuitiondetails.Name,tuitiondetails.Fee FROM student left join tuition using (StudentID) left join tuitionbridge using (TuitionID) left join tuitiondetails using (TuitionDetailsID) where StudentID = " + studentID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrieveAllTuition(){
    
    string query = "SELECT * FROM tuition";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrieveAllUnpaidTuition(){
    
    string query = "SELECT student.StudentID,student.Name AS StudentName FROM tuition join student using (StudentID) where AllPaid = 0";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        dumper.generate_csv("unpaidtuition.csv");
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

bool sarmsdb::checkAlreadyPaidTuition(string &tuitionID){
    string query = "select AllPaid from tuition where TuitionID = " + tuitionID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        if(row[0] == "1"){
            mysql_free_result(result);
            return true;
        }
        else{
            mysql_free_result(result);
            return false;
        }
    }
    else{
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
        return false;
    }
}

string sarmsdb::getTuitionID(string &studentID){
    string query = "select TuitionID from tuition where StudentID = " + studentID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        string tuitionID = row[0];
        mysql_free_result(result);
        return tuitionID;
    }
    else{
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
        return "0";
    }
}

float sarmsdb::getTotalTuitionAmount(string &tuitionID){
    string query = "select sum(Fee) from tuitiondetails join tuitionbridge using (TuitionDetailsID) where TuitionID = " + tuitionID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        float total = stof(row[0]);
        mysql_free_result(result);
        return total;
    }
    else{
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
        return 0;
    }
}

void sarmsdb::setStudentTuition(string &studentID){
    string query = "insert into tuition(Name,Description,StudentID) values ('"+ studentID +" Tuition','Tuition for student "+studentID+"'," + studentID + ")";
    queryDB(query);
    string tuitionID;
    getLastInsertID(tuitionID);
    query = "insert into tuitionbridge(TuitionID,TuitionDetailsID) values ("+tuitionID+",1)";
    queryDB(query);
    query = "insert into tuitionbridge(TuitionID,TuitionDetailsID) values ("+tuitionID+",2)";
    queryDB(query);
    query = "insert into tuitionbridge(TuitionID,TuitionDetailsID) values ("+tuitionID+",3)";
    queryDB(query);
    query = "insert into tuitionbridge(TuitionID,TuitionDetailsID) values ("+tuitionID+",4)";
    queryDB(query);
    query = "insert into tuitionbridge(TuitionID,TuitionDetailsID) values ("+tuitionID+",5)";
    queryDB(query);
}
// Teacher Assessment Management

void sarmsdb::createAssessment(string &studentID) {
    
    string classID,scheduleID;
    string *subjectID;
    string *staffID;
    subjectID = new string[6];
    staffID = new string[6];
    getClassIDFromBridge(classID,studentID);
    getClassScheduleID(classID,scheduleID);
    getSubjectIDFromBridge(scheduleID,subjectID,staffID);
    for(int i = 0; i<6;i++){
        string query = "INSERT INTO assessment (StudentID,StaffID,SubjectID) VALUES (" + studentID + "," + staffID[i] + "," + subjectID[i] + ")";
        queryDB(query);
    }
    delete[] subjectID;
    delete[] staffID;

}

void sarmsdb::retrieveAssessments(string &studentID,string &staffID) {
    
    string query = "SELECT student.Name AS StudentName,subject.Name AS SubjectName,assessment.SubjectID,assessment.Score,assessment.Grade,assessment.Remarks FROM assessment join student using (StudentID) join subject using (SubjectID) WHERE StudentID = " + studentID + " AND StaffID = " + staffID;
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrieveStudentForAssessment(string &staffID) {
    
    string query = "SELECT DISTINCT(assessment.StudentID),student.Name FROM assessment join student using(StudentID)  WHERE StaffID =" + staffID;
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::updateAssessment(string &studentID, string &staffID, string &subjectID, string &score,string &remarks) {
    string query = "UPDATE assessment SET Score = " + score + ", Remarks = '" + remarks + "' WHERE StudentID = " + studentID + " AND StaffID = " + staffID + " AND SubjectID = " + subjectID;
    queryDB(query);
}

void sarmsdb::deleteAssessment(string assessmentID) {
    string query = "DELETE FROM assessment WHERE AssessmentID = " + assessmentID;
    queryDB(query);
}

//Class Management
void sarmsdb::assignStudentToClass(string classID,string studentID) {
    string query = "INSERT INTO classbridge (ClassID, StudentID) VALUES (" + classID + "," + studentID +")";
    queryDB(query);
}

void sarmsdb::addClass(string &name, string &staffID,string &classScheduleID) {
    string query = "INSERT INTO class (Name, StaffID,ClassScheduleID) VALUES ('" + name + "', '" + staffID + "', '" + classScheduleID + "')";
    queryDB(query);
}
void sarmsdb::getClassIDFromBridge(string &classID,string &studentID){
    string query = "select ClassID from classbridge where StudentID = " + studentID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        classID = row[0];
        mysql_free_result(result);
    }
    else{
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::addClassSchedule(string &name) {
    string query = "INSERT INTO class_schedules (Name, Date) VALUES ('" + name + "', CURDATE())";
    queryDB(query);
}
void sarmsdb::retrieveClassList() {
    string query = "SELECT ClassID,Name FROM class";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
    } 
    else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}

void sarmsdb::updateClass(string &classID,string &name,string &staffID) {
    if(name.length()>0){
        string query = "UPDATE class SET Name = '" + name + "' WHERE ClassID = " + classID;
        queryDB(query);
    }
    if(staffID.length()>0){
        string query = "UPDATE class SET StaffID = '" + staffID + "' WHERE ClassID = " + classID;
        queryDB(query);
    }
}
void sarmsdb::updateClassScheduleName(string &scheduleID, string &newName) {
    string query = "UPDATE classschedule SET Name = CONCAT(YEAR(CURDATE()),'/','"+ newName +"'),Date = CURDATE() WHERE ClassScheduleID = " +scheduleID;
    queryDB(query);
}

void sarmsdb::deleteClassSchedule(string scheduleID) {
    string query = "DELETE FROM class_schedules WHERE ScheduleID = " + scheduleID;
    queryDB(query);
}

void sarmsdb::retrieveSubjectSchedule(string &classID) {
    string query = "SELECT class.Name, classschedule.Name, TIME_FORMAT(subjectschedule.StartTime,'%r') AS 'StartTime', TIME_FORMAT(subjectschedule.EndTime,'%r') AS 'EndTime', subjectschedule.Duration, staff.Name AS 'Teacher', subject.Name AS Subject"
                    " FROM class "
                    "JOIN classschedule ON class.ClassScheduleID = classschedule.ClassScheduleID "
                    "JOIN subjectschedule ON classschedule.ClassScheduleID = subjectschedule.ClassScheduleID "
                    "JOIN staff ON subjectschedule.StaffID = staff.StaffID "
                    "JOIN subject ON subjectschedule.SubjectID = subject.SubjectID "
                    "WHERE class.ClassID = " + classID + " ORDER BY subjectschedule.StartTime ASC";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
    } else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}

void sarmsdb::addSubjectToSchedule(string &scheduleID, string &subjectID,string &staffID,string &starttime,string &endtime) {
    string query = "INSERT INTO subjectschedule (ClassScheduleID, SubjectID, StaffID, StartTime, EndTime) VALUES (" + scheduleID + ", " + subjectID + ", " + staffID + ", '" + starttime + "', '" + endtime + "')";
    queryDB(query);
}
void sarmsdb::getClassScheduleID(string &classID,string &scheduleID){
    string query = "select ClassScheduleID from class where ClassID = " + classID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        scheduleID = row[0];
        mysql_free_result(result);
    }
}
bool sarmsdb::checkTimeSlotTaken(string &scheduleID,string starttime,string endtime){
    string query = "select * from subjectschedule where ClassScheduleID = " + scheduleID + " and StartTime = '" + starttime + "' and EndTime = '" + endtime + "'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        if(mysql_num_rows(result)>0){
            cout << "Time slot is taken. Please choose another time slot." << endl;
            mysql_free_result(result);
            return true;
        }
        else{
            mysql_free_result(result);
            return false;
        }
    }
    else{
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
        return true;
    }
}

//Staff Functions
void sarmsdb::staffretrieveUserbyName(string &name){
    
    string query = "select * from staff join useraccounts using (UserID) where role = 'Teacher' and Name like '%" + name + "%'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
        
    }
    query = "select * from parent join useraccounts using (UserID) where Name like '%" + name + "%'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
        
    }
    query = "select * from student join useraccounts using (UserID) where Name like '%" + name + "%'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
        
    }
}

void sarmsdb::staffretrieveUserbyRole(string &role){
    
    string query;
    if(role == "Teacher"){
        query = "select * from useraccounts join staff using (UserID) where role = '" + role + "'";
    }
    else{
        query = "select * from useraccounts join " + role + " using (UserID) where role = '" + role + "'";
    }
    queryDB(query);
    result = mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
        
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::staffretrieveUserbyUsername(string &username){
    string role;
    string query = "select Role from useraccounts where Username = '" + username + "'";
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        row = mysql_fetch_row(result);
        if(row){
            role = row[0];
        }
        else{
            cout << "\nUser not found.";
        }
        mysql_free_result(result);
        if(role =="Teacher"){
            query = "select * from useraccounts join staff using (UserID) where Username = '" + username +"'";
            queryDB(query);
            result = mysql_store_result(conn);
            if(result)
            {
                Result res(result);
                Printer printer;
                Resultset_dumper_base dumper(&res, &printer);
                dumper.dump_table();
                mysql_free_result(result);
                cout << "\nEnter anything to continue : ";
                cin.get();
                
            }
        }
        else if(role == "Parent"){
            query = "select * from useraccounts join parent using (UserID) where Username = '" +username +"'";
            queryDB(query);
            result = mysql_store_result(conn);
            if(result)
            {
                Result res(result);
                Printer printer;
                Resultset_dumper_base dumper(&res, &printer);
                dumper.dump_table();
                mysql_free_result(result);
                cout << "\nEnter anything to continue : ";
                cin.get();
                
            }
        }
        else if(role == "Student"){
            query = "select * from useraccounts join student using (UserID) where Username = '" +username +"'";
            queryDB(query);
            result = mysql_store_result(conn);
            if(result)
            {
                Result res(result);
                Printer printer;
                Resultset_dumper_base dumper(&res, &printer);
                dumper.dump_table();
                mysql_free_result(result);
                cout << "\nEnter anything to continue : ";
                cin.get();
                
            }
        }
    }
    
    
    else
    {
        //cout << "\nUser not found.";
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::staffretrieveAllUser(){
    
    string query = "SELECT Username,Role FROM useraccounts where Role != 'Admin' and Role != 'Staff'";
    queryDB(query);
    result=mysql_store_result(conn);
    if(result)
    {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

// Teacher Grade Management
void sarmsdb::retrieveTeacherClassList(string &staffID) {
    string query = "SELECT class.ClassID, class.Name FROM class WHERE StaffID = " + staffID;
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
    } else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}

///Parent Functions

void sarmsdb::setChildID(string *childID, string &parentID, int &count){
    string query = "select StudentID from student where ParentID = " + parentID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        while(row = mysql_fetch_row(result)){
            childID[count] = row[0];
            count++;
        }
    }
    else{
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrievePaymentHistory(string &parentID){
    
    string query = "SELECT student.Name AS StudentName, tuition.Name AS TuitionName, payment.Method, payment.Amount, payment.Date FROM payment join tuition using (TuitionID) join student using (StudentID) where student.ParentID = " + parentID;
    queryDB(query);
    result = mysql_store_result(conn);
    if(result){
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    }
    else{
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::makePayment(string &childID,string &tuitionID,float &amount){
    string query;
    float total = getTotalTuitionAmount(tuitionID);
    bool AlreadyPaid = checkAlreadyPaidTuition(tuitionID);

    if(AlreadyPaid == 0){
        cout << "Tuition has already been paid." << endl;
        cin.get();
        return;
    }
    if(amount == total){
        query = "update tuitionbridge set PaidFlag = 1 where TuitionID = " + tuitionID;
        queryDB(query);
        query = "insert into payment (Method,Amount,Date,TuitionID) values ('Cash'," + to_string(amount) + ",CURDATE()," + tuitionID + ")";
        queryDB(query);
    }
    else{
        cout << "Amount paid does not match the total tuition amount." << endl;
        cin.get();
    }


}


//Student Functions
void sarmsdb::retrieveStudentAssessment(string &studentID) {
    string query = "SELECT student.Name AS StudentName,subject.Name AS SubjectName,assessment.SubjectID,assessment.Score,assessment.Grade,assessment.Remarks FROM assessment join student using (StudentID) join subject using (SubjectID) WHERE StudentID = " + studentID;
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        mysql_free_result(result);
        cout << "\nEnter anything to continue : ";
        cin.get();
    } else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrieveStudentClassSchedule(string &studentID) {
    string query = "SELECT class.Name, classschedule.Name, TIME_FORMAT(subjectschedule.StartTime,'%r') AS 'StartTime', TIME_FORMAT(subjectschedule.EndTime,'%r') AS 'EndTime', subjectschedule.Duration, staff.Name AS 'Teacher', subject.Name AS Subject"
                    " FROM class "
                    "JOIN classschedule ON class.ClassScheduleID = classschedule.ClassScheduleID "
                    "JOIN subjectschedule ON classschedule.ClassScheduleID = subjectschedule.ClassScheduleID "
                    "JOIN staff ON subjectschedule.StaffID = staff.StaffID "
                    "JOIN subject ON subjectschedule.SubjectID = subject.SubjectID "
                    "JOIN classbridge ON class.ClassID = classbridge.ClassID "
                    "WHERE classbridge.StudentID = " + studentID + " ORDER BY subjectschedule.StartTime ASC";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        Result res(result);
        Printer printer;
        Resultset_dumper_base dumper(&res, &printer);
        dumper.dump_table();
        cin.get();
        mysql_free_result(result);
    } else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}