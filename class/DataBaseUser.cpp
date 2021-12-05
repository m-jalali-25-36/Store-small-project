#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <QtCore/QList>
#include "user.cpp"
#include "../library/split.cpp"
#include "../library/toLower.cpp"
#include "../library/toInt.cpp"

using namespace std;

#pragma once
class DataBaseUser
{
private:
    string filePath = "";

public:
    DataBaseUser(string file_path)
    {
        this->filePath = file_path;
    }
    ~DataBaseUser() {}

    QList<User> GetAll()
    {
        QList<User> result;
        if (filePath == "")
            return result;
        try
        {
            string s;
            fstream db(filePath, std::ios::in);
            if (!db.is_open())
                return result;
            while (!db.eof())
            {
                getline(db, s);
                vector<string> a = split(s, '=', ',', ':');
                if (a.size() > 0 && a[0] == "user")
                {
                    User u;
                    for (int i = 1; i < a.size(); i += 2)
                        u.set(a[i], a[i + 1]);
                    result.push_back(u);
                }
            }
            db.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return result;
    }

    User GetById(int id)
    {
        User result;
        if (filePath == "")
            return result;
        try
        {
            string s;
            fstream db(filePath, std::ios::in);
            if (!db.is_open())
                return result;
            bool isFind = false;
            while (!db.eof())
            {
                getline(db, s);
                vector<string> a = split(s, '=', ',', ':');
                if (a.size() > 0 && a[0] == "user")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        if (tolower(a[i]) == "id" && toInt(a[i + 1]) == id)
                            isFind = true;
                        result.set(a[i], a[i + 1]);
                    }
                }
                if (isFind)
                    break;
                else
                    result.restart();
            }
            db.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return result;
    }

    User GetByUsername(string username)
    {
        User result;
        if (filePath == "")
            return result;
        try
        {
            string s;
            fstream db(filePath, std::ios::in);
            if (!db.is_open())
                return result;
            bool isFind = false;
            while (!db.eof())
            {
                getline(db, s);
                vector<string> a = split(s, '=', ',', ':');
                if (a.size() > 0 && a[0] == "user")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        if (tolower(a[i]) == "un" && a[i + 1] == username)
                            isFind = true;
                        result.set(a[i], a[i + 1]);
                    }
                }
                if (isFind)
                    break;
                else
                    result.restart();
            }
            db.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return result;
    }

    bool Insert(User *user)
    {
        if (filePath == "")
            return false;
        try
        {
            string s;
            int autoId;
            fstream db(filePath, std::ios::in | std::ios::out);
            if (!db.is_open())
            {
                db.open(filePath, std::ios::in | std::ios::out | fstream::trunc);
                autoId = 1;
            }
            else
            {
                int maxId = 0;
                db.seekp(0, ios::beg);
                while (!db.eof())
                {
                    getline(db, s);
                    vector<string> a = split(s, '=', ',', ':');
                    if (a.size() > 0 && a[0] == "user")
                        for (int i = 1; i < a.size(); i += 2)
                            if (tolower(a[i]) == "id")
                                maxId = toInt(a[i + 1]);
                }
                autoId = maxId + 1;
                db.close();
                db.open(filePath, std::ios::in | std::ios::out);
            }
            db.seekp(0, ios::end);
            string a = "\nuser=id:" + to_string(autoId) +
                       ",un:" + user->getUserName() +
                       ",e:" + user->getEmail() +
                       ",p:" + user->getPassword() +
                       ",a:" + to_string(user->getAccess());
            db.write(a.c_str(), a.size());
            db.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        return true;
    }

    bool Delete(User *user)
    {
        return Delete(user->getId());
    }

    bool Delete(int id)
    {
        if (filePath == "")
            return false;
        try
        {
            string s;
            ofstream tempDb(filePath + ".tmp", std::ios::in | std::ios::out | fstream::trunc);
            fstream db(filePath, std::ios::in | std::ios::out);
            if (!db.is_open())
                return false;
            while (!db.eof())
            {
                getline(db, s);
                vector<string> a = split(s, '=', ',', ':');
                User u;
                bool addedTemp = false;
                if (a.size() > 0 && a[0] == "user")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        u.set(a[i], a[i + 1]);
                        addedTemp = a[i] == "id" ? (toInt(a[i + 1]) != id) : addedTemp;
                    }
                }
                if (addedTemp)
                {
                    string a = "user=id:" + to_string(u.getId()) +
                               ",un:" + u.getUserName() +
                               ",e:" + u.getEmail() +
                               ",p:" + u.getPassword() +
                               ",a:" + to_string(u.getAccess()) + "\n";
                    tempDb.write(a.c_str(), a.size());
                }
            }
            db.close();
            tempDb.close();
            remove(filePath.c_str());                              // remove database file
            rename((filePath + ".tmp").c_str(), filePath.c_str()); // rename temp file
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        return true;
    }

    bool Update(User *user)
    {
        if (filePath == "")
            return false;
        try
        {
            string s;
            ofstream tempDb(filePath + ".tmp", std::ios::in | std::ios::out | fstream::trunc);
            fstream db(filePath, std::ios::in | std::ios::out);
            if (!db.is_open())
                return false;
            while (!db.eof())
            {
                getline(db, s);
                vector<string> a = split(s, '=', ',', ':');
                User u;
                bool addedTemp = false;
                if (a.size() > 0 && a[0] == "user")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        u.set(a[i], a[i + 1]);
                        addedTemp = a[i] == "id" ? (toInt(a[i + 1]) != user->getId()) : addedTemp;
                    }
                }
                if (addedTemp)
                {
                    string a = "user=id:" + to_string(u.getId()) +
                               ",un:" + u.getUserName() +
                               ",e:" + u.getEmail() +
                               ",p:" + u.getPassword() +
                               ",a:" + to_string(u.getAccess()) + "\n";
                    tempDb.write(a.c_str(), a.size());
                }
                else if (a.size() > 0 && a[0] == "user")
                {
                    string a = "user=id:" + to_string(user->getId()) +
                               ",un:" + user->getUserName() +
                               ",e:" + user->getEmail() +
                               ",p:" + user->getPassword() +
                               ",a:" + to_string(user->getAccess()) + "\n";
                    tempDb.write(a.c_str(), a.size());
                }
            }
            db.close();
            tempDb.close();
            remove(filePath.c_str());                              // remove database file
            rename((filePath + ".tmp").c_str(), filePath.c_str()); // rename temp file
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        return true;
    }
};
