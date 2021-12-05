#include <iostream>
#include <conio.h>
#include "../class/UnitWorkDb.cpp"
#include "../fun/addProductPanel.cpp"
#include "../fun/editProductPanel.cpp"
#include "../fun/addCategoryPanel.cpp"
#include "../fun/editCategoryPanel.cpp"
#include "../fun/editUserPanel.cpp"
#include "../fun/addUserPanel.cpp"
#include "../library/isCharacter.cpp"
#include "../tools/combine.cpp"
#include "../tools/show.cpp"
#include "../tools/search.cpp"

#pragma once
using namespace std;

void employeePanel(UnitWorkDb *db, int userId)
{
    QList<Cart> cart;
    User user = db->getUserDb()->GetById(userId);
    while (true)
    {
        system("cls");
        cout << "--------------------------------------------" << endl;
        cout << "|             Please select one.           |" << endl;
        cout << "|   Cart: " << setw(2) << cart.size() << "                               |" << endl;
        cout << "|   1) See all product                     |" << endl;
        cout << "|   2) View by group                       |" << endl;
        cout << "|   3) Search product                      |" << endl;
        cout << "|   4) Add product                         |" << endl;
        cout << "|   5) See all category                    |" << endl;
        cout << "|   6) Search category                     |" << endl;
        cout << "|   7) Add category                        |" << endl;
        if (user.getAccess() == Admin)
        {
            cout << "|   8) View users                          |" << endl;
            cout << "|   9) Add user                            |" << endl;
        }
        cout << "|  10) Edit profile                        |" << endl;
        cout << "|   0) Back & Logout                       |" << endl;
        cout << "|  00) Exit                                |" << endl;
        cout << "|                                          |" << endl;
        cout << "--------------------------------------------" << endl;
        string com;
        getline(cin, com);
        // See all product
        if (com == "1")
        {
            system("cls");
            QList<Product> products = db->getProductDb()->GetAll();
            QList<Category> category = db->getCategoryDb()->GetAll();
            products = combine(&products, &category);
            headerShowProducts();
            showProduct(&products);
            cout << "Enter an index to select(You back with 0): ";
            string inp;
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            if (index > 0 && index <= products.size())
            {
                cout << "0 => Back \n1 => Edit \n2 => Remove \ncommand>";
                getline(cin, inp);
                if (inp == "1")
                {
                    editProductPanel(db, products[index - 1].getId());
                }
                else if (inp == "2")
                {
                    if (db->getProductDb()->Delete(products[index - 1].getId()))
                        cout << "Product successfully remove to store." << endl;
                    else
                        cout << "The item was not remove to the store!!!" << endl;
                }
            }
            else
                cout << "The processes failed!!!!!!" << endl;
            getch();
        }
        // View by group
        else if (com == "2")
        {
            string inp;
            system("cls");
            QList<Category> category = db->getCategoryDb()->GetAll();
            headerShowCategory();
            showCategory(&category);
            cout << "Enter an index to show product by category(You back with 0): ";
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            if (!(index > 0 && index <= category.size()))
            {
                cout << "The processes failed!!!" << endl;
                getch();
                continue;
            }
            system("cls");
            QList<Product> products = db->getProductDb()->GetByKey("cat", category[index - 1].getId());
            products = combine(&products, &category);
            headerShowProducts();
            showProduct(&products);
            cout << "Enter an index to select(You back with 0): ";
            getline(cin, inp);
            index = toInt(inp);
            if (index == 0)
                continue;
            if (index > 0 && index <= products.size())
            {
                cout << "0 => Back \n1 => Edit \n2 => Remove \ncommand>";
                getline(cin, inp);
                if (inp == "1")
                {
                    editProductPanel(db, products[index - 1].getId());
                }
                else if (inp == "2")
                {
                    if (db->getProductDb()->Delete(products[index - 1].getId()))
                        cout << "Product successfully remove to store." << endl;
                    else
                        cout << "The item was not remove to the store!!!" << endl;
                }
            }
            else
                cout << "The processes failed!!!!!!" << endl;
            getch();
        }
        // Search product
        else if (com == "3")
        {
            QList<Product> productsAll = db->getProductDb()->GetAll();
            QList<Category> category = db->getCategoryDb()->GetAll();
            productsAll = combine(&productsAll, &category);
            string filter = "";
            QList<Product> productsFilter;
            while (true)
            {
                productsFilter = searchProduct(&productsAll, filter);
                system("cls");
                cout << "Enter key to search(You back with 0): " << filter << endl;
                headerShowProducts();
                showProduct(&productsFilter);
                cout << "Enter key to search(You back with 0): " << filter;
                char cinp = getch();
                if (cinp == 13) // The user has pressed the "Enter" key
                    break;
                if (isCharacter(cinp))
                    filter += cinp;
                else if (cinp == 8) // The user has pressed the "Backspace" key
                    filter = filter.substr(0, filter.size() - 1);
            }
            if (filter == "0")
                continue;
            system("cls");
            headerShowProducts();
            showProduct(&productsFilter);
            cout << "Enter an index to select(You back with 0): ";
            string inp;
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            if (index > 0 && index <= productsFilter.size())
            {
                cout << "0 => Back \n1 => Edit \n2 => Remove \ncommand>";
                getline(cin, inp);
                if (inp == "1")
                {
                    editProductPanel(db, productsFilter[index - 1].getId());
                }
                else if (inp == "2")
                {
                    if (db->getProductDb()->Delete(productsFilter[index - 1].getId()))
                        cout << "Product successfully remove to store." << endl;
                    else
                        cout << "The item was not remove to the store!!!" << endl;
                }
            }
            else
                cout << "The processes failed!!!!!!" << endl;
            getch();
        }
        // Add product
        else if (com == "4")
        {
            addProductPanel(db);
            getch();
        }
        // See all category
        else if (com == "5")
        {
            string inp;
            QList<Category> category = db->getCategoryDb()->GetAll();
            system("cls");
            headerShowCategory();
            showCategory(&category);
            cout << "Enter an index to select(You back with 0): ";
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            if (index > 0 && index <= category.size())
            {
                cout << "0 => Back \n1 => Edit \n2 => Remove \ncommand>";
                getline(cin, inp);
                if (inp == "1")
                {
                    editCategoryPanel(db, category[index - 1].getId());
                }
                else if (inp == "2")
                {
                    if (db->getProductDb()->Delete(category[index - 1].getId()))
                        cout << "Product successfully remove to store." << endl;
                    else
                        cout << "The item was not remove to the store!!!" << endl;
                }
            }
            else
                cout << "The processes failed!!!!!!" << endl;
            getch();
        }
        // Search category
        else if (com == "6")
        {
            string inp;
            system("cls");
            QList<Category> categoryAll = db->getCategoryDb()->GetAll();
            QList<Category> categoryFilter;
            string filter = "";
            while (true)
            {
                categoryFilter = searchCategory(&categoryAll, filter);
                system("cls");
                cout << "Enter key to search(You back with 0): " << filter << endl;
                headerShowCategory();
                showCategory(&categoryFilter);
                cout << "Enter key to search(You back with 0): " << filter;
                char cinp = getch();
                if (cinp == 13) // The user has pressed the "Enter" key
                    break;
                if (isCharacter(cinp))
                    filter += cinp;
                else if (cinp == 8) // The user has pressed the "Backspace" key
                    filter = filter.substr(0, filter.size() - 1);
            }
            if (filter == "0")
                continue;
            system("cls");
            headerShowCategory();
            showCategory(&categoryFilter);
            cout << "Enter an index to select(You back with 0): ";
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            if (index > 0 && index <= categoryFilter.size())
            {
                cout << "0 => Back \n1 => Edit \n2 => Remove \ncommand>";
                getline(cin, inp);
                if (inp == "1")
                {
                    editCategoryPanel(db, categoryFilter[index - 1].getId());
                }
                else if (inp == "2")
                {
                    if (db->getProductDb()->Delete(categoryFilter[index - 1].getId()))
                        cout << "Product successfully remove to store." << endl;
                    else
                        cout << "The item was not remove to the store!!!" << endl;
                }
            }
            else
                cout << "The processes failed!!!!!!" << endl;
            getch();
        }
        // Add category
        else if (com == "7")
        {
            addCategoryPanel(db);
            getch();
        }
        // View users
        else if (com == "8" && user.getAccess() == Admin)
        {
            string inp;
            QList<User> users = db->getUserDb()->GetAll();
            system("cls");
            headerShowUser();
            showUser(&users);
            cout << "Enter an index to select(You back with 0): ";
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            if (index > 0 && index <= users.size())
            {
                cout << "0 => Back \n1 => Edit \n2 => Remove \ncommand>";
                getline(cin, inp);
                if (inp == "1")
                {
                    editUserPanel(db, users[index - 1].getId(), user.getAccess());
                }
                else if (inp == "2")
                {
                    if (db->getUserDb()->Delete(users[index - 1].getId()))
                        cout << "User successfully remove." << endl;
                    else
                        cout << "User remove failed!!!!!!" << endl;
                }
            }
            else
                cout << "The processes failed!!!!!!" << endl;
            getch();
        }
        // Add user
        else if (com == "9" && user.getAccess() == Admin)
        {
            addUserPanel(db);
            getch();
        }
        // Edit profile
        else if (com == "10")
        {
            editUserPanel(db, user.getId(), user.getAccess());
            getch();
        }
        // back
        else if (com == "0")
            return;
        // exit
        else if (com == "00")
            exit(0);
        else
            continue;
    }
}