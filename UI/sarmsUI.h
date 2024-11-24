#ifndef SARMSUI_H
#define SARMSUI_H

class sarmsUI
{
private:
    private:
    const int width = 70;
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
    void printAdminRegistration();
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
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminPage(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Registration");
    printCenteredText("2.Log Out");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminRegistration(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Register Admin.");
    printCenteredText("2.Register Teacher.");
    printCenteredText("3.Register Parent.");
    printCenteredText("4.Register Student.");
    printEmptyLine();
    printBorder();
}
