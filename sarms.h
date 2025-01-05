#ifndef SARMS_H
#define SARMS_H
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include <memory>
#include <mysql.h>


#ifdef _WIN32
#include <conio.h>  // Windows-specific
#else
#include <termios.h>
#include <unistd.h>  // Unix-specific
#endif

using namespace std;
#include "sarmsUI.h"
#include "sarmsTable.h"
#include "sarmsDB.h"
#include "sarmsAdmin.h"
#include "sarmsStaff.h"
#include "sarmsTeacher.h"
#include "sarmsParent.h"
#include "sarmsStudent.h"
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
#endif

sarms::sarms()
{
    try
    {
        do
        {
            frontPage();
            clearScreen();
            db.connectdb();
            loginFlag = db.verifyLogin(username, password, role);
            if (loginFlag)
            {
                ui.setUsernameAndRole(username, role);
                if (role == "Admin")
                {
                    sarmsAdmin admin(db, ui);
                    admin.MainMenu();
                    clearScreen();
                    loginFlag=0;
                }
                else if (role == "Staff")
                {
                    sarmsStaff staff(db, ui);
                    staff.manageStaffTasks();
                    clearScreen();
                    loginFlag=0;
                }
                else if (role == "Teacher")
                {
                    sarmsTeacher teacher(db, ui);
                    teacher.manageTeacherTasks();
                    clearScreen();
                    loginFlag=0;
                }
                else if (role == "Parent")
                {
                    sarmsParent parent(db, ui);
                    parent.manageParentTasks();
                    clearScreen();
                    loginFlag=0;
                }
                else if (role == "Student")
                {
                    sarmsStudent student(db, ui);
                    student.manageStudentTasks();
                    clearScreen();
                    loginFlag=0;
                }
                
            }
            else
            {
                cout << "\nUser does not exist, please try logging again or contact your admin.";
                clearScreen();
            }
        } while (true);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}

sarms::~sarms() {
}

void sarms::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sarms::checkCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void sarms::frontPage() {
    try
    {
        int choice;
        do
        {
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
                clearScreen();
                break;
            }
        } while (choice < 1 || choice > 2);
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }
}

void sarms::Login() {
    clearScreen();
    ui.printEmptyLineNoBorder();
    ui.printBorder();
    ui.printEmptyLine();
    ui.printCenteredText("Enter Username: ");
    ui.printEmptyLine();
    ui.printBorder();
    checkCin();
    getline(cin, username);

    clearScreen();
    ui.printEmptyLineNoBorder();
    ui.printBorder();
    ui.printEmptyLine();
    ui.printCenteredText("Enter Password: ");
    ui.printEmptyLine();
    ui.printBorder();
    getPassword();
}

void sarms::getPassword() {
    char ch;
#ifdef _WIN32
    password = "";
    while ((ch = getch()) != '\r') { // '\r' is Enter
        password.push_back(ch);
        cout << '*'; // Mask the input
    }
#else

    struct termios oldt, newt;
    
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);  
    newt = oldt;
    newt.c_lflag &= ~(ECHO);  // Disable echoing of characters
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply new settings
    
    password = "";
    cout << "Enter your password: ";
    
    while (true) {
        ch = getchar();  // Unix: getchar() hides the input
        if (ch == '\n' || ch == '\r') {  // Enter key
            break;
        } else if (ch == 127) {  // Backspace
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b";  // Erase character from console
            }
        } else {
            password += ch;
            cout << '*';  // Mask input with asterisks
        }
    }
    cout << endl;
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore original terminal settings
#endif
}
