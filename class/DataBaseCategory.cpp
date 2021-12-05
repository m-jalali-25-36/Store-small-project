#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <QtCore/QList>
#include "category.cpp"
#include "../library/split.cpp"
#include "../library/toLower.cpp"
#include "../library/toInt.cpp"

using namespace std;

#pragma once
class DataBaseCategory
{
private:
    string filePath = "";

public:
    DataBaseCategory(string file_path)
    {
        this->filePath = file_path;
    }
    ~DataBaseCategory() {}

    QList<Category> GetAll()
    {
        QList<Category> result;
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
                if (a.size() > 0 && a[0] == "category")
                {
                    Category cat;
                    for (int i = 1; i < a.size(); i += 2)
                        cat.set(a[i], a[i + 1]);
                    result.push_back(cat);
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

    Category GetById(int id)
    {
        Category result;
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
                if (a.size() > 0 && a[0] == "category")
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

    bool Insert(Category *category)
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
                    if (a.size() > 0 && a[0] == "category")
                        for (int i = 1; i < a.size(); i += 2)
                            if (tolower(a[i]) == "id" && toInt(a[i + 1]) > maxId)
                                maxId = toInt(a[i + 1]);
                }
                autoId = maxId + 1;
                db.close();
                db.open(filePath, std::ios::in | std::ios::out);
            }
            db.seekp(0, ios::end);
            string a = "\ncategory=id:" + to_string(autoId) +
                       ",n:" + category->getName() +
                       ",des:" + category->getDescription();
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

    bool Delete(Category *category)
    {
        return Delete(category->getId());
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
                Category cat;
                bool addedTemp = false;
                if (a.size() > 0 && a[0] == "category")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        cat.set(a[i], a[i + 1]);
                        addedTemp = a[i] == "id" ? (toInt(a[i + 1]) != id) : addedTemp;
                    }
                }
                if (addedTemp)
                {
                    string a = "category=id:" + to_string(cat.getId()) +
                               ",n:" + cat.getName() +
                               ",des:" + cat.getDescription() + "\n";
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

    bool Update(Category *category)
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
                Category cat;
                bool addedTemp = false;
                if (a.size() > 0 && a[0] == "category")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        cat.set(a[i], a[i + 1]);
                        addedTemp = a[i] == "id" ? (toInt(a[i + 1]) != category->getId()) : addedTemp;
                    }
                }
                if (addedTemp)
                {
                    string a = "category=id:" + to_string(cat.getId()) +
                               ",n:" + cat.getName() +
                               ",des:" + cat.getDescription() + "\n";
                    tempDb.write(a.c_str(), a.size());
                }
                else if (a.size() > 0 && a[0] == "category")
                {
                    string a = "category=id:" + to_string(category->getId()) +
                               ",n:" + category->getName() +
                               ",des:" + category->getDescription() + "\n";
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
