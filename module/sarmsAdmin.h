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

    void Registration();
    void registerAdmin();
    void registerTeacher();
    void registerParent();
    void registerStudent();
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
                Registration();
                break;
            case 2:
                //placeholder
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }

        } while (choice != 2);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}

sarmsAdmin::~sarmsAdmin()
{
}

void sarmsAdmin::Registration()
{
    try
    {
        int choice;

        do
        {
            clearScreen();
            uiA->printAdminRegistration();
            dbA->retrieveAllUser();
            cin >> choice;
            switch (choice)
            {
            case 1:
                registerAdmin();
                break;
            case 2:
                // placeholder
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }

        } while (choice != 2);
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

    cout << "\nDesignation(Admin,Finance,Teacher) : ";     getline(cin,designation);
    while (designation != "Admin" || designation != "Finance" || designation != "Teacher")
    {
        cout << "\nPlease type in the based on the example Admin,Finance,Teacher :";
        getline(cin,designation);
    }
    
    dbA->addUser(username, password, "Admin", name, phoneno, "NULL", "NULL", designation);
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
    cout << "\nDesignation : ";     getline(cin,designation);
    dbA->addUser(username, password, "Parent", name, phoneno, "NULL", "NULL", designation);
}
void sarmsAdmin::registerStudent(){
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
    cout << "\nDesignation : ";     getline(cin,designation);
    dbA->addUser(username, password, "Student", name, phoneno, "NULL", "NULL", designation);
}