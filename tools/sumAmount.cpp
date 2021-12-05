#include <iostream>
#include <QtCore/QList>
#include "../class/cart.cpp"

#pragma once
using namespace std;

int sumAmount(QList<Cart> *cart)
{
    int sum = 0;
    for (int i = 0; i < cart->size(); i++)
    {
        Cart c = cart->at(i);
        sum += c.getAmount();
    }
    return sum;
}