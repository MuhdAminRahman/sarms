#ifndef SARMSTEACHER_H
#define SARMSTEACHER_H

class sarmsTeacher
{
private:
    sarmsUI* uiT;
    sarmsdb* dbT;
    string myteacherID;
public:
    sarmsTeacher(sarmsdb &db, sarmsUI &ui);
    ~sarmsTeacher();
    void checkCin();
    void clearScreen();

    void setTeacherID(string &teacherID);

    // Implement necessary functionalities for teachers
    void manageTeacherTasks();  // For teacher-specific tasks
    void retrieveAssessment();  // For retrieving assessments
    void updateAssessment();    // For updating assessments

    void manageClasses();       // For managing classes
    void viewClassSchedule(string &classID);  // For viewing class schedule
    void viewClassList();
};

#endif

sarmsTeacher::sarmsTeacher(sarmsdb &db, sarmsUI &ui) {
    dbT = &db;
    uiT = &ui;
}

sarmsTeacher::~sarmsTeacher() {
}

void sarmsTeacher::checkCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void sarmsTeacher::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sarmsTeacher::setTeacherID(string &teacherID) {
    myteacherID = teacherID;
}

void sarmsTeacher::manageTeacherTasks() {
    try {
        int choice;
        do {
            clearScreen();
            uiT->printTeacherPage();  // Create this function in sarmsUI to print the teacher menu
            cin >> choice;
            switch (choice) {
                case 1:
                    retrieveAssessment();
                    break;
                case 2:
                    updateAssessment();
                    break;
                case 3:
                    manageClasses();
                    break;
                case 4:
                    // Return to main menu
                    break;
                default:
                    cout << "Please insert the number shown above.\n";
                    checkCin();
                    break;
            }
        } while (choice != 4);
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
}


void sarmsTeacher::retrieveAssessment() {
    string studentID;
    dbT->retrieveStudentForAssessment(myteacherID);
    checkCin();
    cout << "Enter student ID to retrieve assessments: "; getline(cin, studentID);
    dbT->retrieveAssessments(studentID,myteacherID);
}

void sarmsTeacher::updateAssessment() {
    string studentID, staffID, subjectID,score,remarks;
    
    bool continue1=true;

    checkCin();
    dbT->retrieveStudentForAssessment(myteacherID);
    cout << "\nEnter student ID to update assessment: ";
    checkCin();
    getline(cin, studentID);
    cout << "\nStudent ID is: " << studentID;
    while(continue1){
        checkCin();
        dbT->retrieveAssessments(studentID,myteacherID);
        checkCin();
        cout << "\nEnter subject ID to update assessment: "; getline(cin, subjectID);
        cout << "\nEnter score: "; getline(cin, score);
        cout << "\nEnter remarks: "; getline(cin, remarks);
        dbT->updateAssessment(studentID,myteacherID,subjectID,score,remarks);
        cout << "\nDo you want to update another subject? (1 for yes, 0 for no): "; 
        checkCin();
        cin >> continue1;
    }
    

}


void sarmsTeacher::manageClasses() {
    bool continue1=true;
    string classID;
    
    while(continue1){
        dbT->retrieveTeacherClassList(myteacherID);
        cout << "\nEnter class ID to view schedule: ";
        checkCin();
        getline(cin, classID);
        viewClassSchedule(classID);
        cout << "\nDo you want to manage another class? (1 for yes, 0 for no): "; 
        checkCin();
        cin >> continue1;
    }
}

void sarmsTeacher::viewClassSchedule(string &classID) {
    dbT->retrieveSubjectSchedule(classID);
}

void sarmsTeacher::viewClassList() {
    dbT->retrieveClassList();
}