#include <iostream>

using namespace std;

#pragma once
class Category
{
private:
    int id;
    string name;
    string description;

public:
    Category()
    {
        restart();
    }
    Category(int id, string name, string description = "")
    {
        this->id = id;
        this->name = name;
        this->description = description;
    }
    ~Category() {}
    void restart()
    {
        this->id = -1;
        this->name = "";
        this->description = "";
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
    string getDescription()
    {
        return description;
    }
    void setDescription(string description)
    {
        this->description = description;
    }
    bool set(string key, string value)
    {
        key = tolower(key);
        if (key == "id")
            this->id = toInt(value);
        else if (key == "n" || key == "name")
            this->name = value;
        else if (key == "des" || key == "description")
            this->description = value;
        else
            return false;
        return true;
    }
};