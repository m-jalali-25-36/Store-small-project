#include <iostream>
#include "../class/UnitWorkDb.cpp"

#pragma once
using namespace std;

void addUserPanel(UnitWorkDb *db)
{
    system("cls");
    string inp;
    User user;
    cout << "UserName> ";
    getline(cin, inp);
    user.setUserName(inp);
    cout << "Password> ";
    getline(cin, inp);
    user.setPassword(inp);
    cout << "Email> ";
    getline(cin, inp);
    user.setEmail(inp);
    cout << "Access(1:Admin|2:Employee)> ";
    getline(cin, inp);
    if (toInt(inp) == 1)
        user.setAccess(Admin);
    else
        user.setAccess(Employee);
    if (db->getUserDb()->Insert(&user))
        cout << "User successfully add." << endl;
    else
        cout << "User add failed!!!" << endl;
}