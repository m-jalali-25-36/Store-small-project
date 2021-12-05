#include <iostream>

using namespace std;

enum Access
{
    Admin = 1,
    Employee = 2
};

#pragma once
class User
{
private:
    int id;
    string userName;
    string email;
    string pass;
    Access access;

public:
    User()
    {
        restart();
    }
    User(int id, string userName, string email, string pass, Access access = Employee)
    {
        this->id = id;
        this->userName = userName;
        this->email = email;
        this->pass = pass;
        this->access = access;
    }
    ~User() {}
    void restart()
    {
        this->id = -1;
        this->userName = "";
        this->email = "";
        this->pass = "";
        this->access = Employee;
    }
    int getId()
    {
        return id;
    }
    void setId(int id)
    {
        this->id = id;
    }
    string getUserName()
    {
        return userName;
    }
    void setUserName(string userName)
    {
        this->userName = userName;
    }
    string getEmail()
    {
        return email;
    }
    void setEmail(string email)
    {
        this->email = email;
    }
    string getPassword()
    {
        return pass;
    }
    void setPassword(string pass)
    {
        this->pass = pass;
    }
    Access getAccess()
    {
        return access;
    }
    void setAccess(Access access)
    {
        this->access = access;
    }
    bool set(string key, string value)
    {
        key = tolower(key);
        if (key == "id")
            this->id = toInt(value);
        else if (key == "un" || key == "userName")
            this->userName = value;
        else if (key == "e" || key == "email")
            this->email = value;
        else if (key == "p" || key == "pass")
            this->pass = value;
        else if (key == "a" || key == "access")
            this->access = static_cast<Access>(toInt(value));
        else
            return false;
        return true;
    }
};