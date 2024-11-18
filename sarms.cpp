#include <iostream>
#include <string>
#include <iomanip>
#include <mysql.h> // Make sure you have the MySQL library installed
#include <conio.h>

using namespace std;

// Global variables
int qstate;
MYSQL *conn;
MYSQL_ROW row;
MYSQL_RES *res;

string UserID, CarID;

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
            cout << "Database Connected" << endl;
        else
            cout << "Failed To Connect!" << endl;
        if (conn)
            cout << "Database Connected To MySql" << endl;
        else
            cout << "Failed To Connect!" << endl;
    }
};

int main()
{
    system("title My Project");
    db_response::ConnectionFunction();

    string selectq = "SELECT * FROM country";
    const char *squery = selectq.c_str();

    mysql_query(conn, squery);
    cout << setw(11) << "1" << setw(17) << "2" << setw(20) << "3" << setw(20) << "4" << setw(25) << "5" << endl;

    res = mysql_store_result(conn);
    int field_nums = mysql_num_fields(res);
    cout << endl;
    cout << field_nums;
    cout << endl;
    while (row = mysql_fetch_row(res))
    {
        for (int i = 0; i < field_nums; i++)
        {
            cout << setw(2) << row[i];
        }
        cout << endl;
    }
    system("PAUSE");
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
