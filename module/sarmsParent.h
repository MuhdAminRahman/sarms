#ifndef SARMSPARENT_H
#define SARMSPARENT_H

class sarmsParent
{
private:
    sarmsUI* uiP;
    sarmsdb* dbP;
    string myparentID;
    string mychildID[10];
    int childcount = 0;

public:
    sarmsParent(sarmsdb &db, sarmsUI &ui);
    ~sarmsParent();
    void checkCin();
    void clearScreen();

    void setParentID(string &parentID);

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

void sarmsParent::setParentID(string &parentID) {
    myparentID = parentID;
}

void sarmsParent::manageParentTasks() {
    try {
        int choice;
        dbP->setChildID(mychildID, myparentID,childcount);
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

    string choice;
    string studentID;
    string tuitionID;
    float total;
    float amount;
    for(int i = 0; i < childcount; i++){
        dbP->retrieveTuitionDetails(mychildID[i]);
    }
    
    cout << "\nDo you want to make payments for the tuition? (Y/N): ";
    getline(cin, choice);
    if(choice == "Y" || choice == "y"){
        cout << "\nEnter your child's student ID: "; getline(cin, studentID);
        tuitionID = dbP->getTuitionID(studentID);
        total = dbP->getTotalTuitionAmount(tuitionID);
        cout << "\nTotal amount to pay: " << total << endl;
        cout <<"\nEnter the amount you want to pay: "; cin >> amount;
        checkCin();
        dbP->makePayment(studentID,tuitionID,amount);

    }
}

void sarmsParent::viewPaymentHistory() {
    checkCin();
    dbP->retrievePaymentHistory(myparentID);
}

void sarmsParent::viewChildSchedule() {
    checkCin();

    for(int i = 0; i < childcount; i++){
        dbP->retrieveStudentClassSchedule(mychildID[i]);
    }
}

void sarmsParent::viewChildPerformance() {
    checkCin();
    for(int i = 0; i < childcount; i++){
        dbP->retrieveStudentAssessment(mychildID[i]);
    }
}
