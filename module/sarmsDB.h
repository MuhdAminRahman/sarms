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

    // Parent Communication
    void sendMessageToParent(string parentID, string message);

    // Student Information
    void retrieveStudentInfo(string studentID);

    // New Parent Communication
    void addMessage(string parentID, string message);
    void retrieveMessages(string parentID);
    void deleteMessage(string messageID);

    // System Configuration, Data Backup, and Recovery
    void configureSystem();
    void backupData();
    void restoreData();

    // Report Generation
    void generateReports();

    // Audit and Logging
    void auditLogs();

    // Notification Management
    void manageNotifications();
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

// Parent Communication
void sarmsdb::sendMessageToParent(string parentID, string message) {
    string query = "INSERT INTO messages (ParentID, Message) VALUES ('" + parentID + "', '" + message + "')";
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


// New Parent Communication
void sarmsdb::addMessage(string parentID, string message) {
    string query = "INSERT INTO messages (ParentID, Message) VALUES ('" + parentID + "', '" + message + "')";
    queryDB(query);
}

void sarmsdb::retrieveMessages(string parentID) {
    string query = "SELECT * FROM messages WHERE ParentID = '" + parentID + "'";
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
        cerr << "Error retrieving messages: " << mysql_error(conn) << endl;
    }
}

void sarmsdb::deleteMessage(string messageID) {
    string query = "DELETE FROM messages WHERE MessageID = " + messageID;
    queryDB(query);
}

// System Configuration, Data Backup, and Recovery
void sarmsdb::configureSystem() {
    // Implementation for configuring system settings
    cout << "System configuration functionality coming soon!" << endl;
}

void sarmsdb::backupData() {
    // Implementation for backing up data
    cout << "Data backup functionality coming soon!" << endl;
}

void sarmsdb::restoreData() {
    // Implementation for restoring data
    cout << "Data restore functionality coming soon!" << endl;
}

// Report Generation
void sarmsdb::generateReports() {
    // Implementation for generating and exporting reports
    cout << "Report generation functionality coming soon!" << endl;
}

// Audit and Logging
void sarmsdb::auditLogs() {
    // Implementation for monitoring system logs
    cout << "Audit and logging functionality coming soon!" << endl;
}

// Notification Management
void sarmsdb::manageNotifications() {
    // Implementation for managing notifications and alerts
    cout << "Notification management functionality coming soon!" << endl;
}
