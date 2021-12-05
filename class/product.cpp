#include <iostream>
#include "../library/toLower.cpp"
#include "../library/toInt.cpp"

using namespace std;

#pragma once
class Product
{
private:
    int id;
    string name;
    int category;
    string categoryName;
    string description;
    int price;
    int quantity;

public:
    Product()
    {
        restart();
    }
    Product(int id, string name, int category, string description, long int price, int quantity)
    {
        this->id = id;
        this->name = name;
        this->category = category;
        this->description = description;
        this->price = price;
        this->quantity = quantity;
    }
    ~Product() {}
    void restart()
    {
        this->id = -1;
        this->name = "";
        this->category = -1;
        this->description = "";
        this->price = -1;
        this->quantity = -1;
    }
    int getId()
    {
        return id;
    }
    void setId(int id)
    {
        this->id = id;
    }
    string getName()
    {
        return name;
    }
    void setName(string name)
    {
        this->name = name;
    }
    int getCategoryId()
    {
        return category;
    }
    void setCategoryId(int category)
    {
        this->category = category;
    }
    string getCategoryName()
    {
        return categoryName;
    }
    void setCategoryName(string categoryName)
    {
        this->categoryName = categoryName;
    }
    string getDescription()
    {
        return description;
    }
    void setDescription(string description)
    {
        this->description = description;
    }
    int getPrice()
    {
        return price;
    }
    void setPrice(int price)
    {
        this->price = price;
    }
    int getQuantity()
    {
        return quantity;
    }
    void setQuantity(int quantity)
    {
        this->quantity = quantity;
    }
    void reduceQuantity(int reduce)
    {
        this->quantity -= reduce;
    }
    bool set(string key, string value)
    {
        key = tolower(key);
        if (key == "id")
            this->id = toInt(value);
        else if (key == "n" || key == "name")
            this->name = value;
        else if (key == "cat" || key == "category")
            this->category = toInt(value);
        else if (key == "des" || key == "description")
            this->description = value;
        else if (key == "p" || key == "price")
            this->price = toInt(value);
        else if (key == "qty" || key == "quantity")
            this->quantity = toInt(value);
        else
            return false;
        return true;
    }
};