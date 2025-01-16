#ifndef SARMSSTAFF_H
#define SARMSSTAFF_H

class sarmsStaff
{
private:
    sarmsUI* uiS;
    sarmsdb* dbS;
    string mystaffID;
public:
    sarmsStaff(sarmsdb &db, sarmsUI &ui);
    ~sarmsStaff();
    void checkCin();
    void clearScreen();

    void setStaffID(string &staffID);
    void manageStaffTasks();

    // User Management
    void manageUsers();  // Manage all user roles

    void chooseUserRole(string &role);

    void createUser();  // done

    void searchUser();  // done
    void searchByRole(); //done
    void searchByUsername(); //done
    void searchByName(); //done

    void updateUser();  // Update user details

    void deleteUser();  // Delete a user


    void viewPaymentReport();
    void viewAssessmentReport();
    void viewUnpaidTuitionReport();

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

void sarmsStaff::setStaffID(string &staffID) {
    mystaffID = staffID;
}

void sarmsStaff::manageStaffTasks() {
    try {
        int choice;
        do {
            clearScreen();
            uiS->printStaffPage();  // Create this function in sarmsUI to print the staff menu
            cin >> choice;
            switch (choice) {
                case 1:
                    manageUsers();
                    break;
                case 2:
                    //manageTuition();
                    break;
                case 3:
                    //manageAssessment();
                    break;
                case 4:
                    //manageClass();
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

void sarmsStaff::manageUsers() {
    try {
        int choice;
        do {
            clearScreen();
            uiS->printAdminUserManagement();  // Create this function in sarmsUI to print the user management menu
            
            cin >> choice;
            switch (choice) {
                case 1:
                    createUser();
                    break;
                case 2:
                    searchUser();
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
            checkCin();
        } while (choice != 5);
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
}

void sarmsStaff::chooseUserRole(string &role){
    int choice;
    do
    {
        //print choice
        clearScreen();
        uiS->printStaffChooseRole();
        checkCin();
        cin >> choice;
        switch (choice)
        {
        case 1:
            role = "Teacher";
            break;
        case 2:
            role ="Parent";
            break;
        case 3:
            role = "Student";
            break;
        default:
            cout << "\nError please type in the number of the role you want choose";
            break;
        }
    } while (choice < 1 || choice > 5);
    
}

void sarmsStaff::createUser() {
    string username, password, role, name, phoneno, dob, address, designation;

    chooseUserRole(role);
    checkCin();
    cout << "Enter username: "; getline(cin, username);
    while (dbS->checkUsername(username)) {
        cout << "\nUsername is already taken, please insert a new one: ";
        getline(cin, username);
    }
    cout << "\nEnter password: "; getline(cin, password);

    if (role == "Teacher")
    {
        cout << "\nEnter full name: "; getline(cin, name);
        cout << "\nEnter phone number: "; getline(cin, phoneno);
        designation = role;
        dbS->addUser(username, password, role, name, phoneno, dob, address, designation);
        if (role == "Teacher")
        {
            string subjectID;
            dbS->retrieveSubject();
            cout << "\nEnter the Subject ID to assign to the Teacher: ";
            getline(cin,subjectID);
            dbS->setSubjectToTeacher(subjectID);

        }
    }
    else if(role =="Parent"){
        string studentname;
        string studentID;
        string parentID;
        cout << "\nEnter full name: "; getline(cin, name);
        cout << "\nEnter phone number: "; getline(cin, phoneno);
        //implement parent child assignment
        dbS->addUser(username, password, role, name, phoneno, dob, address, designation);
        dbS->getLastInsertID(parentID);
        cout << "\nEnter their child's name : ";
        getline(cin,studentname);
        dbS->retrieveStudentByName(studentname);
        cout << "\nEnter the StudentID of the child you want to set the parent to: ";
        getline(cin,studentID);
        dbS->setParentToStudent(parentID,studentID);
        
    }
    else if(role == "Student"){
        string studentID;
        string classID;
        cout << "\nEnter full name: "; getline(cin, name);
        cout << "\nEnter phone number: "; getline(cin, phoneno);
        cout << "\nEnter date of birth (YYYY-MM-DD): "; getline(cin, dob);
        cout << "\nEnter address: "; getline(cin, address);
        dbS->addUser(username, password, role, name, phoneno, dob, address, designation);
        dbS->getLastInsertID(studentID);
        cout << "StudentID :" << studentID << endl;
        dbS->setStudentTuition(studentID);
        dbS->retrieveClassList();
        cout << "\nEnter the Class ID of the class you want to assign the student to: ";
        getline(cin,classID);
        dbS->assignStudentToClass(classID,studentID);
        dbS->createAssessment(studentID);
    }
}

void sarmsStaff::searchUser() {
   
    string username, name,role;

    //search by username
    //search by Full name
    //search by Role
    try {
        int choice;
        do {
            clearScreen();
            uiS->printAdminSearchUser();  
            checkCin();
            cin >> choice;
            switch (choice) {
                case 1:
                    searchByRole();
                    break;
                case 2:
                    searchByUsername();
                    break;
                case 3:
                    searchByName();
                    break;
                case 4:
                    // Return to main menu
                    break;
                default:
                    cout << "Please insert the number shown above.\n";
                    break;
            }
        } while (choice != 4);
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
}

void sarmsStaff::searchByRole(){
    string role;
    chooseUserRole(role);
    dbS->staffretrieveUserbyRole(role);
}
void sarmsStaff::searchByUsername(){
    string username;
    cout << "\nPlease enter the username you want to search : ";
    checkCin();
    getline(cin,username);
    cout << "Username is : " << username;
    dbS->staffretrieveUserbyUsername(username);

}
void sarmsStaff::searchByName(){
    string name;
    cout << "\nPlease enter the Name you want to search : ";
    checkCin();
    getline(cin,name);
    dbS->staffretrieveUserbyName(name);
}

void sarmsStaff::updateUser() {
    int choice;
    string username,role;
    string userID,newPassword, newName, newPhone, newDob, newAddress, newRole, newDesignation;
    checkCin();

    dbS->retrieveAllUser();
    cout << "\nEnter username of the user to update: ";
    checkCin();
    getline(cin, username);
    if (dbS->checkUsername(username)) {
        dbS->retrieveRole(username,role);
        dbS->retrieveUserID(username,userID);
        dbS->retrieveUserByUsername(username);
        checkCin();

        if(role == "Teacher"){
            
            do
            {
                uiS->printAdminUpdateStaff();
                checkCin();
                cin >> choice;
                switch (choice)
                {
                case 1:
                    checkCin();
                    cout << "\nEnter new Password: "; getline(cin, newPassword);
                    break;
                case 2:
                    checkCin();
                    cout << "\nEnter new full name: "; getline(cin, newName);
                    break;
                case 3:
                    checkCin();
                    cout << "\nEnter new phone number: "; getline(cin, newPhone);
                    break;
                case 4:
                    //Done
                    break;
                default:
                    cout << "\nPlease enter the number listed.";
                    break;
                }
            } while (choice != 4);
            dbS->updateUseraccounts(userID,newPassword);
            dbS->updateStaff(userID,newName,newPhone);
        }
        else if (role == "Parent")
        {
            do
            {
                uiS->printAdminUpdateParent();
                checkCin();
                cin >> choice;
                switch (choice)
                {
                case 1:
;                   checkCin();
                    cout << "\nEnter new Password: "; getline(cin, newPassword);
                    break;
                case 2:
                    checkCin();
                    cout << "\nEnter new full name: "; getline(cin, newName);
                    break;
                case 3:
                    checkCin();
                    cout << "\nEnter new phone number: "; getline(cin, newPhone);
                    break;
                case 4:
                    //done
                    break;
                default:
                    cout << "\nPlease enter the number listed.";
                    break;
                }
            } while (choice != 4);

            dbS->updateUseraccounts(userID,newPassword);
            dbS->updateParent(userID,newName,newPhone);
        }
        else if (role == "Student")
        {
            do
            {
                uiS->printAdminUpdateStudent();
                checkCin();
                cin >> choice;
                switch (choice)
                {
                case 1:
                    checkCin();
                    cout << "\nEnter new Password: "; getline(cin, newPassword);
                    break;
                case 2:
                    checkCin();
                    cout << "\nEnter new full name: "; getline(cin, newName);
                    break;
                case 3:
                    checkCin();
                    cout << "\nEnter new phone number: "; getline(cin, newPhone);
                    break;
                case 4:
                    checkCin();
                    cout << "\nEnter new date of birth (YYYY-MM-DD): "; getline(cin, newDob);
                    break;
                case 5:
                    checkCin();
                    cout << "\nEnter new address: "; getline(cin, newAddress);
                    break; 
                case 6:
                    //done
                    break;
                default:
                    cout << "\nPlease enter the number listed.";
                    break;
                }
            } while (choice != 6);
            dbS->updateUseraccounts(userID,newPassword);
            dbS->updateStudent(userID,newName,newPhone,newDob,newAddress);
        }
        else{
            cout << "\nUser does not have a role.";
        }
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}

void sarmsStaff::deleteUser() {
    string username, userID;
    checkCin();

    cout << "Enter username of the user to delete: "; getline(cin, username);
    if (dbS->checkUsername(username)) {
        dbS->retrieveUserID(username, userID);
        dbS->deleteUser(userID);
    } else {
        cout << "\nUser doesn't exist, please try again.";
    }
}