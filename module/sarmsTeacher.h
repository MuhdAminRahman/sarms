#ifndef SARMSTEACHER_H
#define SARMSTEACHER_H

class sarmsTeacher
{
private:
    sarmsUI* uiT;
    sarmsdb* dbT;
public:
    sarmsTeacher(sarmsdb &db, sarmsUI &ui);
    ~sarmsTeacher();
    void checkCin();
    void clearScreen();

    // Implement necessary functionalities for teachers
    void manageTeacherTasks();  // For teacher-specific tasks
    void createAssessment();    // For creating assessments
    void retrieveAssessment();  // For retrieving assessments
    
    void updateAssessment();    // For updating assessments
    void deleteAssessment();    // For deleting assessments

    void manageClasses();       // For managing classes
    void viewClassSchedule();
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

void sarmsTeacher::manageTeacherTasks() {
    try {
        int choice;
        do {
            clearScreen();
            uiT->printTeacherPage();  // Create this function in sarmsUI to print the teacher menu
            cin >> choice;
            switch (choice) {
                case 1:
                    createAssessment();
                    break;
                case 2:
                    retrieveAssessment();
                    break;
                case 3:
                    updateAssessment();
                    break;
                case 4:
                    deleteAssessment();
                    break;
                case 5:
                    manageClasses();
                    break;
                case 6:
                    // Return to main menu
                    break;
                default:
                    cout << "Please insert the number shown above.\n";
                    checkCin();
                    break;
            }
        } while (choice != 6);
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
}

void sarmsTeacher::createAssessment() {
    string name, details;
    checkCin();

    cout << "Enter assessment name: "; getline(cin, name);
    cout << "Enter assessment details: "; getline(cin, details);
    
    dbT->addAssessment(name, details);
}

void sarmsTeacher::retrieveAssessment() {
    dbT->retrieveAssessments();
}

void sarmsTeacher::updateAssessment() {
    string assessmentID, newName, newDetails;
    checkCin();

    cout << "Enter assessment ID to update: "; getline(cin, assessmentID);
    cout << "Enter new assessment name: "; getline(cin, newName);
    cout << "Enter new assessment details: "; getline(cin, newDetails);

    dbT->updateAssessment(assessmentID, newName, newDetails);
}

void sarmsTeacher::deleteAssessment() {
    string assessmentID;
    checkCin();

    cout << "Enter assessment ID to delete: "; getline(cin, assessmentID);
    
    dbT->deleteAssessment(assessmentID);
}

void sarmsTeacher::manageClasses() {
    int choice;
    try {
        do {
            clearScreen();
            uiT->printTeacherClass(); // Create this function in sarmsUI to print the class management menu
            cin >> choice;

            switch (choice) {
                case 1:
                    viewClassSchedule();
                    break;
                case 2:
                    viewClassList();
                    break;
                case 3:
                    // Return to previous menu
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

void sarmsTeacher::viewClassSchedule() {
    dbT->retrieveClassList();
}

void sarmsTeacher::viewClassList() {
    dbT->retrieveClassList();
}