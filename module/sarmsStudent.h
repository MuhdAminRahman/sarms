#ifndef SARMSSTUDENT_H
#define SARMSSTUDENT_H

class sarmsStudent
{
private:
    sarmsUI* uiSt;
    sarmsdb* dbSt;
public:
    sarmsStudent(sarmsdb &db, sarmsUI &ui);
    ~sarmsStudent();
    void checkCin();
    void clearScreen();

    void manageStudentTasks();  // Main menu for student tasks
    void viewGrades();  // View overall and specific grades
    void viewClassSchedule();  // View class schedule
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

void sarmsStudent::manageStudentTasks() {
    try {
        int choice;
        do {
            clearScreen();
            uiSt->printStudentPage();  // Create this function in sarmsUI to print the student menu
            cin >> choice;
            switch (choice) {
                case 1:
                    viewGrades();
                    break;
                case 2:
                    viewClassSchedule();
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

void sarmsStudent::viewGrades() {
    string studentID;
    checkCin();

    cout << "Enter your student ID: "; getline(cin, studentID);
    dbSt->retrieveGrades(studentID);
}

void sarmsStudent::viewClassSchedule() {
    string studentID;
    checkCin();

    cout << "Enter your student ID: "; getline(cin, studentID);
    //dbSt->retrieveClassSchedule(studentID);
}
