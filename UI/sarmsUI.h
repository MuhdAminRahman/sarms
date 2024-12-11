#ifndef SARMSUI_H
#define SARMSUI_H

class sarmsUI
{
private:
    private:
    const int width = 200;
    const char cornerChar = '+';
    const char edgeChar = '=';
    const char borderChar = '|';

public:
    sarmsUI();
    ~sarmsUI();
    void printBorder();
    void printEmptyLine();
    void printCenteredText(const string &text);

    void printFrontPage();
    void printLoginPage();

    void printAdminPage();
    void printAdminUserManagement();
    void printAdminManagement();
    void printTeacherManagement();
    void printParentManagement();
    void printStudentManagement();

    void printAdminSubject();
    void printAdminClassSchedule();
    void printAdminTuition();

    void printTeacherPage();
    void printTeacherAssessment();
    void printTeacherClass();

    void printParentPage();
    void printParentAssessmen();
    void printParentClass();
    void printParentTuition();

    void printStudentPage();
    void printStudentAssessment();
    void printStudentClass();
    
};
#endif

sarmsUI::sarmsUI(){}

sarmsUI::~sarmsUI(){}

void sarmsUI::printBorder(){
    cout  << cornerChar << setfill(edgeChar) << setw(width - 1) << edgeChar << cornerChar << endl;
}
void sarmsUI::printEmptyLine(){
    cout << borderChar << setfill(' ') << setw(width - 1) << ' ' << borderChar << endl;
}
void sarmsUI::printCenteredText(const string &text){
    int padding = (width - text.length() - 2) / 2; // Subtract 2 for border characters
    cout << borderChar << setw(padding + 1) << ' ' << text << setw(padding + 1) << ' ' << borderChar << endl;
}

void sarmsUI::printFrontPage(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Login");
    printCenteredText("2.Exit");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminPage(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.User Management");
    printCenteredText("2.Log Out");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminUserManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Admin Management.");
    printCenteredText("2.Teacher Management.");
    printCenteredText("3.Parent Management.");
    printCenteredText("4.Student Management.");
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Admin Registration.");
    printCenteredText("2.Admin Retrieve.");
    printCenteredText("3.Admin Update.");
    printCenteredText("4.Admin Delete.");
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printTeacherManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Teacher Registration.");
    printCenteredText("2.Teacher Retrieve.");
    printCenteredText("3.Teacher Update.");
    printCenteredText("4.Teacher Delete.");
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printParentManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Parent Registration.");
    printCenteredText("2.Parent Retrieve.");
    printCenteredText("3.Parent Update.");
    printCenteredText("4.Parent Delete.");
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printStudentManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Student Registration.");
    printCenteredText("2.Student Retrieve.");
    printCenteredText("3.Student Update.");
    printCenteredText("4.Student Delete.");
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}
