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

    void printAdminSubjectManagement();
    void printAdminTuitionManagement();
    void printAdminClassManagement();
    void printAdminManageClass();
    void printAdminManageClassSchedule();

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
    printCenteredText("2.Subject Management");
    printCenteredText("3.Tuition Management");
    printCenteredText("4.Class Management");
    printCenteredText("5.Log Out");
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
    printCenteredText("5.Return To Main Screen.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Register Admin.");
    printCenteredText("2.List Admin.");
    printCenteredText("3.Update Admin.");
    printCenteredText("4.Delete Admin.");
    printCenteredText("5.Return To Main Screen.");
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
    printCenteredText("5.Return To Main Screen.");
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
    printCenteredText("5.Return To Main Screen.");
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
    printCenteredText("5.Set Student's Parent.");
    printCenteredText("6.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminSubjectManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Add Subject.");
    printCenteredText("2.Retrieve All Subjects.");
    printCenteredText("3.Update Subject.");
    printCenteredText("4.Delete Subject.");
    printCenteredText("5.Set Teacher to Subject.");
    printCenteredText("6.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminTuitionManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Add Tuition.");
    printCenteredText("2.Retrieve All Tuitions.");
    printCenteredText("3.Update Tuition.");
    printCenteredText("4.Delete Tuition.");
    printCenteredText("5.Set Tuition to Student.");
    printCenteredText("6.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminClassManagement(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Manage Class.");
    printCenteredText("2.Manage Class Schedule.");
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminManageClass(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Add Class.");
    printCenteredText("2.Retrieve All Class.");
    printCenteredText("3.Update Class.");
    printCenteredText("4.Delete Class.");
    printCenteredText("5.Set Student to Class.");
    printCenteredText("6.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminManageClassSchedule(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Add Schedule.");
    printCenteredText("2.Retrieve All Schedule.");
    printCenteredText("3.Update Schedule.");
    printCenteredText("4.Delete Schedule.");
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}