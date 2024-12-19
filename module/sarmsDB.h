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
    void connectdb();
    void closedb();
    void queryDB(string &query);

    // User verification
    bool verifyLogin(string &username, string &password, string &role);
    bool checkUsername(string &username);

    // Admin User Management
    void addUser(string username, string password, string role, string name, string phoneno, string dob, string address, string designation);
    void retrieveAllUser();
    void retrieveAdmin();
    void retrieveTeacher();
    void retrieveParent();
    void retrieveStudent();
    void retrieveUserID(string &username, string &UserID);
    void retrieveUserByRole(string &role);

    void deleteUser(string username);
    void updateUser(string userID, string newName, string newPhone, string newDob, string newAddress, string newRole, string newDesignation);

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

void sarmsdb::retrieveAdmin(){
    string query = "SELECT * FROM useraccounts JOIN staff using (UserID) where Role = 'Admin'";
    queryDB(query);
    result = mysql_store_result(conn);
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
void sarmsdb::retrieveTeacher(){
    string query = "SELECT * FROM useraccounts JOIN staff using (UserID) where Role = 'Teacher'";
    queryDB(query);
    result = mysql_store_result(conn);
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
void sarmsdb::retrieveParent(){
    string query = "SELECT * FROM useraccounts JOIN parent using (UserID) where Role = 'Parent'";
    queryDB(query);
    result = mysql_store_result(conn);
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
void sarmsdb::retrieveStudent(){
    string query = "SELECT * FROM useraccounts JOIN student using (UserID) where Role = 'Student'";
    queryDB(query);
    result = mysql_store_result(conn);
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
        /*numfields = mysql_num_fields(result);
        fields = mysql_fetch_fields(result);
        for(int i=0; i<numfields;i++){
            cout << fields[i].name << " ";
        }
        cout << endl;
        while((row = mysql_fetch_row(result))){
            for(int i = 0;i<numfields;i++){
                if(row[i]){
                    cout << "| "  << row[i] << " |";
                }
                else{
                    cout << "| "  << "NULL" << " |";
                }
            }
            cout << endl;
        }*/
        mysql_free_result(result);
        cout << "+-------------------+" << endl;
        cout << "\nEnter anything to continue : ";
        cin >> continue1;
        
    }
    else
    {
        cerr << "Error retrieving data : " << mysql_error(conn) << endl;
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