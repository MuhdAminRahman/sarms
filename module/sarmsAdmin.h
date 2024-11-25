#ifndef SARMSADMIN_H
#define SARMSADMIN_H

class sarmsAdmin
{
private:
    sarmsUI ui;
    sarmsdb db;
public:
    sarmsAdmin(/* args */);
    ~sarmsAdmin();
    void checkCin();
    void clearScreen();
    void Registration();
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
    cout << "\nPlease follow the instruction for input.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

sarmsAdmin::sarmsAdmin(/* args */){
    try
    {
        int choice;
        do
        {
            clearScreen();
            ui.printAdminPage();
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
            
        } while (choice !=2 );
        
    }
    catch(const exception e)
    {
        cerr << e.what() << '\n';
    }
}

sarmsAdmin::~sarmsAdmin(){
}

void sarmsAdmin::Registration(){
    try
    {
        int choice;
        string username,password,role;;
        string name,phoneno,dob,address;
        string designation;
        do
        {
            clearScreen();
            ui.printAdminRegistration();
            cin >> choice;
            switch(choice)
            {
            case 1:
                cout << "New Admin Username: ";
                cin >> username;
                cout << "\n Password : ";
                cin >> password;
                cout << "\nRole(Admin/Teacher/Parent/Student): ";
                cin >> role;
                cout << "\nAdmin name : ";
                cin >> name;
                cout << "\nPhone number : ";
                cin >> phoneno;
                cout << "\nDesignation : ";
                cin >> designation;
                db.addUser(username,password,role,name,phoneno,dob,address,designation);
                break;
            case 2:
                //placeholder
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }
            
        } while (choice !=2 );
        
    }
    catch(const exception e)
    {
        cerr << e.what() << '\n';
    }
    
}