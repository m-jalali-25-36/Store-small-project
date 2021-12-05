#include <iostream>
#include <QtCore/QList>
#include "../class/product.cpp"
#include "../class/category.cpp"
#include "../class/cart.cpp"

#pragma once
using namespace std;

QList<Product> combine(QList<Product> *product, QList<Category> *category)
{
    QList<Product> result;
    for (size_t i = 0; i < product->size(); i++)
    {
        Product p = product->at(i);
        if (p.getCategoryId() != -1)
            for (int j = 0; j < category->size(); j++)
            {
                Category c = category->at(j);
                if (p.getCategoryId() == c.getId())
                {
                    p.setCategoryName(c.getName());
                    break;
                }
            }
        result.push_back(p);
    }
    return result;
}

QList<Product> combine(QList<Product> *product, QList<Cart> *cart)
{
    QList<Product> result;
    for (size_t i = 0; i < cart->size(); i++)
    {
        Cart c = cart->at(i);
        for (int j = 0; j < product->size(); j++)
        {
            Product p = product->at(j);
            if (p.getId() == c.getId())
            {
                p.setQuantity(c.getQuantity());
                result.push_back(p);
                break;
            }
        }
    }
    return result;
}