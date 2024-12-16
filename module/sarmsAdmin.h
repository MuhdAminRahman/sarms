#ifndef SARMSADMIN_H
#define SARMSADMIN_H

class sarmsAdmin
{
private:
    sarmsUI* uiA;
    sarmsdb* dbA;
public:
    sarmsAdmin(sarmsdb &db, sarmsUI &ui);
    ~sarmsAdmin();
    void checkCin();
    void clearScreen();

    // User Management
    void manageUsers();  // Manage all user roles
    void createUser();  // Create a new user
    void retrieveUsers();  // Retrieve users
    void updateUser();  // Update user details
    void deleteUser();  // Delete a user

    // System Configuration
    void configureSystem();  // Configure system settings

    // Data Backup and Recovery
    void backupData();  // Backup database
    void restoreData();  // Restore data from backups

    // Report Generation
    void generateReports();  // Generate and export reports

    // Audit and Logging
    void auditLogs();  // Monitor system logs

    // Notification Management
    void manageNotifications();  // Manage notifications and alerts
};

#endif

sarmsAdmin::sarmsAdmin(sarmsdb &db, sarmsUI &ui) {
    dbA = &db;
    uiA = &ui;
}

sarmsAdmin::~sarmsAdmin() {
}

void sarmsAdmin::checkCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void sarmsAdmin::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sarmsAdmin::manageUsers() {
    try {
        int choice;
        do {
            clearScreen();
            uiA->printAdminUserManagement();  // Create this function in sarmsUI to print the user management menu
            cin >> choice;
            switch (choice) {
                case 1:
                    createUser();
                    break;
                case 2:
                    retrieveUsers();
                    break;
                case 3:
                    updateUser();
                    break;
                case 4:
                    deleteUser();
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

void sarmsAdmin::createUser() {
    string username, password, role, name, phoneno, dob, address, designation;
    checkCin();

    cout << "Enter username: "; getline(cin, username);
    while (dbA->checkUsername(username)) {
        cout << "\nUsername is already taken, please insert a new one: ";
        getline(cin, username);
    }
    cout << "\nEnter password: "; getline(cin, password);
    cout << "\nEnter full name: "; getline(cin, name);
    cout << "\nEnter phone number: "; getline(cin, phoneno);
    cout << "\nEnter date of birth (YYYY-MM-DD): "; getline(cin, dob);
    cout << "\nEnter address: "; getline(cin, address);
    cout << "\nEnter role (Admin, Staff, Teacher, Parent, Student): "; getline(cin, role);
    cout << "\nEnter designation (for Staff/Teacher roles): "; getline(cin, designation);

    dbA->addUser(username, password, role, name, phoneno, dob, address, designation);
}

void sarmsAdmin::retrieveUsers() {
    dbA->retrieveAllUser();
}

void sarmsAdmin::updateUser() {
    string username, userID, newName, newPhone, newDob, newAddress, newRole, newDesignation;
    checkCin();

    cout << "Enter username of the user to update: "; getline(cin, username);
    if (dbA->checkUsername(username)) {
        dbA->retrieveUserID(username, userID);
        cout << "\nEnter new full name: "; getline(cin, newName);
        cout << "\nEnter new phone number: "; getline(cin, newPhone);
        cout << "\nEnter new date of birth (YYYY-MM-DD): "; getline(cin, newDob);
        cout << "\nEnter new address: "; getline(cin, newAddress);
        cout << "\nEnter new role: "; getline(cin, newRole);
        cout << "\nEnter new designation: "; getline(cin, newDesignation);

        dbA->updateUser(userID, newName, newPhone, newDob, newAddress, newRole, newDesignation);
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}

void sarmsAdmin::deleteUser() {
    string username, userID;
    checkCin();

    cout << "Enter username of the user to delete: "; getline(cin, username);
    if (dbA->checkUsername(username)) {
        dbA->retrieveUserID(username, userID);
        dbA->deleteUser(userID);
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}

void sarmsAdmin::configureSystem() {
    // Implementation for configuring system settings
    cout << "System configuration functionality coming soon!" << endl;
}

void sarmsAdmin::backupData() {
    // Implementation for backing up data
    cout << "Data backup functionality coming soon!" << endl;
}

void sarmsAdmin::restoreData() {
    // Implementation for restoring data
    cout << "Data restore functionality coming soon!" << endl;
}

void sarmsAdmin::generateReports() {
    // Implementation for generating and exporting reports
    cout << "Report generation functionality coming soon!" << endl;
}

void sarmsAdmin::auditLogs() {
    // Implementation for monitoring system logs
    cout << "Audit and logging functionality coming soon!" << endl;
}

void sarmsAdmin::manageNotifications() {
    // Implementation for managing notifications and alerts
    cout << "Notification management functionality coming soon!" << endl;
}
