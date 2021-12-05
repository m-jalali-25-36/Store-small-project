#include <iostream>

using namespace std;

#pragma once
class Cart
{
private:
    int id;
    string name;
    int quantity;
    int unitPrice;
    int amount;

public:
    Cart() {}
    Cart(int id,string name, int quantity, int unitPrice)
    {
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->unitPrice = unitPrice;
        this->amount = this->quantity * this->unitPrice;
    }
    ~Cart() {}
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
    int getAmount()
    {
        return amount;
    }
    int getQuantity()
    {
        return quantity;
    }
    void setQuantity(int quantity)
    {
        this->quantity = quantity;
        this->amount = this->quantity * this->unitPrice;
    }
    int getUnitPrice()
    {
        return unitPrice;
    }
    void setUnitPrice(int unitPrice)
    {
        this->unitPrice = unitPrice;
        this->amount = this->quantity * this->unitPrice;
    }
};