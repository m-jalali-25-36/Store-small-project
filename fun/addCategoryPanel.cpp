#include <iostream>
#include "../class/UnitWorkDb.cpp"

#pragma once
using namespace std;

void addCategoryPanel(UnitWorkDb *db)
{
    system("cls");
    Category category;
    string inp;
    cout << "Name> ";
    getline(cin, inp);
    category.setName(inp);
    cout << "Description> ";
    getline(cin, inp);
    category.setDescription(inp);
    if (db->getCategoryDb()->Insert(&category))
        cout << "Category successfully add." << endl;
    else
        cout << "Category add failed!!!" << endl;
}