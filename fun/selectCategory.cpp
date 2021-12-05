#include <iostream>
#include "../tools/show.cpp"
#include "../class/UnitWorkDb.cpp"

#pragma once
using namespace std;

int selectCategory(UnitWorkDb *db, int *id, string *name)
{
    QList<Category> category = db->getCategoryDb()->GetAll();
    system("cls");
    cout << "Select a category to change.";
    headerShowCategory();
    showCategory(&category);
    cout << "Enter an index: ";
    string inp;
    getline(cin, inp);
    int index = toInt(inp);
    if (index > 0 && index <= category.size())
    {
        *name = category[index - 1].getName();
        *id = category[index - 1].getId();
        return category[index - 1].getId();
    }
    *name = "";
    *id = -1;
    return -1;
}