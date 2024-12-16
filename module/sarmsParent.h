#ifndef SARMSPARENT_H
#define SARMSPARENT_H

class sarmsParent
{
private:
    sarmsUI* uiP;
    sarmsdb* dbP;
public:
    sarmsParent(sarmsdb &db, sarmsUI &ui);
    ~sarmsParent();
    void checkCin();
    void clearScreen();

    void manageParentTasks();  // Main menu for parent tasks
    void viewTuitionDetails();  // View tuition details
    void viewPaymentHistory();  // View payment history
    void viewChildSchedule();  // View child's class schedule
    void viewChildPerformance();  // View child's performance (assessments and attendance)
};

#endif

sarmsParent::sarmsParent(sarmsdb &db, sarmsUI &ui) {
    dbP = &db;
    uiP = &ui;
}

sarmsParent::~sarmsParent() {
}

void sarmsParent::checkCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void sarmsParent::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sarmsParent::manageParentTasks() {
    try {
        int choice;
        do {
            clearScreen();
            uiP->printParentPage();  // Create this function in sarmsUI to print the parent menu
            cin >> choice;
            switch (choice) {
                case 1:
                    viewTuitionDetails();
                    break;
                case 2:
                    viewPaymentHistory();
                    break;
                case 3:
                    viewChildSchedule();
                    break;
                case 4:
                    viewChildPerformance();
                    break;
                case 5:
                    // Return to main menu
                    break;
                default:
                    cout << "Please insert the number shown above.\n";
                    checkCin();
                    break;
            }
        } while (choice != 5);
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
}

void sarmsParent::viewTuitionDetails() {
    string studentID;
    checkCin();

    cout << "Enter your child's student ID: "; getline(cin, studentID);
    dbP->retrieveTuitionDetails();
}

void sarmsParent::viewPaymentHistory() {
    string studentID;
    checkCin();

    cout << "Enter your child's student ID: "; getline(cin, studentID);
    dbP->retrievePaymentHistory(studentID);
}

void sarmsParent::viewChildSchedule() {
    string studentID;
    checkCin();

    cout << "Enter your child's student ID: "; getline(cin, studentID);
    dbP->retrieveClassSchedule(studentID);
}

void sarmsParent::viewChildPerformance() {
    string studentID;
    checkCin();

    cout << "Enter your child's student ID: "; getline(cin, studentID);
    dbP->retrieveChildPerformance(studentID);
}
