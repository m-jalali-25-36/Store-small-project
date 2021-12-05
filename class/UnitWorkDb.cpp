#include <iostream>
#include "DataBaseProducts.cpp"
#include "DataBaseCategory.cpp"
#include "DataBaseUser.cpp"

using namespace std;

#pragma once
class UnitWorkDb
{
private:
    string path;
    DataBaseProducts *dbProducts = NULL;
    DataBaseCategory *dbCategory = NULL;
    DataBaseUser *dbUsers = NULL;

public:
    UnitWorkDb(string path)
    {
        if (path[path.size() - 1] == '\\')
            this->path = path.substr(0, path.size() - 1);
        else
            this->path = path;
    }
    ~UnitWorkDb()
    {
        if (dbProducts != NULL)
            delete dbProducts;
        if (dbCategory != NULL)
            delete dbCategory;
        if (dbUsers != NULL)
            delete dbUsers;
    }
    DataBaseProducts *getProductDb()
    {
        if (dbProducts == NULL)
        {
            dbProducts = new DataBaseProducts(path + "\\product.db");
        }
        return dbProducts;
    }
    DataBaseCategory *getCategoryDb()
    {
        if (dbCategory == NULL)
        {
            dbCategory = new DataBaseCategory(path + "\\category.db");
        }
        return dbCategory;
    }
    DataBaseUser *getUserDb()
    {
        if (dbUsers == NULL)
        {
            dbUsers = new DataBaseUser(path + "\\user.db");
        }
        return dbUsers;
    }
};