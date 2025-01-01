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
    string id;

    int qstate;
    bool checkflag;

public:
    sarmsdb();
    ~sarmsdb();
    void connectdb();//done
    void closedb();//done
    void queryDB(string &query);//done

    // User verification
    bool verifyLogin(string &username, string &password, string &role);//done
    bool checkUsername(string &username);//done
    void retrieveRole(string &username,string &role);//done

    // Admin User Management
    void addUser(string username, string password, string role, string name, string phoneno, string dob, string address, string designation);
    void retrieveAllUser();//done
    void retrieveAdmin();//done
    void retrieveTeacher();//done
    void retrieveParent();//done
    void retrieveStudent();//done
    void retrieveUser(string & userID,string &role);
    void retrieveUserID(string &username, string &UserID);//done
    void retrieveUserByRole(string &role);//done
    void retrieveUserByUsername(string &username);//done
    void retrieveUserByName(string &name);//done

    void deleteUser(string username);
    void updateUser(string &username,string &role,string &userID, string &newName, string &newPhone, string &newDob, string &newAddress,string &parentid);
    void updateUseraccounts(string &userID,string &newUsername,string &newPassword);
    void updateStaff(string &userID,string &newName, string &newPhone);
    void updateParent(string &userID,string &newName,string &newPhone);
    void updateStudent(string &userID,string &newName,string &newPhone, string &newDob, string &newAddress, string &parentid);

    // Admin Subject Management
    void addSubject(string name, string description);
    void retrieveSubject();
    void deleteSubject(string subjectID);
    void updateSubject();

    // Admin Tuition Management
    void addTuitionDetails(string name, string fee);
    void retrieveTuitionDetails();
    void deleteTuitionDetails();
    void updateTuitionDetails();

    // Admin Class Management
    void addClass(string name, string StaffID);
    void retrieveClass();
    void deleteClass();
    void updateClass();

    // Teacher Assessment Management
    void addAssessment(string name, string details);
    void retrieveAssessments();
    void updateAssessment(string assessmentID, string newName, string newDetails);
    void deleteAssessment(string assessmentID);

    // Teacher Class Management
    void assignStudentToClass(string studentID, string classID);
    void retrieveClassList();
    void updateClassSchedule(string classID, string newSchedule);
    void deleteClassSchedule(string scheduleID);

    // Teacher Grade Management
    void addGrade(string studentID, string assessmentID, string grade);
    void retrieveGrades(string studentID);
    void updateGrade(string gradeID, string newGrade);
    void deleteGrade(string gradeID);


    // Student Information
    void retrieveStudentInfo(string studentID);


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
    string continue1;
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
        cin >> continue1;
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}

void sarmsdb::retrieveAdmin(){
    string continue1;
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
        cin >> continue1;
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveTeacher(){
    string continue1;
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
        cin >> continue1;
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveParent(){
    string continue1;
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
        cin >> continue1;
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveStudent(){
    string continue1;
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
        cin >> continue1;
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
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
    string continue1;
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
        cin >> continue1;
        
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
    
}
void sarmsdb::retrieveUserByUsername(string &username){
    string role,continue1;
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
            cin >> continue1;
            
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
            cin >> continue1;
            
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
            cin >> continue1;
            
        }
    }
    
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
    }
}
void sarmsdb::retrieveUserByName(string &name){
    string continue1;
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
        cin >> continue1;
        
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
        cin >> continue1;
        
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
        cin >> continue1;
        
    }
}

void sarmsdb::deleteUser(string UserID){
    string query = "DELETE FROM useraccounts WHERE UserID = '" + UserID + "'";
    queryDB(query);

}
void sarmsdb::updateUser(string &username,string &role,string &userID, string &newName, string &newPhone, string &newDob, string &newAddress,string &parentid){
    string query= "select";

}
void sarmsdb::updateUseraccounts(string &userID,string &newUsername,string &newPassword){
    string query;
    if (newUsername.length()>0)
    {
        query = "update useraccounts set Username = '" +newUsername+ "' wehere UserID = " +userID;
        queryDB(query);
    }
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
void sarmsdb::updateStudent(string &userID,string &newName,string &newPhone, string &newDob, string &newAddress, string &parentid){
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
    if(parentid.length()>0){
        query = "update student set ParentID = '" + newAddress + "' where UserID = " + userID ;
        queryDB(query);
    }
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

// Teacher Assessment Management
void sarmsdb::addAssessment(string name, string details) {
    string query = "INSERT INTO assessments (Name, Details) VALUES ('" + name + "', '" + details + "')";
    queryDB(query);
}

void sarmsdb::retrieveAssessments() {
    string query = "SELECT * FROM assessments";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                cout << row[i] << " ";
            }
            cout << endl;
        }
        mysql_free_result(result);
    } else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}

void sarmsdb::updateAssessment(string assessmentID, string newName, string newDetails) {
    string query = "UPDATE assessments SET Name = '" + newName + "', Details = '" + newDetails + "' WHERE AssessmentID = " + assessmentID;
    queryDB(query);
}

void sarmsdb::deleteAssessment(string assessmentID) {
    string query = "DELETE FROM assessments WHERE AssessmentID = " + assessmentID;
    queryDB(query);
}

// Teacher Class Management
void sarmsdb::assignStudentToClass(string studentID, string classID) {
    string query = "INSERT INTO class_assignments (StudentID, ClassID) VALUES ('" + studentID + "', '" + classID + "')";
    queryDB(query);
}

void sarmsdb::retrieveClassList() {
    string query = "SELECT * FROM class_assignments";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                cout << row[i] << " ";
            }
            cout << endl;
        }
        mysql_free_result(result);
    } else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}

void sarmsdb::updateClassSchedule(string classID, string newSchedule) {
    string query = "UPDATE classes SET Schedule = '" + newSchedule + "' WHERE ClassID = " + classID;
    queryDB(query);
}

void sarmsdb::deleteClassSchedule(string scheduleID) {
    string query = "DELETE FROM class_schedules WHERE ScheduleID = " + scheduleID;
    queryDB(query);
}

// Teacher Grade Management
void sarmsdb::addGrade(string studentID, string assessmentID, string grade) {
    string query = "INSERT INTO grades (StudentID, AssessmentID, Grade) VALUES ('" + studentID + "', '" + assessmentID + "', '" + grade + "')";
    queryDB(query);
}

void sarmsdb::retrieveGrades(string studentID) {
    string query = "SELECT * FROM grades WHERE StudentID = '" + studentID + "'";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                cout << row[i] << " ";
            }
            cout << endl;
        }
        mysql_free_result(result);
    } else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}

void sarmsdb::updateGrade(string gradeID, string newGrade) {
    string query = "UPDATE grades SET Grade = '" + newGrade + "' WHERE GradeID = " + gradeID;
    queryDB(query);
}

void sarmsdb::deleteGrade(string gradeID) {
    string query = "DELETE FROM grades WHERE GradeID = " + gradeID;
    queryDB(query);
}


// Student Information
void sarmsdb::retrieveStudentInfo(string studentID) {
    string query = "SELECT * FROM students WHERE StudentID = '" + studentID + "'";
    queryDB(query);
    result = mysql_store_result(conn);
    if (result) {
        numfields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result))) {
            for (int i = 0; i < numfields; i++) {
                cout << row[i] << " ";
            }
            cout << endl;
        }
        mysql_free_result(result);
    } else {
        cerr << "Error retrieving data: " << mysql_error(conn) << endl;
    }
}