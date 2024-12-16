#ifndef SARMSUI_H
#define SARMSUI_H

class sarmsUI
{
private:
    const int width = 230;
    const char cornerChar = '+';
    const char edgeChar = '=';
    const char borderChar = '|';
    string username;
    string userrole;

public:
    sarmsUI();
    ~sarmsUI();
    void setUsernameAndRole(const string &user,const string &role);
    void printBorder();
    void printEmptyLine();
    void printEmptyLineNoBorder();
    void printCenteredText(const string &text);
    void printUser();

    void printProgramName();
    void printMenuName();

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

void sarmsUI::setUsernameAndRole(const string &user,const string &role){
    username = user; userrole = role;
}

void sarmsUI::printBorder(){
    cout  << cornerChar << setfill(edgeChar) << setw(width - 1) << edgeChar << cornerChar << endl;
}
void sarmsUI::printEmptyLine(){
    cout  << setfill(' ') << setw(width - 1) << ' '  << endl;
}
void sarmsUI::printEmptyLineNoBorder(){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
void sarmsUI::printCenteredText(const string &text){
    int padding = (width - text.length()) / 2;
    cout  << setw(padding + 1) << ' ' << text << setw(padding + 1) << ' '  << endl;
}
void sarmsUI::printUser(){
    int padding = (width - (username.length() + userrole.length())) / 2;
    cout << setw(padding + 1) << "User: " <<  username << "\t" << "Role: " << userrole << endl;
}

void sarmsUI::printFrontPage(){
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printCenteredText("1.Login");
    printCenteredText("2.Exit");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminPage(){
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printUser();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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
    printEmptyLineNoBorder();
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

void sarmsUI::printTeacherPage() {
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printUser();
    printCenteredText("1. Create Assessment");
    printCenteredText("2. Retrieve Assessments");
    printCenteredText("3. Update Assessment");
    printCenteredText("4. Delete Assessment");
    printCenteredText("5. Manage Classes");
    printCenteredText("6. Log Out");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printTeacherClass() {
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printUser();
    printCenteredText("1. View Class Schedule");
    printCenteredText("2. Update Class Schedule");
    printCenteredText("3. View Class List");
    printCenteredText("4. Return to Previous Menu");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}


void sarmsUI::printParentPage() {
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printUser();
    printCenteredText("1. View Tuition Details");
    printCenteredText("2. View Payment History");
    printCenteredText("3. View Child's Class Schedule");
    printCenteredText("4. View Child's Performance");
    printCenteredText("5. Log Out");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printStudentPage() {
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printUser();
    printCenteredText("1. View Grades");
    printCenteredText("2. View Class Schedule");
    printCenteredText("3. Log Out");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}
