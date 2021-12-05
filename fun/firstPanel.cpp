#include <iostream>
#include "employeePanel.cpp"
#include "customerPanel.cpp"
#include "loginPanel.cpp"
#include "helpPanel.cpp"
#include "../class/UnitWorkDb.cpp"

#pragma once
using namespace std;

void firstPanel(UnitWorkDb *db)
{
    while (true)
    {
        system("cls");
        cout << "--------------------------------------------" << endl;
        cout << "|             Please select one.           |" << endl;
        cout << "|   1) Customer                            |" << endl;
        cout << "|   2) Employee                            |" << endl;
        cout << "|   3) Help                                |" << endl;
        cout << "|   0) Exit                                |" << endl;
        cout << "|                                          |" << endl;
        cout << "--------------------------------------------" << endl;
        string com;
        getline(cin, com);
        if (com == "1")
            customerPanel(db);
        else if (com == "2")
        {
            int userId = loginPanel(db);
            if (userId != -1)
                employeePanel(db, userId);
        }
        else if (com == "3")
            helpPanel();
        else if (com == "0")
            return;
        else
            continue;
    }
}