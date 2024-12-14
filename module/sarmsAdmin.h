#ifndef SARMSADMIN_H
#define SARMSADMIN_H

class sarmsAdmin
{
private:
    sarmsUI* uiA;
    sarmsdb* dbA;
public:
    sarmsAdmin(sarmsdb &db,sarmsUI &ui);
    ~sarmsAdmin();
    void checkCin();
    void clearScreen();

    ///////////////////////////////////////////////////////////////////////
    void manageUser();//done
    void deleteUser();//done

    void manageAdmin();
    void registerAdmin();//done
    void updateAdmin();
    void deleteAdmin();//done

    void manageTeacher();
    void registerTeacher();//done
    void updateTeacher();
    void deleteTeacher();//done

    void manageParent();
    void registerParent();//done
    void updateParent();
    void deleteParent();//done

    void manageStudent();
    void registerStudent();//done
    void updateStudent();
    void deleteStudent();//done
    ///////////////////////////////////////////////////////////////////////
    void manageSubjects();
    void addSubject();
    void deleteSubject();
    void updateSubject();
    ///////////////////////////////////////////////////////////////////////
    void manageTuition();
    void addTuition();
    void deleteTuition();
    void updateTuition();
    void setStudentTuition();

    ///////////////////////////////////////////////////////////////////////
    void manageClass();


};
#endif

void sarmsAdmin::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sarmsAdmin::checkCin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

sarmsAdmin::sarmsAdmin(sarmsdb& db,sarmsUI& ui)
{
    uiA = new sarmsUI(ui);
    dbA = new sarmsdb(db);
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
                manageUser();
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
                //Log Out
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }

        } while (choice != 5);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}

sarmsAdmin::~sarmsAdmin()
{
}

