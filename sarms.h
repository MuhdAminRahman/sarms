#include <iomanip>
#include <string>
#include <mysql.h>
#include <limits>
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
    sarmsUser user;
    // sarms Admin
    //sarms Parent
    //Sarms Student 
    //sarms teacher
    //sarms Login
public:
    sarms();
    ~sarms();
    void clearScreen();//clears the screen
    void checkCin();//check for misinput
    void frontPage();//front page loop
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
    cout << "\nPlease follow the instruction for input.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


sarms::sarms(){

    do
    {
        clearScreen();
        frontPage();
        if(user.isUser(username,password,role)){
            cout << role;
            if(role == "Admin"){
                sarmsAdmin admin;
            }
            if(role == "Teacher"){
                //sarmsTeacher teacher;
            }
            if(role == "Parent"){
                //sarmsParent parent;
            }
            if(role=="Student"){
                //sarmsStudent student;
            }

        
        }
    } while (true);
    
    
}

sarms::~sarms()
{
}

void sarms::frontPage(){
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
                cout << "Username: ";
                cin >> username;
                cout << "\nPassword : ";
                cin >> password;cout << endl;
                break;
            case 2:
                exit(0);
                break;
            default:
                cout << "Please insert the number shown above.\n";
                break;
            }
        } while (choice < 1 && choice > 2 );
        
    }
    catch(const exception e)
    {
        cerr << e.what() << '\n';
    }
}