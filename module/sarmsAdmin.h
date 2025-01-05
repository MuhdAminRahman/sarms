#ifndef SARMSADMIN_H
#define SARMSADMIN_H


/* An Admin for Student Academic Record Management System is able to: 
    1. access User management module for any type of USER(Admin,Staff,Teacher,Parent,Student) CRUD operations
    2. access Subject Management Module for CRUD operatios.....cont
    3. access Tuition Management Module for Tuition CRUD operation and assigning 
    4. access Class Management Module for Class CRUD operations such as creating a class and assigning the teacher that handles the class
       and are able to manage th eclass Schedule for that specific class*/
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

    void MainMenu();

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

    
    ///////////////////////////////////////////////////////////////////////
    //Subject Management
    void manageSubjects();
    void addSubject();
    void updateSubject();

    
    ///////////////////////////////////////////////////////////////////////
    //Tuition Management
    void manageTuition();
    void updateTuition();
    void setStudentTuition();

    ///////////////////////////////////////////////////////////////////////
    //Class Management
    void manageClass();
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

void sarmsAdmin::MainMenu(){
    try
    {
        int choice;
        do
        {
            clearScreen();
            uiA->printAdminPage();
            cin >> choice;
            switch (choice)
            {
            case 1:
                manageUsers();
                break;
            case 2:
                manageSubjects();
                break;
            case 3:
                manageTuition();
                break;
            case 4:
                manageClass();
                break;
            case 5:
                //Log out
                break;
            default:
                cout << "Please insert the number shown above.\n";
                    checkCin();
                    break;
            }
        } while (choice != 5);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
void sarmsAdmin::manageUsers() {
    try {
        int choice;
        do {
            clearScreen();
            uiA->printAdminUserManagement();  // Create this function in sarmsUI to print the user management menu
            checkCin();
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
        } while (choice != 5);
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
}

void sarmsAdmin::chooseUserRole(string &role){
    int choice;
    do
    {
        //print choice
        clearScreen();
        uiA->printAdminChooseRole();
        cin >> choice;
        switch (choice)
        {
        case 1:
            role = "Admin";
            break;
        case 2:
            role = "Staff";
            break;
        case 3:
            role = "Teacher";
            break;
        case 4:
            role ="Parent";
            break;
        case 5:
            role = "Student";
            break;
        default:
            cout << "\nError please type in the number of the role you want choose";
            break;
        }
    } while (choice < 1 || choice > 5);
    
}

void sarmsAdmin::createUser() {
    string username, password, role, name, phoneno, dob, address, designation;

    chooseUserRole(role);
    checkCin();
    cout << "Enter username: "; getline(cin, username);
    while (dbA->checkUsername(username)) {
        cout << "\nUsername is already taken, please insert a new one: ";
        getline(cin, username);
    }
    cout << "\nEnter password: "; getline(cin, password);// implement secure password check

    if (role == "Admin" || role == "Staff" || role == "Teacher")
    {
        cout << "\nEnter full name: "; getline(cin, name);
        cout << "\nEnter phone number: "; getline(cin, phoneno);
        designation = role;
        dbA->addUser(username, password, role, name, phoneno, dob, address, designation);
        if (role == "Teacher")
        {
            string subjectID;
            dbA->retrieveSubject();
            cout << "\nEnter the Subject ID to assign to the Teacher: ";
            checkCin();
            getline(cin,subjectID);
            dbA->setSubjectToTeacher(subjectID);

        }
    }
    else if(role =="Parent"){
        string studentname;
        string studentID;
        cout << "\nEnter full name: "; getline(cin, name);
        cout << "\nEnter phone number: "; getline(cin, phoneno);
        //implement parent child assignment
        dbA->addUser(username, password, role, name, phoneno, dob, address, designation);
        cout << "\nEnter their child's name : ";
        getline(cin,studentname);
        dbA->retrieveStudentByName(studentname);
        cout << "\nEnter the StudentID of the child you want to set the parent to: ";
        getline(cin,studentID);
        dbA->setParentToStudent(studentID);
        
    }
    else if(role == "Student"){
        string studentID;
        string classID;
        cout << "\nEnter full name: "; getline(cin, name);
        cout << "\nEnter phone number: "; getline(cin, phoneno);
        cout << "\nEnter date of birth (YYYY-MM-DD): "; getline(cin, dob);
        cout << "\nEnter address: "; getline(cin, address);
        dbA->addUser(username, password, role, name, phoneno, dob, address, designation);
        dbA->getLastInsertID(studentID);
        cout << "StudentID :" << studentID << endl;
        dbA->setStudentTuition(studentID);
        dbA->retrieveClassList();
        cout << "\nEnter the Class ID of the class you want to assign the student to: ";
        getline(cin,classID);

        
    }

    
}

void sarmsAdmin::searchUser() {
   
    string username, name,role;

    //search by username
    //search by Full name
    //search by Role
    try {
        int choice;
        do {
            clearScreen();
            uiA->printAdminSearchUser();  // Create this function in sarmsUI to print the user management menu
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
                    checkCin();
                    break;
            }
        } while (choice != 4);
    } catch (const exception& e) {
        cerr << e.what() << '\n';
    }
}

void sarmsAdmin::searchByRole(){
    string role;
    chooseUserRole(role);
    dbA->retrieveUserByRole(role);
}
void sarmsAdmin::searchByUsername(){
    string username;
    cout << "\nPlease enter the username you want to search : ";
    checkCin();
    getline(cin,username);
    dbA->retrieveUserByUsername(username);

}
void sarmsAdmin::searchByName(){
    string name;
    cout << "\nPlease enter the Name you want to search : ";
    checkCin();
    getline(cin,name);
    dbA->retrieveUserByName(name);
}

void sarmsAdmin::updateUser() {
    string username, userID, newName, newPhone, newDob, newAddress, newRole, newDesignation;
    checkCin();

    dbA->retrieveAllUser();
    cout << "\nEnter username of the user to update: ";
    checkCin();
    getline(cin, username);
    if (dbA->checkUsername(username)) {
        dbA->retrieveRole(username,role);
        dbA->retrieveUserID(username,userID);
        dbA->retrieveUserByUsername(username);
        checkCin();

        if(role == "Admin" || role == "Staff" || role == "Teacher"){
            
            do
            {
                uiA->printAdminUpdateStaff();
                cin >> choice;
                switch (choice)
                {
                case 1:
                    checkCin();
                    cout << "\nEnter new  Username: "; getline(cin, newUsername);
                    break;
                case 2:
                    checkCin();
                    cout << "\nEnter new Password: "; getline(cin, newPassword);
                    break;
                case 3:
                    checkCin();
                    cout << "\nEnter new full name: "; getline(cin, newName);
                    break;
                case 4:
                    checkCin();
                    cout << "\nEnter new phone number: "; getline(cin, newPhone);
                    break;
                case 5:
                    //Done
                    break;
                default:
                    checkCin();
                    cout << "\nPlease enter the number listed.";
                    break;
                }
            } while (choice != 5);
            dbA->updateUseraccounts(userID,newUsername,newPassword);
            dbA->updateStaff(userID,newName,newPhone);
        }
        else if (role == "Parent")
        {
            do
            {
                uiA->printAdminUpdateParent();
                cin >> choice;
                switch (choice)
                {
                case 1:
                    checkCin();
                    cout << "\nEnter new  Username: "; getline(cin, newUsername);
                    break;
                case 2:
;                   checkCin();
                    cout << "\nEnter new Password: "; getline(cin, newPassword);
                    break;
                case 3:
                    checkCin();
                    cout << "\nEnter new full name: "; getline(cin, newName);
                    break;
                case 4:
                    checkCin();
                    cout << "\nEnter new phone number: "; getline(cin, newPhone);
                    break;
                case 5:
                    //Done
                    break;
                default:
                    break;
                }
            } while (choice != 5);

            dbA->updateUseraccounts(userID,newUsername,newPassword);
            dbA->updateParent(userID,newName,newPhone);
        }
        else if (role == "Student")
        {
            do
            {
                uiA->printAdminUpdateStudent();
                cin >> choice;
                switch (choice)
                {
                case 1:
                    checkCin();
                    cout << "\nEnter new  Username: "; getline(cin, newUsername);
                    break;
                case 2:
                    checkCin();
                    cout << "\nEnter new Password: "; getline(cin, newPassword);
                    break;
                case 3:
                    //
                    break;
                case 4:
                    //
                    break;
                case 5:
                    //
                    break;
                default:
                    break;
                }
            } while (choice != 7);
            
            
            cout << "\nEnter new full name: "; getline(cin, newName);
            cout << "\nEnter new phone number: "; getline(cin, newPhone);
            cout << "\nEnter new date of birth (YYYY-MM-DD): "; getline(cin, newDob);
            cout << "\nEnter new address: "; getline(cin, newAddress);
            //dbA->updateUser(username,role,userID,newName,newPhone,newDob,newAddress,parentid);
        }
        else{
            cout << "\nUser does not have a role.";
        }
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

void sarmsAdmin::manageSubjects(){
    try
    {
        int choice;

        do
        {
            clearScreen();
            uiA->printAdminSubjectManagement();
            cin >> choice;
            switch (choice)
            {
            case 1:
                addSubject();
                break;
            case 2:
                dbA->retrieveSubject();
                break;
            case 3:
                //deleteSubject
                break;
            case 4:
                //updateSubject
                break;
            case 5:
                //set Subject to Teacher
                break;
            case 6:
                //return back
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }

        } while (choice != 6);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}
void sarmsAdmin::addSubject(){
    string name,description;
    checkCin();

    cout << "\nPlease insert the name of the Subject: "; getline(cin,name);
    cout << "\nPlease insert the description of the Subject: "; getline(cin,description);
    dbA->addSubject(name,description);
}

void sarmsAdmin::manageTuition(){}

void sarmsAdmin::manageClass(){
    try
    {
        int choice;
        do
        {
            clearScreen();
            dbA->retrieveClassList();
            cout << "\n Enter the ClassID you want to manage(enter 7 to return back to previous menu): ";
            checkCin();
            cin >> choice;
            
        } while (choice != 7);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}