void sarmsAdmin::manageUser()
{
    try
    {
        int choice;

        do
        {
            clearScreen();
            uiA->printAdminUserManagement();
            dbA->retrieveAllUser();
            cin >> choice;
            switch (choice)
            {
            case 1:
                manageAdmin();
                break;
            case 2:
                manageTeacher();
                break;
            case 3:
                manageParent();
                break;
            case 4:
                manageStudent();
                break;
            case 5:
                //return to admin menu()
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }

        } while (choice != 5);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}

void sarmsAdmin::deleteUser(){
    string username1;
    string UserID;
    cout << "\nPlease insert the username of the user you want to delete: ";
        cin >> username1;
        if(dbA->checkUsername(username1)){
            dbA->retrieveUserID(username1,UserID);
            dbA->deleteUser(UserID);
        }
        else{
            cout << "\nUser doesnt exist please try again.";
        }
}

void sarmsAdmin::manageAdmin(){
    try
    {
        string continue1;
        int choice;
        do
        {
            clearScreen();
            uiA->printAdminManagement();
            cin >> choice;

            switch (choice)
            {
            case 1:
                registerAdmin();
                break;
            case 2:
                dbA->retrieveAdmin();
                cout << "\n Type in anything to continue: ";
                cin >> continue1;
                break;
            case 3:
                //update
                break;
            case 4:
                deleteAdmin();
                break;
            case 5:
                //return back
                break;
            default:
                cout << "Please insert the number shown above.\n";
                checkCin();
                break;
            }

        } while (choice != 5);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}

void sarmsAdmin::registerAdmin()
{
    string username, password;
    string name, phoneno;
    string designation;
    checkCin();

    cout << "Username: ";           getline(cin,username);
    while(dbA->checkUsername(username)){
        cout << "\nUsername is already taken please insert a new one: ";
        getline(cin,username);
    }
    cout << "\nPassword : ";       getline(cin,password);
    cout << "\nFull name : "; getline(cin,name);
    cout << "\nPhone number : ";    getline(cin,phoneno);

    cout << "\nDesignation(Admin,Finance,Teacher) : ";     getline(cin,designation); // change to number choice
    while (designation != "Admin" && designation != "Finance" && designation != "Teacher")
    {
        cout << "\nPlease type in the based on the example Admin,Finance,Teacher :";
        getline(cin,designation);
    }
    
    dbA->addUser(username, password, "Admin", name, phoneno, "NULL", "NULL", designation);
}

void sarmsAdmin::deleteAdmin(){  
    dbA->retrieveAdmin();
    deleteUser();
}

void sarmsAdmin::manageTeacher(){
try
    {
        string continue1;
        int choice;
        do
        {
            clearScreen();
            uiA->printTeacherManagement();
            cin >> choice;

            switch (choice)
            {
            case 1:
                registerTeacher();
                break;
            case 2:
                //retrieve
                dbA->retrieveTeacher();
                cout << "\n Type in anything to continue: ";
                cin >> continue1;
                break;
            case 3:
                //update
                break;
            case 4:
                deleteTeacher();
                break;
            case 5:
                //return back
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }

        } while (choice != 5);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}

void sarmsAdmin::registerTeacher(){
    string username, password;
    string name, phoneno;
    string designation;
    int choice;
    checkCin();
    
    cout << "Username: ";           getline(cin,username);
    while(dbA->checkUsername(username)){
        cout << "\nUsername is already taken please insert a new one: ";
        getline(cin,username);
    }
    cout << "\nPassword : ";        getline(cin,password);
    cout << "\nFull name : ";       getline(cin,name);
    cout << "\nPhone number : ";    getline(cin,phoneno);
    dbA->addUser(username, password, "Teacher", name, phoneno, "NULL", "NULL", "Teacher");
}

void sarmsAdmin::deleteTeacher(){
    dbA->retrieveTeacher();
    deleteUser();
}

void sarmsAdmin::manageParent(){
try
    {
        string continue1;
        int choice;
        do
        {
            clearScreen();
            uiA->printParentManagement();
            cin >> choice;

            switch (choice)
            {
            case 1:
                registerParent();
                break;
            case 2:
                //retrieve
                dbA->retrieveParent();
                cout << "\n Type in anything to continue: ";
                cin >> continue1;
                break;
            case 3:
                //update
                break;
            case 4:
                //delete
                break;
            case 5:
                //return back
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }

        } while (choice != 5);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}

void sarmsAdmin::registerParent(){
    string username, password;
    string name, phoneno;
    string designation;
    int choice;
    checkCin();
    
    cout << "Username: ";           getline(cin,username);
    while(dbA->checkUsername(username)){
        cout << "\nUsername is already taken please insert a new one: ";
        getline(cin,username);
    }
    cout << "\nPassword : ";        getline(cin,password);
    cout << "\nFull name : ";       getline(cin,name);
    cout << "\nPhone number : ";    getline(cin,phoneno);
    dbA->addUser(username, password, "Parent", name, phoneno, "NULL", "NULL", "NULL");
}

void sarmsAdmin::deleteParent(){
    dbA->retrieveParent();
    deleteUser();
}

void sarmsAdmin::manageStudent(){
    try
        {
            int choice;
            string continue1;
            do
            {
                clearScreen();
                uiA->printStudentManagement();
                cin >> choice;

                switch (choice)
                {
                case 1:
                    registerStudent();
                    break;
                case 2:
                    //retrieve
                    dbA->retrieveStudent();
                    cout << "\n Type in anything to continue: ";
                    cin >> continue1;
                    break;
                case 3:
                    //update
                    break;
                case 4:
                    deleteStudent();
                    break;
                case 5:
                    //set student's parent
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

void sarmsAdmin::registerStudent(){
    string username, password;
    string name, phoneno,dob,address;
    string designation;
    int choice;
    checkCin();
    
    cout << "Username: ";           getline(cin,username);
    while(dbA->checkUsername(username)){
        cout << "\nUsername is already taken please insert a new one: ";
        getline(cin,username);
    }
    cout << "\nPassword : ";        getline(cin,password);
    cout << "\nFull name : ";       getline(cin,name);
    cout << "\nPhone number : ";    getline(cin,phoneno);
    cout << "\nDate of Birth (yyyy-mm-dd) : ";    getline(cin,dob);
    cout << "\nAddress : ";     getline(cin,address);
    dbA->addUser(username, password, "Student", name, phoneno, dob, address,"NULL");
}

void sarmsAdmin::deleteStudent(){
    dbA->retrieveStudent();
    deleteUser();
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

void sarmsAdmin::manageClass(){}