#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <QtCore/QList>
#include "product.cpp"
#include "../library/split.cpp"
#include "../library/toLower.cpp"
#include "../library/toInt.cpp"

using namespace std;

#pragma once
class DataBaseProducts
{
private:
    string filePath = "";

public:
    DataBaseProducts(string file_path)
    {
        this->filePath = file_path;
    }
    ~DataBaseProducts() {}

    QList<Product> GetAll()
    {
        QList<Product> result;
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
                if (a.size() > 0 && a[0] == "product")
                {
                    Product p;
                    for (int i = 1; i < a.size(); i += 2)
                        p.set(a[i], a[i + 1]);
                    result.push_back(p);
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

    Product GetById(int id)
    {
        Product result;
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
                bool isFind = false;
                getline(db, s);
                vector<string> a = split(s, '=', ',', ':');
                if (a.size() > 0 && a[0] == "product")
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

    QList<Product> GetById(QList<int> id)
    {
        QList<Product> result;
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
                bool isFind = false;
                getline(db, s);
                vector<string> a = split(s, '=', ',', ':');
                Product p;
                if (a.size() > 0 && a[0] == "product")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        if (tolower(a[i]) == "id")
                            for (int j = 0; j < id.size(); j++)
                                if (toInt(a[i + 1]) == id[j])
                                    isFind = true;
                        p.set(a[i], a[i + 1]);
                    }
                }
                if (isFind)
                    result.push_back(p);
                else
                    p.restart();
            }
            db.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return result;
    }

    QList<Product> GetByKey(string key, int value)
    {
        QList<Product> result;
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
                bool isFind = false;
                getline(db, s);
                vector<string> a = split(s, '=', ',', ':');
                Product p;
                if (a.size() > 0 && a[0] == "product")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        if (tolower(a[i]) == key && toInt(a[i + 1]) == value)
                            isFind = true;
                        p.set(a[i], a[i + 1]);
                    }
                }
                if (isFind)
                    result.push_back(p);
                else
                    p.restart();
            }
            db.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return result;
    }

    bool Insert(Product *product)
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
                    if (a.size() > 0 && a[0] == "product")
                        for (int i = 1; i < a.size(); i += 2)
                            if (tolower(a[i]) == "id" && toInt(a[i + 1]) > maxId)
                                maxId = toInt(a[i + 1]);
                }
                autoId = maxId + 1;
                db.close();
                db.open(filePath, std::ios::in | std::ios::out);
            }
            db.seekp(0, ios::end);
            string a = "\nproduct=id:" + to_string(autoId) +
                       ",n:" + product->getName() +
                       ",cat:" + to_string(product->getCategoryId()) +
                       ",des:" + product->getDescription() +
                       ",p:" + to_string(product->getPrice()) +
                       ",qty:" + to_string(product->getQuantity());
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

    bool Delete(Product *product)
    {
        return Delete(product->getId());
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
                Product p;
                bool addedTemp = false;
                if (a.size() > 0 && a[0] == "product")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        p.set(a[i], a[i + 1]);
                        addedTemp = a[i] == "id" ? (toInt(a[i + 1]) != id) : addedTemp;
                    }
                }
                if (addedTemp)
                {
                    string a = "product=id:" + to_string(p.getId()) +
                               ",n:" + p.getName() +
                               ",cat:" + to_string(p.getCategoryId()) +
                               ",des:" + p.getDescription() +
                               ",p:" + to_string(p.getPrice()) +
                               ",qty:" + to_string(p.getQuantity()) + "\n";
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

    bool Update(Product *product)
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
                Product p;
                bool addedTemp = false;
                if (a.size() > 0 && a[0] == "product")
                {
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        p.set(a[i], a[i + 1]);
                        addedTemp = a[i] == "id" ? (toInt(a[i + 1]) != product->getId()) : addedTemp;
                    }
                }
                if (addedTemp)
                {
                    string a = "product=id:" + to_string(p.getId()) +
                               ",n:" + p.getName() +
                               ",cat:" + to_string(p.getCategoryId()) +
                               ",des:" + p.getDescription() +
                               ",p:" + to_string(p.getPrice()) +
                               ",qty:" + to_string(p.getQuantity()) + "\n";
                    tempDb.write(a.c_str(), a.size());
                }
                else if (a.size() > 0 && a[0] == "product")
                {
                    string a = "product=id:" + to_string(product->getId()) +
                               ",n:" + product->getName() +
                               ",cat:" + to_string(product->getCategoryId()) +
                               ",des:" + product->getDescription() +
                               ",p:" + to_string(product->getPrice()) +
                               ",qty:" + to_string(product->getQuantity()) + "\n";
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

    bool Update(QList<Product> *product)
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
                if (a.size() > 0 && a[0] == "product")
                {
                    Product p;
                    bool addedTemp = true;
                    int addedTempIndex = -1;
                    for (int i = 1; i < a.size(); i += 2)
                    {
                        p.set(a[i], a[i + 1]);
                        if (a[i] == "id")
                        {
                            for (int j = 0; j < product->size(); j++)
                            {
                                Product temp = product->at(j);
                                if (toInt(a[i + 1]) == temp.getId())
                                {
                                    addedTemp = false;
                                    addedTempIndex = j;
                                    break;
                                }
                            }
                        }
                    }
                    if (addedTemp)
                    {
                        string a = "product=id:" + to_string(p.getId()) +
                                   ",n:" + p.getName() +
                                   ",cat:" + to_string(p.getCategoryId()) +
                                   ",des:" + p.getDescription() +
                                   ",p:" + to_string(p.getPrice()) +
                                   ",qty:" + to_string(p.getQuantity()) + "\n";
                        tempDb.write(a.c_str(), a.size());
                    }
                    else
                    {
                        Product temp = product->at(addedTempIndex);
                        string a = "product=id:" + to_string(temp.getId()) +
                                   ",n:" + temp.getName() +
                                   ",cat:" + to_string(temp.getCategoryId()) +
                                   ",des:" + temp.getDescription() +
                                   ",p:" + to_string(temp.getPrice()) +
                                   ",qty:" + to_string(temp.getQuantity()) + "\n";
                        tempDb.write(a.c_str(), a.size());
                    }
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
