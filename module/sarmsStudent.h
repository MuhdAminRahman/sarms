#ifndef SARMSSTUDENT_H
#define SARMSSTUDENT_H

class sarmsStudent
{
private:
    sarmsUI* uiSt;
    sarmsdb* dbSt;
    string mystudentID;
public:
    sarmsStudent(sarmsdb &db, sarmsUI &ui);
    ~sarmsStudent();
    void checkCin();
    void clearScreen();

    void setStudentID(string &studentID);

    void manageStudentTasks();  // Main menu for student tasks
};

#endif

sarmsStudent::sarmsStudent(sarmsdb &db, sarmsUI &ui) {
    dbSt = &db;
    uiSt = &ui;
}

sarmsStudent::~sarmsStudent() {
}

void sarmsStudent::checkCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void sarmsStudent::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sarmsStudent::setStudentID(string &studentID) {
    mystudentID = studentID;
}

void sarmsStudent::manageStudentTasks() {
    try {
        int choice;
        do {
            clearScreen();
            uiSt->printStudentPage();  // Create this function in sarmsUI to print the student menu
            cin >> choice;
            switch (choice) {
                case 1:
                    checkCin();
                    dbSt->retrieveStudentAssessment(mystudentID);
                    break;
                case 2:
                    checkCin();
                    dbSt->retrieveStudentClassSchedule(mystudentID);
                    break;
                case 3:
                    // Return to main menu
                    break;
                default:
                    cout << "Please insert the number shown above.\n";
                    checkCin();
                    break;
            }
        } while (choice != 3);
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
}
