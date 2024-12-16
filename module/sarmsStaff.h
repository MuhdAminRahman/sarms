#ifndef SARMSSTAFF_H
#define SARMSSTAFF_H

class sarmsStaff
{
private:
    sarmsUI* uiS;
    sarmsdb* dbS;
public:
    sarmsStaff(sarmsdb &db, sarmsUI &ui);
    ~sarmsStaff();
    void checkCin();
    void clearScreen();

    void manageStaffTasks();

    void createTeacher();
    void retrieveTeacher();
    void updateTeacher();
    void deleteTeacher();

    void createParent();
    void retrieveParent();
    void updateParent();
    void deleteParent();

    void createStudent();
    void retrieveStudent();
    void updateStudent();
    void deleteStudent();
};

#endif

sarmsStaff::sarmsStaff(sarmsdb &db, sarmsUI &ui) {
    dbS = &db;
    uiS = &ui;
}

sarmsStaff::~sarmsStaff() {
}

void sarmsStaff::checkCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void sarmsStaff::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sarmsStaff::manageStaffTasks() {
    try {
        int choice;
        do {
            clearScreen();
            uiS->printMenuName();  // Create this function in sarmsUI to print the staff menu
            cin >> choice;
            switch (choice) {
                case 1:
                    createTeacher();
                    break;
                case 2:
                    retrieveTeacher();
                    break;
                case 3:
                    updateTeacher();
                    break;
                case 4:
                    deleteTeacher();
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

void sarmsStaff::createTeacher() {
    string username, password, name, phoneno;
    checkCin();
    
    cout << "Username: ";           getline(cin, username);
    while (dbS->checkUsername(username)) {
        cout << "\nUsername is already taken, please insert a new one: ";
        getline(cin, username);
    }
    cout << "\nPassword: ";        getline(cin, password);
    cout << "\nFull name: ";       getline(cin, name);
    cout << "\nPhone number: ";    getline(cin, phoneno);
    dbS->addUser(username, password, "Teacher", name, phoneno, "NULL", "NULL", "Teacher");
}

void sarmsStaff::retrieveTeacher() {
    dbS->retrieveTeacher();
}

void sarmsStaff::updateTeacher() {
    string username, UserID;
    checkCin();
    
    cout << "Enter username of the teacher to update: "; getline(cin, username);
    if (dbS->checkUsername(username)) {
        dbS->retrieveUserID(username, UserID);
        // Add code to update teacher details
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}

void sarmsStaff::deleteTeacher() {
    string username, UserID;
    checkCin();
    
    cout << "Enter username of the teacher to delete: "; getline(cin, username);
    if (dbS->checkUsername(username)) {
        dbS->retrieveUserID(username, UserID);
        dbS->deleteUser(UserID);
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}

void sarmsStaff::createParent() {
    string username, password, name, phoneno;
    checkCin();

    cout << "Username: ";           getline(cin, username);
    while (dbS->checkUsername(username)) {
        cout << "\nUsername is already taken, please insert a new one: ";
        getline(cin, username);
    }
    cout << "\nPassword: ";        getline(cin, password);
    cout << "\nFull name: ";       getline(cin, name);
    cout << "\nPhone number: ";    getline(cin, phoneno);
    dbS->addUser(username, password, "Parent", name, phoneno, "NULL", "NULL", "NULL");
}

void sarmsStaff::retrieveParent() {
    dbS->retrieveParent();
}

void sarmsStaff::updateParent() {
    string username, UserID;
    checkCin();
    
    cout << "Enter username of the parent to update: "; getline(cin, username);
    if (dbS->checkUsername(username)) {
        dbS->retrieveUserID(username, UserID);
        // Add code to update parent details
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}

void sarmsStaff::deleteParent() {
    string username, UserID;
    checkCin();
    
    cout << "Enter username of the parent to delete: "; getline(cin, username);
    if (dbS->checkUsername(username)) {
        dbS->retrieveUserID(username, UserID);
        dbS->deleteUser(UserID);
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}

void sarmsStaff::createStudent() {
    string username, password, name, phoneno, dob, address;
    checkCin();

    cout << "Username: ";           getline(cin, username);
    while (dbS->checkUsername(username)) {
        cout << "\nUsername is already taken, please insert a new one: ";
        getline(cin, username);
    }
    cout << "\nPassword: ";        getline(cin, password);
    cout << "\nFull name: ";       getline(cin, name);
    cout << "\nPhone number: ";    getline(cin, phoneno);
    cout << "\nDate of birth (YYYY-MM-DD): "; getline(cin, dob);
    cout << "\nAddress: ";         getline(cin, address);
    dbS->addUser(username, password, "Student", name, phoneno, dob, address, "NULL");
}

void sarmsStaff::retrieveStudent() {
    dbS->retrieveStudent();
}

void sarmsStaff::updateStudent() {
    string username, UserID;
    checkCin();
    
    cout << "Enter username of the student to update: "; getline(cin, username);
    if (dbS->checkUsername(username)) {
        dbS->retrieveUserID(username, UserID);
        // Add code to update student details
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}

void sarmsStaff::deleteStudent() {
    string username, UserID;
    checkCin();

    cout << "Enter username of the student to delete: "; getline(cin, username);
    if (dbS->checkUsername(username)) {
        dbS->retrieveUserID(username, UserID);
        dbS->deleteUser(UserID);
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}
