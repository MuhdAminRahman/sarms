#include <iomanip>
#include <string>
#include <mysql.h>
#include <limits>
#include <conio.h>
using namespace std;
#include "sarmsUI.h"
#include "sarmsDB.h"
#include "sarmsUser.h"
#include "sarmsAdmin.h"

class sarms
{
private:
    string username;
    string password;
    string role;
    sarmsUI ui;
    sarmsdb db;
    bool loginFlag = 0;
    // sarms Admin
    // sarms Parent
    // Sarms Student
    // sarms teacher
    // sarms Login
public:
    sarms();
    ~sarms();
    void clearScreen(); // clears the screen
    void checkCin();    // check for misinput
    void frontPage();   // front page loop
    void Login();
    void getPassword();
};

void sarms::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sarms::checkCin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

sarms::sarms()
{

    do
    {
        clearScreen();
        frontPage();
        db.connectdb();
        loginFlag = db.verifyLogin(username, password, role);
        if (loginFlag)
        {
            if (role == "Admin")
            {
                sarmsAdmin admin(db,ui);
                
            }
            if (role == "Teacher")
            {
                // sarmsTeacher teacher;
            }
            if (role == "Parent")
            {
                // sarmsParent parent;
            }
            if (role == "Student")
            {
                // sarmsStudent student;
            }
            db.closedb();
        }
        else
        {
            cout << "\nUser does not exist, please try logging again or contact your admin.";

        }
        
    } while (true);
}

sarms::~sarms()
{
}

void sarms::frontPage()
{
    try
    {
        int choice;
        do
        {
            clearScreen();
            ui.printFrontPage();
            cin >> choice;

            switch (choice)
            {
            case 1:
                Login();
                break;
            case 2:
                exit(0);
                break;
            default:
                cout << "Please insert the number shown above.\n";
                checkCin();
                break;
            }
        } while (choice < 1 || choice > 2);
    }
    catch (const exception e)
    {
        cerr << e.what() << '\n';
    }
}

void sarms::Login(){
    cout << "Enter Username : ";
    checkCin();
    getline(cin,username);

    cout << "\nEnter password : ";
    getPassword();
}

void sarms::getPassword(){
    char ch;
    password = "";
    while ((ch = _getch()) != '\r') { // '\r' is Enter
        password.push_back(ch);
        cout << '*'; // Mask the input
    }
}