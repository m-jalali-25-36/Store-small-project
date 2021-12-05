#include <iostream>
#include "../class/product.cpp"

#pragma once
using namespace std;

void printProduct(Product *product)
{
    system("cls");
    cout << "Name: " << product->getName() << endl;
    cout << "Category: " << product->getCategoryName() << endl;
    cout << "Price: " << product->getPrice() << endl;
    cout << "Quantity: " << product->getQuantity() << endl;
    cout << "Description: " << product->getDescription() << endl;
}