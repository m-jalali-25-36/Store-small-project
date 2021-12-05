#include <iostream>
#include <conio.h>
#include "../class/cart.cpp"
#include "../class/UnitWorkDb.cpp"
#include "../tools/combine.cpp"
#include "../tools/show.cpp"
#include "../tools/search.cpp"
#include "../tools/sumAmount.cpp"
#include "../library/isCharacter.cpp"

#pragma once
using namespace std;

void customerPanel(UnitWorkDb *db)
{
    QList<Cart> cart;
    while (true)
    {
        system("cls");
        cout << "--------------------------------------------" << endl;
        cout << "|             Please select one.           |" << endl;
        cout << "|   Cart: " << setw(2) << cart.size() << "                               |" << endl;
        cout << "|   1) See all                             |" << endl;
        cout << "|   2) View by group                       |" << endl;
        cout << "|   3) Search product                      |" << endl;
        cout << "|   4) Search category                     |" << endl;
        cout << "|   5) See cart                            |" << endl;
        cout << "|   6) End of purchase                     |" << endl;
        cout << "|   0) Back & Cancel                       |" << endl;
        cout << "|  00) Exit                                |" << endl;
        cout << "|                                          |" << endl;
        cout << "--------------------------------------------" << endl;
        string com;
        getline(cin, com);
        // See all
        if (com == "1")
        {
            system("cls");
            QList<Product> products = db->getProductDb()->GetAll();
            QList<Category> category = db->getCategoryDb()->GetAll();
            products = combine(&products, &category);
            headerShowProducts();
            showProduct(&products);
            cout << "Enter an index to add to cart(You back with 0): ";
            string inp;
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            cout << "Quantity: ";
            getline(cin, inp);
            int qty = toInt(inp);
            if (index > 0 && index <= products.size() && qty > 0 && qty <= products[index - 1].getQuantity())
            {
                cart.push_back(Cart(products[index - 1].getId(), products[index - 1].getName(), qty, products[index - 1].getPrice()));
                cout << "Product successfully added to cart." << endl;
            }
            else
                cout << "The item was not added to the cart!!!" << endl;
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
            cout << "Enter an index to add to cart(You back with 0): ";
            getline(cin, inp);
            index = toInt(inp);
            if (index == 0)
                continue;
            cout << "Quantity: ";
            getline(cin, inp);
            int qty = toInt(inp);
            if (index > 0 && index <= products.size() && qty > 0 && qty <= products[index - 1].getQuantity())
            {
                cart.push_back(Cart(products[index - 1].getId(), products[index - 1].getName(), qty, products[index - 1].getPrice()));
                cout << "Product successfully added to cart." << endl;
            }
            else
                cout << "The item was not added to the cart!!!" << endl;
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
            cout << "Enter an index to add to cart(You back with 0): ";
            string inp;
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            cout << "Quantity: ";
            getline(cin, inp);
            int qty = toInt(inp);
            if (index > 0 && index <= productsFilter.size() && qty > 0 && qty <= productsFilter[index - 1].getQuantity())
            {
                cart.push_back(Cart(productsFilter[index - 1].getId(), productsFilter[index - 1].getName(), qty, productsFilter[index - 1].getPrice()));
                cout << "Product successfully added to cart." << endl;
            }
            else
                cout << "The item was not added to the cart!!!" << endl;
                getch();
        }
        // Search category
        else if (com == "4")
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
            cout << "Enter an index to show product by category(You back with 0): ";
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            if (!(index > 0 && index <= categoryFilter.size()))
            {
                cout << "The processes failed!!!" << endl;
                getch();
                continue;
            }
            QList<Product> productsAll = db->getProductDb()->GetByKey("cat", categoryFilter[index - 1].getId());
            productsAll = combine(&productsAll, &categoryAll);
            filter = "";
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
            cout << "Enter an index to add to cart(You back with 0): ";
            getline(cin, inp);
            index = toInt(inp);
            if (index == 0)
                continue;
            cout << "Quantity: ";
            getline(cin, inp);
            int qty = toInt(inp);
            if (index > 0 && index <= productsFilter.size() && qty > 0 && qty <= productsFilter[index - 1].getQuantity())
            {
                cart.push_back(Cart(productsFilter[index - 1].getId(), productsFilter[index - 1].getName(), qty, productsFilter[index - 1].getPrice()));
                cout << "Product successfully added to cart." << endl;
            }
            else
                cout << "The item was not added to the cart!!!" << endl;
                getch();
        }
        // See cart
        else if (com == "5")
        {
            system("cls");
            headerShowCart();
            showCart(&cart);
            cout << "Total: " << sumAmount(&cart) << endl;
            cout << "Enter an index to remove to cart(You back with 0): ";
            string inp;
            getline(cin, inp);
            int index = toInt(inp);
            if (index == 0)
                continue;
            if (index > 0 && index <= cart.size())
            {
                cart.removeAt(index - 1);
                cout << "Product successfully removed from cart." << endl;
            }
            else
                cout << "Item not removed from cart!!!" << endl;
            getch();
        }
        // End of purchase
        else if (com == "6")
        {
            string inp;
            system("cls");
            headerShowCart();
            showCart(&cart);
            cout << "Total: " << sumAmount(&cart) << endl;
            cout << "Are you sure you want to finish your purchase?(y/n): ";
            getline(cin, inp);
            if (inp == "y" || inp == "Y" || inp == "yes")
            {
                QList<Product> product = db->getProductDb()->GetAll();
                QList<Product> productUpdate;
                for (int i = 0; i < cart.size(); i++)
                {
                    for (int j = 0; j < product.size(); j++)
                    {
                        if (product[j].getId() == cart[i].getId())
                        {
                            Product pu = product[j];
                            pu.reduceQuantity(cart[i].getQuantity());
                            productUpdate.push_back(pu);
                            break;
                        }
                    }
                }
                db->getProductDb()->Update(&productUpdate);
                cart.clear();
                cout << "Your purchase was completed successfully." << endl;
                getch();
            }
            else
                continue;
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
