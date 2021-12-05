#include <iostream>
#include <QtCore/QList>
#include "../class/product.cpp"
#include "../class/category.cpp"
#include "../library/contain.cpp"
#include "../library/toLower.cpp"

#pragma once
using namespace std;

QList<Product> searchProduct(QList<Product> *product, string key, bool caseSensitive = false)
{
    if (key == "")
        return *product;
    QList<Product> result;
    if (caseSensitive)
    {
        for (int i = 0; i < product->size(); i++)
        {
            Product p = product->at(i);
            if (contain(p.getName(), key) ||
                contain(p.getCategoryName(), key) ||
                contain(p.getDescription(), key))
                result.push_back(p);
        }
    }
    else
    {
        for (int i = 0; i < product->size(); i++)
        {
            Product p = product->at(i);
            if (contain(tolower(p.getName()), tolower(key)) ||
                contain(tolower(p.getCategoryName()), tolower(key)) ||
                contain(tolower(p.getDescription()), tolower(key)))
                result.push_back(p);
        }
    }
    return result;
}

QList<Category> searchCategory(QList<Category> *category, string key, bool caseSensitive = false)
{
    if (key == "")
        return *category;
    QList<Category> result;
    if (caseSensitive)
    {
        for (int i = 0; i < category->size(); i++)
        {
            Category c = category->at(i);
            if (contain(c.getName(), key) ||
                contain(c.getDescription(), key))
                result.push_back(c);
        }
    }
    else
    {
        for (int i = 0; i < category->size(); i++)
        {
            Category c = category->at(i);
            if (contain(tolower(c.getName()), tolower(key)) ||
                contain(tolower(c.getDescription()), tolower(key)))
                result.push_back(c);
        }
    }
    return result;
}