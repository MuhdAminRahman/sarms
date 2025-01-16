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


    /////////////////////////////////////////////////////////////////
    //Admin
    void printAdminPage();
    void printAdminUserManagement();

    void printAdminCreateUser();
    void printAdminChooseRole();

    void printAdminSearchUser();

    void printAdminUpdateStaff();
    void printAdminUpdateParent();
    void printAdminUpdateStudent();

    void printAdminDeleteUser();


    void printAdminSubjectManagement();
    void printAdminTuitionManagement();
    void printAdminClassManagement();
    void printAdminManageClass();
    void printAdminUpdateClass();
    void printAdminManageClassSchedule();
    void printstartTimeSelection();

    /////////////////////////////////////////////////////////////////
    //Staff
    void printStaffPage();
    void printStaffChooseRole();

    /////////////////////////////////////////////////////////////////
    //Teacher
    void printTeacherPage();
    void printTeacherAssessment();
    void printTeacherClass();

    /////////////////////////////////////////////////////////////////
    //Parent
    void printParentPage();
    void printParentAssessmen();
    void printParentClass();
    void printParentTuition();

    /////////////////////////////////////////////////////////////////
    //Student
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
    cout  << cornerChar << setfill(edgeChar) << setw(width - 30) << edgeChar << cornerChar << endl;
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

void sarmsUI::printProgramName(){

}
void sarmsUI::printMenuName(){

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Admin
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
    printCenteredText("1.Create User.");
    printCenteredText("2.Search User.");
    printCenteredText("3.Update User.");
    printCenteredText("4.Delete User.");
    printCenteredText("5.Return To Main Screen.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminCreateUser(){

}
void sarmsUI::printAdminChooseRole(){
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printCenteredText("Please type in the number of the Role you want to choose: ");
    printCenteredText("1.Admin");
    printCenteredText("2.Staff");
    printCenteredText("3.Teacher");
    printCenteredText("4.Parent");
    printCenteredText("5.Student");
    printEmptyLine();
    printBorder();
}
void sarmsUI::printAdminSearchUser(){
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printCenteredText("Please type in the number of the Role you want to choose: ");
    printCenteredText("1.Search by Role");
    printCenteredText("2.Search by Username");
    printCenteredText("3.Search by Name");
    printCenteredText("4.Return to Main Menu");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminUpdateStaff(){
    printBorder();
    printEmptyLine();
    printCenteredText("Please type in the number of the data you want to update: ");
    printCenteredText("1.Update Password");
    printCenteredText("2.Update Name");
    printCenteredText("3.Update Phone Number");
    printCenteredText("4.Done");
    printEmptyLine();
    printBorder();
}
void sarmsUI::printAdminUpdateParent(){
    printBorder();
    printEmptyLine();
    printCenteredText("Please type in the number of the data you want to update: ");
    printCenteredText("1.Update Password");
    printCenteredText("2.Update Name");
    printCenteredText("3.Update Phone Number");
    printCenteredText("4.Done");
    printEmptyLine();
    printBorder();
}
void sarmsUI::printAdminUpdateStudent(){
    printBorder();
    printEmptyLine();
    printCenteredText("Please type in the number of the data you want to update: ");
    printCenteredText("1.Update Password");
    printCenteredText("2.Update Name");
    printCenteredText("3.Update Phone Number");
    printCenteredText("4.Update Date of Birth");
    printCenteredText("5.Update Address");
    printCenteredText("6.Done");
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
    printCenteredText("4.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminTuitionManagement(){
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printCenteredText("1.Retrieve All Tuitions.");
    printCenteredText("2.Update Student Tuition.");
    printCenteredText("3.Return Back.");
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
    printCenteredText("3.Return Back.");
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
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminUpdateClass(){
    printBorder();
    printEmptyLine();
    printCenteredText("Please type in the number of the data you want to update: ");
    printCenteredText("1.Update Name");
    printCenteredText("2.Update Staff");
    printCenteredText("3.Done");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printAdminManageClassSchedule(){
    printBorder();
    printEmptyLine();
    printCenteredText("1.Add Subject to Schedule.");
    printCenteredText("2.Retrieve All Schedule.");
    printCenteredText("3.Update Schedule.");
    printCenteredText("4.Delete Schedule.");
    printCenteredText("5.Return Back.");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printstartTimeSelection(){
    printBorder();
    printEmptyLine();
    printCenteredText("Please type in the number of the time you want to set: ");
    printCenteredText("1. 8:00");
    printCenteredText("2. 9:00");
    printCenteredText("3. 10:30");
    printCenteredText("4. 11:30");
    printCenteredText("5. 14:00");
    printCenteredText("6. 15:00");
    printEmptyLine();
    printBorder();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Staff
void sarmsUI::printStaffPage(){
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printUser();
    printCenteredText("1. Manage Users");
    printCenteredText("2. Manage Tuition");
    printCenteredText("3. Manage Assessment");
    printCenteredText("4. Manage Class");
    printCenteredText("5. Log Out");
    printCenteredText("Please insert the number shown above to navigate to it.");
    printEmptyLine();
    printBorder();
}

void sarmsUI::printStaffChooseRole(){
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printCenteredText("Please type in the number of the Role you want to choose: ");
    printCenteredText("1.Teacher");
    printCenteredText("2.Parent");
    printCenteredText("3.Student");
    printCenteredText("4.Return to Main Menu");
    printEmptyLine();
    printBorder();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Teacher
void sarmsUI::printTeacherPage() {
    printEmptyLineNoBorder();
    printBorder();
    printEmptyLine();
    printUser();
    printCenteredText("1. Retrieve Assessments");
    printCenteredText("2. Update Assessment");
    printCenteredText("3. Manage Classes");
    printCenteredText("4. Log Out");
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Parent
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Student
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
