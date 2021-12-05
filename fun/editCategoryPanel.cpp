#include <iostream>
#include "../class/UnitWorkDb.cpp"
#include "../tools/show.cpp"

#pragma once
using namespace std;

void editCategoryPanel(UnitWorkDb *db, int editId)
{
    Category category = db->getCategoryDb()->GetById(editId);
    system("cls");
    cout << "Name: " << category.getName() << endl;
    cout << "Description: " << category.getDescription() << endl;
    cout << "-------------------------------------" << endl;
    string inp;
    cout << "Name> ";
    getline(cin, inp);
    if (inp != "")
        category.setName(inp);
    cout << "Description> ";
    getline(cin, inp);
    if (inp != "")
        category.setDescription(inp);
    if (db->getCategoryDb()->Update(&category))
        cout << "Category successfully edit." << endl;
    else
        cout << "Category edit failed!!!" << endl;
}
