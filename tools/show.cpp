#include <iostream>
#include <iomanip>
#include <QtCore/QList>
#include "../class/product.cpp"
#include "../class/category.cpp"
#include "../class/cart.cpp"

#pragma once
using namespace std;

void showProduct(QList<Product> *products)
{
    for (int i = 0; i < products->size(); i++)
    {
        auto p = products->at(i);
        cout << setfill(' ') << setw(2) << (i + 1) << ")    ";
        cout << std::left;
        cout << setw(35) << p.getName();
        cout << setw(25) << p.getCategoryName();
        cout << setw(15) << p.getPrice();
        cout << setw(15) << p.getQuantity();
        cout << setw(15) << p.getDescription() << "\n";
    }
}
void headerShowProducts()
{
    cout << "index  ";
    cout << std::left << setfill(' ');
    cout << setw(35) << "Name ";
    cout << setw(25) << "Category ";
    cout << setw(15) << "Price ";
    cout << setw(15) << "Quantity ";
    cout << setw(15) << "Description";
    cout << setw(0) << endl;
}

void showCategory(QList<Category> *category)
{
    for (int i = 0; i < category->size(); i++)
    {
        auto c = category->at(i);
        cout << setfill(' ') << setw(2) << (i + 1) << ")    ";
        cout << std::left;
        cout << setw(35) << c.getName();
        cout << setw(35) << c.getDescription() << "\n";
    }
}
void headerShowCategory()
{
    cout << "index  ";
    cout << std::left << setfill(' ');
    cout << setw(35) << "Name ";
    cout << setw(35) << "Description";
    cout << setw(0) << endl;
}

void showUser(QList<User> *user)
{
    for (int i = 0; i < user->size(); i++)
    {
        auto c = user->at(i);
        string access = c.getAccess() == Admin ? "Admin" : "Employee";
        cout << setfill(' ') << setw(2) << (i + 1) << ")    ";
        cout << std::left;
        cout << setw(35) << c.getUserName();
        cout << setw(20) << c.getPassword();
        cout << setw(35) << c.getEmail();
        cout << setw(10) << access << "\n";
    }
}
void headerShowUser()
{
    cout << "index  ";
    cout << std::left << setfill(' ');
    cout << setw(35) << "UserName ";
    cout << setw(20) << "Password ";
    cout << setw(35) << "Email ";
    cout << setw(10) << "Access ";
    cout << setw(0) << endl;
}

void showCart(QList<Cart> *cart)
{
    for (int i = 0; i < cart->size(); i++)
    {
        auto c = cart->at(i);
        cout << setfill(' ') << setw(2) << (i + 1) << ")    ";
        cout << std::left;
        cout << setw(35) << c.getName();
        cout << setw(15) << c.getUnitPrice();
        cout << setw(15) << c.getQuantity();
        cout << setw(15) << c.getAmount() << "\n";
    }
}
void headerShowCart()
{
    cout << "index  ";
    cout << std::left << setfill(' ');
    cout << setw(35) << "Name ";
    cout << setw(15) << "UnitPrice ";
    cout << setw(15) << "Quantity ";
    cout << setw(15) << "Amount ";
    cout << setw(0) << endl;
}