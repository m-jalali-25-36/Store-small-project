#include <iostream>
#include "../class/UnitWorkDb.cpp"

#pragma once
using namespace std;

int loginPanel(UnitWorkDb *db)
{
    while (true)
    {
        system("cls");
        string username, pass;
        cout << "Enter username: " << endl;
        getline(cin, username);
        cout << "Enter pass: " << endl;
        getline(cin, pass);
        User user = db->getUserDb()->GetByUsername(username);
        if (user.getId() != -1 && user.getPassword() == pass)
            return user.getId();
        else
        {
            cout << "Password and username not found.\nWant to try again(y/n)? ";
            string com;
            getline(cin, com);
            if (com == "y" || com == "Y" || com == "yes")
                continue;
            else
                return -1;
        }
    }
}