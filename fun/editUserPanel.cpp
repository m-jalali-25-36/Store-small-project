#include <iostream>
#include "../class/UnitWorkDb.cpp"

#pragma once
using namespace std;

void editUserPanel(UnitWorkDb *db, int editId, Access access)
{
    User user = db->getUserDb()->GetById(editId);
    system("cls");
    string acc = user.getAccess() == Admin ? "Admin" : "Employee";
    cout << "UserName: " << user.getUserName() << endl;
    cout << "Password: " << user.getPassword() << endl;
    cout << "Email: " << user.getEmail() << endl;
    cout << "Access: " << acc << endl;
    cout << "-------------------------------------" << endl;
    string inp;
    cout << "UserName> ";
    getline(cin, inp);
    if (inp != "")
        user.setUserName(inp);
    cout << "Password> ";
    getline(cin, inp);
    if (inp != "")
        user.setPassword(inp);
    cout << "Email> ";
    getline(cin, inp);
    if (inp != "")
        user.setEmail(inp);
    if (access == Admin)
    {
        cout << "Access(1:Admin|2:Employee)> ";
        getline(cin, inp);
        if (inp != "")
            user.setAccess(static_cast<Access>(toInt(inp)));
    }
    if (db->getUserDb()->Update(&user))
        cout << "User successfully edit." << endl;
    else
        cout << "User edit failed!!!" << endl;
}
