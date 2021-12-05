#include <iostream>
#include "../class/UnitWorkDb.cpp"
#include "./selectCategory.cpp"
#include "./printProduct.cpp"

#pragma once
using namespace std;

void addProductPanel(UnitWorkDb *db)
{
    system("cls");
    Product newProduct;
    string inp;
    cout << "Name> ";
    getline(cin, inp);
    if (inp != "")
        newProduct.setName(inp);
    int idCategory;
    selectCategory(db, &idCategory, &inp);
    system("cls");
    cout << "Name> " << newProduct.getName() << endl;
    cout << "Category> " << inp << endl;
    newProduct.setCategoryId(idCategory);
    cout << "Price> ";
    getline(cin, inp);
    newProduct.setPrice(toInt(inp));
    cout << "Quantity> ";
    getline(cin, inp);
    newProduct.setQuantity(toInt(inp));
    cout << "Description> ";
    getline(cin, inp);
    newProduct.setDescription(inp);
    if (db->getProductDb()->Insert(&newProduct))
        cout << "Product successfully add." << endl;
    else
        cout << "Product add failed!!!" << endl;
}